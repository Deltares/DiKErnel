# syntax=docker/dockerfile:1

FROM mcr.microsoft.com/windows/servercore:ltsc2022

# Set powershell as default shell
SHELL ["powershell", "-Command", "$ErrorActionPreference = 'Stop'; $ProgressPreference = 'SilentlyContinue';"]

RUN Invoke-WebRequest -Uri https://dot.net/v1/dotnet-install.ps1 -OutFile dotnet-install.ps1 -UseBasicParsing; \
    .\dotnet-install.ps1 -Version 7.0.304 -Architecture x86 -InstallDir C:\dotnet; \
    Remove-Item -Force dotnet-install.ps1; \
    $path = [Environment]::GetEnvironmentVariable('PATH', [EnvironmentVariableTarget]::Machine); \
    $path = $path + ';C:\dotnet'; \
    [Environment]::SetEnvironmentVariable('PATH', $path, [EnvironmentVariableTarget]::Machine);