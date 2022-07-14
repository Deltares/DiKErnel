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

#include "AsphaltRevetmentWaveImpactFunctionsInput.h"

#include <utility>

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    AsphaltRevetmentWaveImpactFunctionsInput::AsphaltRevetmentWaveImpactFunctionsInput(
        const double z,
        const vector<pair<double, double>>& widthFactors,
        const vector<pair<double, double>>& depthFactors,
        const vector<pair<double, double>>& impactFactors,
        const double fatigueAlpha,
        const double fatigueBeta,
        const double impactNumberC)
        : _z(z),
          _widthFactors(widthFactors),
          _depthFactors(depthFactors),
          _impactFactors(impactFactors),
          _fatigueAlpha(fatigueAlpha),
          _fatigueBeta(fatigueBeta),
          _impactNumberC(impactNumberC) { }

    void AsphaltRevetmentWaveImpactFunctionsInput::SetWaterLevel(
        const double waterLevel)
    {
        _waterLevel = waterLevel;
    }

    void AsphaltRevetmentWaveImpactFunctionsInput::SetWaveHeightHm0(
        const double waveHeightHm0)
    {
        _waveHeightHm0 = waveHeightHm0;
    }

    double AsphaltRevetmentWaveImpactFunctionsInput::GetZ() const
    {
        return _z;
    }

    const vector<pair<double, double>>& AsphaltRevetmentWaveImpactFunctionsInput::GetWidthFactors() const
    {
        return _widthFactors;
    }

    const vector<pair<double, double>>& AsphaltRevetmentWaveImpactFunctionsInput::GetDepthFactors() const
    {
        return _depthFactors;
    }

    const vector<pair<double, double>>& AsphaltRevetmentWaveImpactFunctionsInput::GetImpactFactors() const
    {
        return _impactFactors;
    }

    double AsphaltRevetmentWaveImpactFunctionsInput::GetFatigueAlpha() const
    {
        return _fatigueAlpha;
    }

    double AsphaltRevetmentWaveImpactFunctionsInput::GetFatigueBeta() const
    {
        return _fatigueBeta;
    }

    double AsphaltRevetmentWaveImpactFunctionsInput::GetImpactNumberC() const
    {
        return _impactNumberC;
    }

    double AsphaltRevetmentWaveImpactFunctionsInput::GetWaterLevel() const
    {
        return _waterLevel;
    }

    double AsphaltRevetmentWaveImpactFunctionsInput::GetWaveHeightHm0() const
    {
        return _waveHeightHm0;
    }
}
