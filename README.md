# DiKErnel
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=Deltares_DiKErnel&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=Deltares_DiKErnel)

## Contents of repository

**Development**\
Files for deploying specific parts of the development environment.

**Dependencies**\
Libraries used in the repository that are not consumed via NuGet.

**Deployment**\
Files for specifying the deployment environment.

**Licenses**\
Full license texts of the libraries used in the repository.

**Src**\
The source code files of DiKErnel.

**Test**\
The test code files of DiKErnel.

**DEPENDENCIES.md**\
Overview of the libraries used in the repository.

**LICENSE**\
The terms under which DiKErnel can be redistributed and/or modified.

## Build

### Requirements for building
- Microsoft Visual Studio 2022 (build tools)
- .NET7 SDK

### Requirements for running
- .NET7 runtime
- Microsoft Visual C++ Redistributable 2022

```mermaid
classDiagram
Class01 <|-- AveryLongClass : Cool
Class03 *-- Class04
Class05 o-- Class06
Class07 .. Class08
Class09 --> C2 : Where am i?
Class09 --* C3
Class09 --|> Class07
Class07 : equals()
Class07 : Object[] elementData
Class01 : size()
Class01 : int chimp
Class01 : int gorilla
Class08 <--> C2: Cool label
```