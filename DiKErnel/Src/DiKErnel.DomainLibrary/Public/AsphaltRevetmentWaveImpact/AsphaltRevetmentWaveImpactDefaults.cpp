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

#include <tuple>

namespace DiKErnel::DomainLibrary
{
    using namespace std;

    AsphaltRevetmentWaveImpactDefaults::AsphaltRevetmentWaveImpactDefaults()
    {
        _widthFactors = vector<tuple<double, double>>
        {
            tuple<double, double>(0.1, 0.0392),
            tuple<double, double>(0.2, 0.0738),
            tuple<double, double>(0.3, 0.1002),
            tuple<double, double>(0.4, 0.1162),
            tuple<double, double>(0.5, 0.1213),
            tuple<double, double>(0.6, 0.1168),
            tuple<double, double>(0.7, 0.1051),
            tuple<double, double>(0.8, 0.0890),
            tuple<double, double>(0.9, 0.0712),
            tuple<double, double>(1.0, 0.0541),
            tuple<double, double>(1.1, 0.0391),
            tuple<double, double>(1.2, 0.0269),
            tuple<double, double>(1.3, 0.0216),
            tuple<double, double>(1.4, 0.0150),
            tuple<double, double>(1.5, 0.0105)
        };

        _depthFactors = vector<tuple<double, double>>
        {
            tuple<double, double>(-1, 0.0244),
            tuple<double, double>(-0.875, 0.0544),
            tuple<double, double>(-0.750, 0.0938),
            tuple<double, double>(-0.625, 0.1407),
            tuple<double, double>(-0.500, 0.1801),
            tuple<double, double>(-0.375, 0.1632),
            tuple<double, double>(-0.250, 0.1426),
            tuple<double, double>(-0.125, 0.0994),
            tuple<double, double>(0, 0.06),
            tuple<double, double>(0.125, 0.0244),
            tuple<double, double>(0.250, 0.0169)
        };

        _impactFactors = vector<tuple<double, double>>
        {
            tuple<double, double>(2, 0.039),
            tuple<double, double>(2.4, 0.1),
            tuple<double, double>(2.8, 0.18),
            tuple<double, double>(3.2, 0.235),
            tuple<double, double>(3.6, 0.2),
            tuple<double, double>(4.0, 0.13),
            tuple<double, double>(4.4, 0.08),
            tuple<double, double>(4.8, 0.02),
            tuple<double, double>(5.2, 0.01),
            tuple<double, double>(5.6, 0.005),
            tuple<double, double>(6, 0.001)
        };
    }

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
