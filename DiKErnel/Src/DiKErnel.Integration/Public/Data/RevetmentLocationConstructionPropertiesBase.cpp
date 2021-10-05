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

#include "RevetmentLocationConstructionPropertiesBase.h"

namespace DiKErnel::Integration
{
    using namespace std;

    RevetmentLocationConstructionPropertiesBase::RevetmentLocationConstructionPropertiesBase(
        string name,
        const double x,
        const double positionZ)
        : _name(move(name)),
          _x(x),
          _positionZ(positionZ) { }

    void RevetmentLocationConstructionPropertiesBase::SetInitialDamage(
        unique_ptr<double> initialDamage)
    {
        _initialDamage = move(initialDamage);
    }

    void RevetmentLocationConstructionPropertiesBase::SetFailureNumber(
        unique_ptr<double> failureNumber)
    {
        _failureNumber = move(failureNumber);
    }

    string RevetmentLocationConstructionPropertiesBase::GetName() const
    {
        return _name;
    }

    double RevetmentLocationConstructionPropertiesBase::GetX() const
    {
        return _x;
    }

    double RevetmentLocationConstructionPropertiesBase::GetPositionZ() const
    {
        return _positionZ;
    }

    const double* RevetmentLocationConstructionPropertiesBase::GetInitialDamage() const
    {
        return _initialDamage.get();
    }

    const double* RevetmentLocationConstructionPropertiesBase::GetFailureNumber() const
    {
        return _failureNumber.get();
    }
}
