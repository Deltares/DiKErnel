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

#pragma once

namespace DiKErnel::Integration
{
    class ProfileDataFactorySegment
    {
        public:
            explicit ProfileDataFactorySegment(
                double startPointX,
                double startPointZ,
                double endPointX,
                double endPointZ,
                const double* roughnessCoefficient);

            [[nodiscard]]
            double GetStartPointX() const;

            [[nodiscard]]
            double GetStartPointZ() const;

            [[nodiscard]]
            double GetEndPointX() const;

            [[nodiscard]]
            double GetEndPointZ() const;

            [[nodiscard]]
            const double* GetRoughnessCoefficient() const;

        private:
            double _startPointX;
            double _startPointZ;
            double _endPointX;
            double _endPointZ;
            const double* _roughnessCoefficient;
    };
}
