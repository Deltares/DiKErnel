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