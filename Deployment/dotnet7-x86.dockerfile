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
RUN dotnet tool install --global SpecFlow.Plus.LivingDoc.CLI --add-source https://api.nuget.org/v3/index.json \
    $tool_path = [Environment]::Getfolderpath("USERPROFILE") + '\.dotnet\tools' \
    $path = [Environment]::GetEnvironmentVariable('PATH', [EnvironmentVariableTarget]::Machine); \
    $path = $path + ';' + $tool_path; \
    [Environment]::SetEnvironmentVariable('PATH', $path, [EnvironmentVariableTarget]::Machine);