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
using DiKErnel.Gui.ViewModel;
using Microsoft.Win32;

namespace DiKErnel.Gui.View
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        string fileDialogFilter = "Json files (*.json)|*.json|All files (*.*)|*.*";
        private MainWindowViewModel MainWindowViewModel { get; set; }

        public MainWindow()
        {
            MainWindowViewModel = new MainWindowViewModel();
            DataContext = MainWindowViewModel;
            InitializeComponent();
        }

        private void OnInputFileOpenButtonClicked(object sender, RoutedEventArgs e)
        {
            var openFileDialog = new OpenFileDialog
            {
                Filter = fileDialogFilter
            };
            if (openFileDialog.ShowDialog() == true)
            {
                MainWindowViewModel.InputFilePath = openFileDialog.FileName;
                InputTextBlock.Text = openFileDialog.FileName;
                InputTextBlock.Foreground = Brushes.Black;

                //this is to make sure that the rightmost part of text is visible in the textBlock when text is updated.
                InputTextBlock.HorizontalAlignment = HorizontalAlignment.Right;
            }
        }

        private void OnOutputFileOpenButtonClicked(object sender, RoutedEventArgs e)
        {
            var openFileDialog = new SaveFileDialog
            {
                Filter = fileDialogFilter,
                CheckFileExists = false
            };

            if (openFileDialog.ShowDialog() == true)
            {
                MainWindowViewModel.OutputFilePath = openFileDialog.FileName;
                OutputTextBlock.Text = openFileDialog.FileName;
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