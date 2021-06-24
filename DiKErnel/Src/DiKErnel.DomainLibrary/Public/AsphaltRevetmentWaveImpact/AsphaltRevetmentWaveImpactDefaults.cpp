// Copyright (C) Stichting Deltares 2020. All rights reserved.
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

#include "AsphaltRevetmentWaveImpactDefaults.h"

namespace DiKErnel::DomainLibrary
{
    using namespace std;

    double AsphaltRevetmentWaveImpactDefaults::GetSubLayerThickness() const
    {
        return 0;
    }

    double AsphaltRevetmentWaveImpactDefaults::GetAverageNumberOfWavesCtm() const
    {
        return 1;
    }

    double AsphaltRevetmentWaveImpactDefaults::GetFatigueAlpha() const
    {
        return 0.42;
    }

    double AsphaltRevetmentWaveImpactDefaults::GetFatigueBeta() const
    {
        return 4.76;
    }

    double AsphaltRevetmentWaveImpactDefaults::GetImpactNumberC() const
    {
        return 1;
    }

    double AsphaltRevetmentWaveImpactDefaults::GetStiffnessRelationNu() const
    {
        return 0.35;
    }

    const vector<tuple<double, double>>& AsphaltRevetmentWaveImpactDefaults::GetWidthFactors() const
    {
        return _widthFactors;
    }

    const vector<tuple<double, double>>& AsphaltRevetmentWaveImpactDefaults::GetDepthFactors() const
    {
        return _depthFactors;
    }

    const vector<tuple<double, double>>& AsphaltRevetmentWaveImpactDefaults::GetImpactFactors() const
    {
        return _impactFactors;
    }
}
