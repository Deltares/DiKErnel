# syntax=docker/dockerfile:1

FROM mcr.microsoft.com/windows/servercore:ltsc2022

# Set powershell as default shell
SHELL ["powershell", "-Command", "$ErrorActionPreference = 'Stop'; $ProgressPreference = 'SilentlyContinue';"]

RUN Set-ExecutionPolicy Bypass -Scope Process -Force; \
    $installVCRedistScript = ((New-Object System.Net.WebClient).DownloadString('https://vcredist.com/install.ps1')); \
    Invoke-Command -ScriptBlock ([scriptblock]::Create($installVCRedistScript));

RUN $installDotnet = ((New-Object System.Net.WebClient).DownloadString('https://dot.net/v1/dotnet-install.ps1')); \
    & ([scriptblock]::Create($installDotnet)) -Version 7.0.304 -Architecture x86 -InstallDir C:\dotnet; \
    $path = [Environment]::GetEnvironmentVariable('PATH', [EnvironmentVariableTarget]::Machine); \
    $path = $path + ';C:\dotnet'; \
    [Environment]::SetEnvironmentVariable('PATH', $path, [EnvironmentVariableTarget]::Machine);

# Install living doc CLI
RUN dotnet tool install --global SpecFlow.Plus.LivingDoc.CLI --add-source https://api.nuget.org/v3/index.json --tool-path C:\SpecFlow-LivingDoc-CLI; \
    $new_path = [Environment]::GetEnvironmentVariable('PATH', [EnvironmentVariableTarget]::Machine); \
    $livingdoc_path = $new_path + ';C:\SpecFlow-LivingDoc-CLI'; \
    [Environment]::SetEnvironmentVariable('PATH', $livingdoc_path, [EnvironmentVariableTarget]::Machine);
    
RUN echo [Environment]::GetEnvironmentVariable('PATH', [EnvironmentVariableTarget]::Machine); 