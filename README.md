# DiKErnel
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=Deltares_DiKErnel&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=Deltares_DiKErnel)

## Contents of Repository

**Build**\
Files for deploying specific parts of the development environment (static code analysis, documentation, etc.).

**Deployment**\
Files for deploying versioned instances of DiKErnel on different platforms (currently only Windows).

**Design**\
UML diagrams that elaborate on the architecture of DiKErnel.

**Development**\
Files for deploying different IDEs (currently only Visual Studio).

**DiKErnel**\
The actual source files and test code of DiKErnel.

**LICENCE**\
The terms under which DiKErnel can be redistributed and/or modified.

**LICENSE-3RD-PARTY**\
A listing of the terms that are shipped with the third party components used by DiKErnel.

## Build

### Requirements
- CMake 3.18 or higher
- A C++17 compatible compiler

### Requirements to build the Gui
- Qt6.3
- Set an environment variable with the name "QT6DIR64" and the path to the Qt installation\
- ![EnvironmentVariableQt](https://user-images.githubusercontent.com/5822688/172304265-6e3120aa-2d8e-4805-9e9b-506f59bb4ea4.png)
- Add the lib and bin folder to the Path variable\
- ![PathVariableQt](https://user-images.githubusercontent.com/5822688/172304423-d277c0ac-366f-4e4b-9d95-672e8731446a.png)

### IDE
To use an IDE, such as Visual Studio:

```powershell
cmake -S .\DiKErnel\ -B .\Development\VisualStudio\ -G "Visual Studio 17 2022" -A x64
cmake --build .\Development\VisualStudio\
cmake --open .\Development\VisualStudio\
```
