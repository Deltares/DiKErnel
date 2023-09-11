// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using DiKErnel.Application;
using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Gui.ViewModel;
using DiKErnel.KernelWrapper.Json.Input;
using DiKErnel.KernelWrapper.Json.Output;
using DiKErnel.Util;
using Microsoft.Win32;

namespace DiKErnel.Gui.View
{
    public partial class MainWindow
    {
        private const string fileDialogFilter = "Json files (*.json)|*.json|All files (*.*)|*.*";

        private readonly MainWindowViewModel mainWindowViewModel = new MainWindowViewModel();
        private readonly Dictionary<string, IEnumerable<string>> errorMessageCache = new Dictionary<string, IEnumerable<string>>();
        private readonly Dictionary<string, IEnumerable<string>> warningMessageCache = new Dictionary<string, IEnumerable<string>>();

        public MainWindow()
        {
            InitializeComponent();

            DataContext = mainWindowViewModel;
        }

        private void OnRequestNavigate(object sender, RequestNavigateEventArgs e)
        {
            Process.Start(new ProcessStartInfo(e.Uri.AbsoluteUri)
            {
                UseShellExecute = true
            });

            e.Handled = true;
        }

        private void OnSelectInputFileButtonClicked(object sender, RoutedEventArgs e)
        {
            var openFileDialog = new OpenFileDialog
            {
                Filter = fileDialogFilter
            };

            if (openFileDialog.ShowDialog() == true)
            {
                mainWindowViewModel.InputFilePath = openFileDialog.FileName;
            }
        }

        private void OnSelectOutputFileButtonClicked(object sender, RoutedEventArgs e)
        {
            var openFileDialog = new SaveFileDialog
            {
                Filter = fileDialogFilter,
                CheckFileExists = false
            };

            if (openFileDialog.ShowDialog() == true)
            {
                mainWindowViewModel.OutputFilePath = openFileDialog.FileName;
            }
        }

        private void OnFilePathChanged(object sender, TextChangedEventArgs e)
        {
            var textBox = (TextBox) sender;

            // Set cursor to end
            textBox.CaretIndex = textBox.Text.Length;
            textBox.Focus();
        }

        private void OnStartButtonClicked(object sender, RoutedEventArgs e)
        {
            StartCalculation();
        }

        private void OnCopyButtonClicked(object sender, RoutedEventArgs e)
        {
            Clipboard.SetText(
                string.Join(Environment.NewLine, mainWindowViewModel.TextBlocks.Select(block => block.Text)));
        }

        private void OnEraseButtonClicked(object sender, RoutedEventArgs e)
        {
            mainWindowViewModel.TextBlocks.Clear();
        }

        #region Calculate

        private void StartCalculation()
        {
            try
            {
                RemoveFileWhenExists(mainWindowViewModel.OutputFilePath);

                DataResult<ICalculationInput> calculationInputDataResult = ValidateAndReadInput(mainWindowViewModel.InputFilePath);

                if (calculationInputDataResult == null)
                {
                    return;
                }

                ICalculationInput calculationInput = calculationInputDataResult.Data;

                if (!ValidateCalculationInput(calculationInput))
                {
                    return;
                }

                var stopwatch = new Stopwatch();

                stopwatch.Start();

                DataResult<CalculationOutput> calculatorResult = Calculate(calculationInput);

                if (calculatorResult == null)
                {
                    return;
                }

                stopwatch.Stop();

                WriteOutput(calculatorResult.Data, stopwatch);

                WriteFinalLogMessages(calculationInput, stopwatch);
            }
            catch
            {
                AddMessage("Berekening mislukt", TextType.Bold);
                AddMessage("Er is een onverwachte fout opgetreden. Indien gewenst kunt u contact met ons opnemen via " +
                           "dikernel@deltares.nl.");
                AddMessage("");
            }
        }

        private static void RemoveFileWhenExists(string filePath)
        {
            if (File.Exists(filePath))
            {
                File.Delete(filePath);
            }
        }

        private DataResult<ICalculationInput> ValidateAndReadInput(string jsonInputFilePath)
        {
            if (mainWindowViewModel.ValidateJsonInput)
            {
                bool validationResult = JsonInputComposer.ValidateJson(jsonInputFilePath);

                CacheMessagesWhenApplicable("het valideren van het Json-formaat", EventRegistry.Flush());

                if (!validationResult)
                {
                    LogFailureMessage();

                    return null;
                }
            }

            DataResult<ICalculationInput> inputComposerResult = JsonInputComposer.GetInputDataFromJson(jsonInputFilePath);

            CacheMessagesWhenApplicable("het valideren van het Json-formaat", inputComposerResult.Events);

            if (inputComposerResult.Successful)
            {
                return inputComposerResult;
            }

            LogFailureMessage();

            return null;
        }

        private bool ValidateCalculationInput(ICalculationInput calculationInput)
        {
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput);

            CacheMessagesWhenApplicable("het valideren van de invoer", validationResult.Events);

            if (validationResult.Data != ValidationResultType.Failed && validationResult.Successful)
            {
                return true;
            }

            LogFailureMessage();

            return false;
        }

