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

#include "AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteDefaults.h"

namespace DiKErnel::DomainLibrary
{
    using namespace std;

    double AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteDefaults::GetDensityOfWater() const
    {
        return 1025;
    }

    double AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteDefaults::GetAverageNumberOfWavesCtm() const
    {
        return 1;
    }

    double AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteDefaults::GetFatigueAlpha() const
    {
        return 0.42;
    }

    double AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteDefaults::GetFatigueBeta() const
    {
        return 4.76;
    }

    double AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteDefaults::GetImpactNumberC() const
    {
        return 1;
    }

    double AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteDefaults::GetStiffnessRelationNu() const
    {
        return 0.35;
    }

    const vector<pair<double, double>>& AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteDefaults::GetWidthFactors() const
    {
        return _widthFactors;
    }

    const vector<pair<double, double>>& AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteDefaults::GetDepthFactors() const
    {
        return _depthFactors;
    }

    const vector<pair<double, double>>& AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteDefaults::GetImpactFactors() const
    {
        return _impactFactors;
    }
}
