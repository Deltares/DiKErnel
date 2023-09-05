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
using DiKErnel.Application;

namespace DiKErnel.Gui.ViewModel
{
    public class MainWindowViewModel : INotifyPropertyChanged
    {
        private string outputFilePath;
        private string inputFilePath;
        private string versionNumber;
        private ObservableCollection<TextBlock> textBlocks;

        public event PropertyChangedEventHandler PropertyChanged;

        public MainWindowViewModel()
        {
            inputFilePath = "Invoerbestand.json";
            outputFilePath = "Uitvoerbestand.json";
            versionNumber = ApplicationHelper.ApplicationVersionString;
            TextBlocks = new ObservableCollection<TextBlock>();
        }

        public ObservableCollection<TextBlock> TextBlocks
        {
            get => textBlocks;
            set
            {
                if (Equals(value, textBlocks))
                    return;
                textBlocks = value;
                OnPropertyChanged(nameof(TextBlocks));
            }
        }

        public string VersionNumber
        {
            get => versionNumber;
            set
            {
                if (value == versionNumber)
                    return;
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
                    return;
                inputFilePath = value;
                OnPropertyChanged(nameof(InputFilePath));
            }
        }

        public string OutputFilePath
        {
            get => outputFilePath;
            set
            {
                if (value == outputFilePath)
                    return;
                outputFilePath = value;
                OnPropertyChanged(nameof(OutputFilePath));
            }
        }

        private void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}