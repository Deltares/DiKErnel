// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System;
using System.Windows;
using System.Windows.Media;
using DiKErnel.Application;
using Microsoft.Win32;

namespace DiKErnel.Gui
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            DataContext = this;

            VersionNumber = ApplicationHelper.ApplicationVersionString;
            InputFilePath = "Invoerbestand.json";
            OutputFilePath = "Uitvoerbestand.json";
        }

        public string VersionNumber { get; private set; }

        public string InputFilePath { get; private set; }

        public string OutputFilePath { get; private set; }

        private void OnInputFileOpenButtonClicked(object sender, RoutedEventArgs e)
        {
            var openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
            {
                InputFilePath = openFileDialog.FileName;
                InputTextBlock.Text = InputFilePath;
                InputTextBlock.Foreground = Brushes.Black;
                //this is to make sure that the rightmost part of text is visible in the textBlock when text is updated.
                InputTextBlock.HorizontalAlignment = HorizontalAlignment.Right;
            }
        }

        private void OnOutputFileOpenButtonClicked(object sender, RoutedEventArgs e)
        {
            var openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true)
            {
                OutputFilePath = openFileDialog.FileName;
                OutputTextBlock.Text = OutputFilePath;
                OutputTextBlock.Foreground = Brushes.Black;
                //this is to make sure that the rightmost part of text is visible in the textBlock when text is updated.
                OutputTextBlock.HorizontalAlignment = HorizontalAlignment.Right;
            }
        }

        private void OnStartButtonClicked(object sender, RoutedEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void OnEraseButtonClicked(object sender, RoutedEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void OnCopyButtonClicked(object sender, RoutedEventArgs e)
        {
            throw new NotImplementedException();
        }
    }
}