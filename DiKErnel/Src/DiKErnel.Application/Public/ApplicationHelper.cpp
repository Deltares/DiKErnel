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

#include "ApplicationHelper.h"
#include "Version.h"

#include <chrono>

namespace DiKErnel::Application
{
    using namespace std;
    using namespace std::chrono;

    string ApplicationHelper::GetApplicationVersionString()
    {
        return VERSION_STRING;
    }

    string ApplicationHelper::GetOperatingSystemName()
    {
        #ifdef _WIN64
        return "Windows 64-bit";
        #elif _WIN32
        return "Windows 32-bit";
        #elif __APPLE__ || __MACH__
        return "Mac OSX";
        #elif __linux__
        return "Linux";
        #else
        return "Onbekend";
        #endif
    }

    string ApplicationHelper::GetFormattedDateTimeString()
    {
        tm tm{};

        const auto nowAsTime = system_clock::to_time_t(system_clock::now());

        localtime_s(&tm, &nowAsTime);

        char formattedTime[20];

        strftime(formattedTime, sizeof formattedTime, "%FT%TZ", &tm);

        return formattedTime;
    }
}
