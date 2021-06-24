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
        : _widthFactors(vector<tuple<double, double>>()),
          _depthFactors(vector<tuple<double, double>>()),
          _impactFactors(vector<tuple<double, double>>())
    {
        _widthFactors.emplace_back(0.1, 0.0392);
        _widthFactors.emplace_back(0.2, 0.0738);
        _widthFactors.emplace_back(0.3, 0.1002);
        _widthFactors.emplace_back(0.4, 0.1162);
        _widthFactors.emplace_back(0.5, 0.1213);
        _widthFactors.emplace_back(0.6, 0.1168);
        _widthFactors.emplace_back(0.7, 0.1051);
        _widthFactors.emplace_back(0.8, 0.0890);
        _widthFactors.emplace_back(0.9, 0.0712);
        _widthFactors.emplace_back(1.0, 0.0541);
        _widthFactors.emplace_back(1.1, 0.0391);
        _widthFactors.emplace_back(1.2, 0.0269);
        _widthFactors.emplace_back(1.3, 0.0216);
        _widthFactors.emplace_back(1.4, 0.0150);
        _widthFactors.emplace_back(1.5, 0.0105);

        _depthFactors.emplace_back(-1.0, 0.0244);
        _depthFactors.emplace_back(-0.875, 0.0544);
        _depthFactors.emplace_back(-0.750, 0.0938);
        _depthFactors.emplace_back(-0.625, 0.1407);
        _depthFactors.emplace_back(-0.500, 0.1801);
        _depthFactors.emplace_back(-0.375, 0.1632);
        _depthFactors.emplace_back(-0.250, 0.1426);
        _depthFactors.emplace_back(-0.125, 0.0994);
        _depthFactors.emplace_back(0.0, 0.06);
        _depthFactors.emplace_back(0.125, 0.0244);
        _depthFactors.emplace_back(0.250, 0.0169);

        _impactFactors.emplace_back(2.0, 0.039);
        _impactFactors.emplace_back(2.4, 0.1);
        _impactFactors.emplace_back(2.8, 0.18);
        _impactFactors.emplace_back(3.2, 0.235);
        _impactFactors.emplace_back(3.6, 0.2);
        _impactFactors.emplace_back(4.0, 0.13);
        _impactFactors.emplace_back(4.4, 0.08);
        _impactFactors.emplace_back(4.8, 0.02);
        _impactFactors.emplace_back(5.2, 0.01);
        _impactFactors.emplace_back(5.6, 0.005);
        _impactFactors.emplace_back(6.0, 0.001);
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
