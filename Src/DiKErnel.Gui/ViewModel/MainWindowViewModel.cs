using System.ComponentModel;
using DiKErnel.Application;

namespace DiKErnel.Gui.ViewModel
{
    public class MainWindowViewModel : INotifyPropertyChanged
    {
    private string outputFilePath;
    private string inputFilePath;
    private string versionNumber;
    
        public MainWindowViewModel()
        {
            inputFilePath = "Invoerbestand.json";
            outputFilePath = "Invoerbestand.json";
            versionNumber = ApplicationHelper.ApplicationVersionString;
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

        public event PropertyChangedEventHandler PropertyChanged;  
        private void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }  
    }
}