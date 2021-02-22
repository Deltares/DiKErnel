Powershell.exe -executionpolicy remotesigned -File  BuildMinGWMakeFiles.ps1

cd ../Development/MinGW/Test

start cmd.exe /k DiKErnel.Core.Test\DiKErnel.Core.Test.exe --gtest_output=xml:core.xml & DiKErnel.DomainLibrary.Test\DiKErnel.DomainLibrary.Test.exe --gtest_output=xml:domain_library.xml & DiKErnel.FunctionLibrary.Test\DiKErnel.FunctionLibrary.Test.exe --gtest_output=xml:function_library.xml & DiKErnel.KernelWrapper.Json.Test\DiKErnel.KernelWrapper.Json.Test.exe --gtest_output=xml:kernel_wrapper_json.xml