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
  ![Qt environment variable](https://tscscreencastlive.blob.core.windows.net/uploads/g000301kys7AqXKZzJkWpsHDy4iDK/LWR_Recording.png?sv=2019-07-07&sr=b&sig=UPMpvmgI6FnQJw6yy%2FqSCCHcdGVTQv5pU%2FjK40l64WU%3D&st=2022-06-07T05%3A00%3A54Z&se=2022-06-08T05%3A05%3A54Z&sp=r)
- Add the lib and bin folder to the Path variable\
  ![Path variable](https://tscscreencastlive.blob.core.windows.net/uploads/g0003017qq7yNYv130mjO7GwPNAHR/LWR_Recording.png?sv=2019-07-07&sr=b&sig=D2MuJluxNsTv4%2FPNs9v%2BHycQktdCYzjD7Z1WuHZM7Ys%3D&st=2022-06-07T05%3A11%3A38Z&se=2022-06-08T05%3A16%3A38Z&sp=r)

### IDE
To use an IDE, such as Visual Studio:

```powershell
cmake -S .\DiKErnel\ -B .\Development\VisualStudio\ -G "Visual Studio 17 2022" -A x64
cmake --build .\Development\VisualStudio\
cmake --open .\Development\VisualStudio\
```