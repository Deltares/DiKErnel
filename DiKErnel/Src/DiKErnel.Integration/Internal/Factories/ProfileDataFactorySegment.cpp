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

#include "ProfileDataFactorySegment.h"

namespace DiKErnel::Integration
{
    using namespace std;

    ProfileDataFactorySegment::ProfileDataFactorySegment(
        const double startPointX,
        const double startPointZ,
        const double endPointX,
        const double endPointZ,
        unique_ptr<double> roughnessCoefficient)
        : _startPointX(startPointX),
          _startPointZ(startPointZ),
          _endPointX(endPointX),
          _endPointZ(endPointZ),
          _roughnessCoefficient(move(roughnessCoefficient)) { }

    double ProfileDataFactorySegment::GetStartPointX() const
    {
        return _startPointX;
    }

    double ProfileDataFactorySegment::GetStartPointZ() const
    {
        return _startPointZ;
    }

    double ProfileDataFactorySegment::GetEndPointX() const
    {
        return _endPointX;
    }

    double ProfileDataFactorySegment::GetEndPointZ() const
    {
        return _endPointZ;
    }

    const double* ProfileDataFactorySegment::GetRoughnessCoefficient() const
    {
        return _roughnessCoefficient.get();
    }
}
