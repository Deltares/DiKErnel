// Copyright (C) Stichting Deltares 2022. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#include <filesystem>
#include <iostream>
using namespace std;

#pragma region Forward declarations

string GetLogOutputFilePath(
    const string& jsonOutputFilePath);

#pragma endregion

int main(
    int argc,
    char* argv[])
{
    if(argc != 3)
    {
        cout << "You have entered an invalid number of arguments." << endl;
        return 0;
    }

    const string jsonInputFilePath(argv[1]);
    const string jsonOutputFilePath(argv[2]);
    const auto logOutputFilePath = GetLogOutputFilePath(jsonOutputFilePath);

    return 0;
}

string GetLogOutputFilePath(
    const string& jsonOutputFilePath)
{
    const auto outputFilePath = filesystem::path(jsonOutputFilePath);
    const auto outputDirectory = outputFilePath.parent_path();
    const auto outputFileName = outputFilePath.stem().u8string();

    return (outputDirectory / (outputFileName + ".log")).u8string();
}
