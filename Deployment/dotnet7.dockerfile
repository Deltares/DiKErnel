FROM mcr.microsoft.com/windows/servercore:ltsc2022

ARG architecture

SHELL ["powershell", "-Command", "$ErrorActionPreference = 'Stop'; $ProgressPreference = 'SilentlyContinue';"]

RUN Set-ExecutionPolicy Bypass -Scope Process -Force; \
    $installVCRedistScript = ((New-Object System.Net.WebClient).DownloadString('https://vcredist.com/install.ps1')); \
    Invoke-Command -ScriptBlock ([scriptblock]::Create($installVCRedistScript));

RUN $dotNetPath = 'C:\dotnet'; \
    $specFlowLivingDocPath = 'C:\SpecFlow-LivingDoc-CLI'; \
    $installDotnet = ((New-Object System.Net.WebClient).DownloadString('https://dot.net/v1/dotnet-install.ps1')); \
    & ([scriptblock]::Create($installDotnet)) -Version 7.0.406 -Architecture $env:architecture -InstallDir ${dotNetPath}; \
    & ${dotNetPath}\dotnet tool install SpecFlow.Plus.LivingDoc.CLI --add-source https://api.nuget.org/v3/index.json --tool-path ${specFlowLivingDocPath}; \
    $path = [Environment]::GetEnvironmentVariable('PATH', [EnvironmentVariableTarget]::Machine); \
    $path += ';' + ${dotNetPath} + ';' + ${specFlowLivingDocPath}; \
    [Environment]::SetEnvironmentVariable('PATH', ${path}, [EnvironmentVariableTarget]::Machine); \
    [Environment]::SetEnvironmentVariable('DOTNET_ROOT', ${dotNetPath}, [EnvironmentVariableTarget]::Machine);