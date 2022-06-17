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

#include "AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteTopLayerDefaults.h"

namespace DiKErnel::DomainLibrary
{
    using namespace std;

    double AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteTopLayerDefaults::GetDensityOfWater() const
    {
        return 1025;
    }

    double AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteTopLayerDefaults::GetAverageNumberOfWavesCtm() const
    {
        return 1;
    }

    double AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteTopLayerDefaults::GetFatigueAlpha() const
    {
        return 0.42;
    }

    double AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteTopLayerDefaults::GetFatigueBeta() const
    {
        return 4.76;
    }

    double AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteTopLayerDefaults::GetImpactNumberC() const
    {
        return 1;
    }

    double AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteTopLayerDefaults::GetStiffnessRelationNu() const
    {
        return 0.35;
    }

    const vector<pair<double, double>>& AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteTopLayerDefaults::GetWidthFactors() const
    {
        return _widthFactors;
    }

    const vector<pair<double, double>>& AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteTopLayerDefaults::GetDepthFactors() const
    {
        return _depthFactors;
    }

    const vector<pair<double, double>>& AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteTopLayerDefaults::GetImpactFactors() const
    {
        return _impactFactors;
    }
}
