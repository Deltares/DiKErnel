Powershell.exe -executionpolicy remotesigned -File  BuildMinGWMakeFiles.ps1

cd ../Development/MinGW/Test

start cmd.exe /k for /F %%G in ('dir /b /s *.exe') do %%G --gtest_output=xml:%%~nG.xml