        private DataResult<CalculationOutput> Calculate(ICalculationInput calculationInput)
        {
            var calculator = new Calculator(calculationInput);

            calculator.WaitForCompletion();

            DataResult<CalculationOutput> calculatorResult = calculator.Result;

            CacheMessagesWhenApplicable("de berekening", calculatorResult.Events);

            if (calculator.CalculationState == CalculationState.FinishedSuccessfully && calculatorResult.Successful)
            {
                return calculatorResult;
            }

            LogFailureMessage();

            return null;
        }

        private void CacheMessagesWhenApplicable(string endOfDescription, IEnumerable<Event> events)
        {
            var errorMessages = new List<string>();
            var warningMessages = new List<string>();

            foreach (Event e in events)
            {
                switch (e.Type)
                {
                    case EventType.Error:
                        errorMessages.Add(e.Message);
                        break;
                    case EventType.Warning:
                        warningMessages.Add(e.Message);
                        break;
                    default:
                        throw new ArgumentOutOfRangeException();
                }
            }

            if (warningMessages.Any())
            {
                warningMessageCache[endOfDescription] = warningMessages;
            }

            if (errorMessages.Any())
            {
                errorMessageCache[endOfDescription] = errorMessages;
            }
        }

        private void LogFailureMessage()
        {
            AddMessage("Berekening mislukt", TextType.Bold);

            LogCachedMessages(errorMessageCache, "fout", "fouten");

            AddMessage("");
        }

        private void AddMessage(string s, TextType textType = TextType.Normal)
        {
            var textBlock = new TextBlock
            {
                Text = s
            };
            switch (textType)
            {
                case TextType.Normal:
                    break;
                case TextType.Bold:
                    textBlock.FontWeight = FontWeights.Bold;
                    break;
                case TextType.Italic:
                    textBlock.FontStyle = FontStyles.Italic;
                    break;
                default:
                    throw new ArgumentOutOfRangeException(nameof(textType), textType, null);
            }

            mainWindowViewModel.TextBlocks.Add(textBlock);
        }

        private void LogCachedMessages(Dictionary<string, IEnumerable<string>> messageCache,
                                       string messageTypeDescriptionSingular, string messageTypeDescriptionPlural)
        {
            foreach ((string endOfDescription, IEnumerable<string> messagesEnumerable) in messageCache)
            {
                IEnumerable<string> messages = messagesEnumerable.ToList();
                if (messages.Count() == 1)
                {
                    AddMessage($"De volgende {messageTypeDescriptionSingular} is opgetreden tijdens {endOfDescription}:");
                    AddMessage($"{messages.ElementAt(0)}", TextType.Italic);
                }
                else
                {
                    AddMessage($"De volgende {messageTypeDescriptionPlural} is opgetreden tijdens {endOfDescription}:");
                    AddMessage($"{messages.ElementAt(0)}", TextType.Italic);

                    foreach (string message in messages)
                    {
                        AddMessage($"- {message}", TextType.Italic);
                    }
                }
            }
        }

        private void WriteFinalLogMessages(ICalculationInput calculationInput, Stopwatch elapsed)
        {
            AddMessage(@"Berekening gelukt", TextType.Bold);

            LogCachedMessages(warningMessageCache, "waarschuwing", "waarschuwingen");

            int numberOfLocations = calculationInput.LocationDependentInputItems.Count;
            int numberOfTimeSteps = calculationInput.TimeDependentInputItems.Count;

            var timeStepString = $"{(numberOfTimeSteps == 1 ? "is {numberOfTimeSteps} tijdstap" : "zijn {numberOfTimeSteps} tijdstappen")}";

            AddMessage($"Er {timeStepString} doorgerekend voor {numberOfLocations} {(numberOfLocations == 1 ? "locatie" : "locaties")}.");

            AddMessage($"De rekenduur bedroeg {elapsed.Elapsed.Seconds} seconden.");

            AddMessage("Zie het uitvoerbestand voor verdere details.");

            AddMessage("");
        }

        private void WriteOutput(CalculationOutput calculationOutput, Stopwatch elapsed)
        {
            Dictionary<string, object> metaDataItems = null;

            if (mainWindowViewModel.WriteMetadata)
            {
                metaDataItems = new Dictionary<string, object>
                {
                    ["versie"] = ApplicationHelper.ApplicationVersionString,
                    ["besturingssysteem"] = ApplicationHelper.OperatingSystemName,
                    ["tijdstipBerekening"] = ApplicationHelper.FormattedDateTimeString,
                    ["tijdsduurBerekening"] = elapsed.Elapsed.Seconds
                };
            }

            SimpleResult outputComposerResult = JsonOutputComposer.WriteCalculationOutputToJson(
                mainWindowViewModel.OutputFilePath, calculationOutput, mainWindowViewModel.OutputType, metaDataItems);

            CacheMessagesWhenApplicable("het schrijven van de resultaten", outputComposerResult.Events);

            if (!outputComposerResult.Successful)
            {
                LogFailureMessage();
            }
        }

        private enum TextType
        {
            Bold,
            Italic,
            Normal
        }

        #endregion
    }
}