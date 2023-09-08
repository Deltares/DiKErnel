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

using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows.Controls;
using System.Windows.Media;
using DiKErnel.Application;
using DiKErnel.KernelWrapper.Json.Output;

namespace DiKErnel.Gui.ViewModel
{
    internal class MainWindowViewModel : INotifyPropertyChanged
    {
        private const string exampleInputFilePath = "Invoerbestand.json";
        private const string exampleOutputFilePath = "Uitvoerbestand.json";

        private string versionNumber;
        private string inputFilePath = exampleInputFilePath;
        private string outputFilePath = exampleOutputFilePath;

        public event PropertyChangedEventHandler PropertyChanged;

        public MainWindowViewModel()
        {
            versionNumber = ApplicationHelper.ApplicationVersionString;
        }

        public ObservableCollection<TextBlock> TextBlocks { get; set; } = new ObservableCollection<TextBlock>();

        public string VersionNumber
        {
            get => versionNumber;
            set
            {
                if (value == versionNumber)
                {
                    return;
                }

                versionNumber = value;

                OnPropertyChanged(nameof(VersionNumber));
            }
        }

        public string InputFilePath
        {
            get => inputFilePath;
            set
            {
                if (value == inputFilePath)
                {
                    return;
                }

                inputFilePath = value;

                OnPropertyChanged(nameof(InputFilePath));
                OnPropertyChanged(nameof(InputFilePathForeground));
                OnPropertyChanged(nameof(CanCalculate));
            }
        }

        public SolidColorBrush InputFilePathForeground => InputFilePath == exampleInputFilePath ? Brushes.DarkGray : Brushes.Black;

        public string OutputFilePath
        {
            get => outputFilePath;
            set
            {
                if (value == outputFilePath)
                {
                    return;
                }

                outputFilePath = value;

                OnPropertyChanged(nameof(OutputFilePath));
                OnPropertyChanged(nameof(OutputFilePathForeground));
                OnPropertyChanged(nameof(CanCalculate));
            }
        }

        public SolidColorBrush OutputFilePathForeground => OutputFilePath == exampleOutputFilePath ? Brushes.DarkGray : Brushes.Black;

        public JsonOutputType OutputType { get; set; } = JsonOutputType.Damage;

        public bool CanCalculate => InputFilePath != exampleInputFilePath && outputFilePath != exampleOutputFilePath;

        private void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}