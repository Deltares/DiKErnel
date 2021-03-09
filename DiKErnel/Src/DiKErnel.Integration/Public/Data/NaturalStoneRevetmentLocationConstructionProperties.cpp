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

#include "NaturalStoneRevetmentLocationConstructionProperties.h"

namespace DiKErnel::Integration
{
    using namespace std;

    NaturalStoneRevetmentLocationConstructionProperties::NaturalStoneRevetmentLocationConstructionProperties(
        const double initialDamage,
        const double slopeAngle,
        const double thicknessTopLayer)
        : _initialDamage(initialDamage),
          _slopeAngle(slopeAngle),
          _thicknessTopLayer(thicknessTopLayer) { }

    void NaturalStoneRevetmentLocationConstructionProperties::SetRelativeDensity(
        unique_ptr<double> relativeDensity)
    {
        _relativeDensity = move(relativeDensity);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetPlungingCoefficientA(
        unique_ptr<double> plungingCoefficientA)
    {
        _plungingCoefficientA = move(plungingCoefficientA);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetPlungingCoefficientB(
        unique_ptr<double> plungingCoefficientB)
    {
        _plungingCoefficientB = move(plungingCoefficientB);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetPlungingCoefficientC(
        unique_ptr<double> plungingCoefficientC)
    {
        _plungingCoefficientC = move(plungingCoefficientC);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetPlungingCoefficientN(
        unique_ptr<double> plungingCoefficientN)
    {
        _plungingCoefficientN = move(plungingCoefficientN);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetSurgingCoefficientA(
        unique_ptr<double> surgingCoefficientA)
    {
        _surgingCoefficientA = move(surgingCoefficientA);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetSurgingCoefficientB(
        unique_ptr<double> surgingCoefficientB)
    {
        _surgingCoefficientB = move(surgingCoefficientB);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetSurgingCoefficientC(
        unique_ptr<double> surgingCoefficientC)
    {
        _surgingCoefficientC = move(surgingCoefficientC);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetSurgingCoefficientN(
        unique_ptr<double> surgingCoefficientN)
    {
        _surgingCoefficientN = move(surgingCoefficientN);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetSimilarityParameterThreshold(
        unique_ptr<double> similarityParameterThreshold)
    {
        _similarityParameterThreshold = move(similarityParameterThreshold);
    }

    double NaturalStoneRevetmentLocationConstructionProperties::GetInitialDamage() const
    {
        return _initialDamage;
    }

    double NaturalStoneRevetmentLocationConstructionProperties::GetSlopeAngle() const
    {
        return _slopeAngle;
    }

    double NaturalStoneRevetmentLocationConstructionProperties::GetThicknessTopLayer() const
    {
        return _thicknessTopLayer;
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetRelativeDensity() const
    {
        return _relativeDensity.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetPlungingCoefficientA() const
    {
        return _plungingCoefficientA.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetPlungingCoefficientB() const
    {
        return _plungingCoefficientB.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetPlungingCoefficientC() const
    {
        return _plungingCoefficientC.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetPlungingCoefficientN() const
    {
        return _plungingCoefficientN.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetSurgingCoefficientA() const
    {
        return _surgingCoefficientA.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetSurgingCoefficientB() const
    {
        return _surgingCoefficientB.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetSurgingCoefficientC() const
    {
        return _surgingCoefficientC.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetSurgingCoefficientN() const
    {
        return _surgingCoefficientN.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetSimilarityParameterThreshold() const
    {
        return _similarityParameterThreshold.get();
    }
}
