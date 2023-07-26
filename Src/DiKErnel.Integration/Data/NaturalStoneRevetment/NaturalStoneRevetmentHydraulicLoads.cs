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

namespace DiKErnel.Integration.Data.NaturalStoneRevetment
{
    class NaturalStoneRevetmentHydraulicLoads
    {
        public:
            explicit NaturalStoneRevetmentHydraulicLoads(
                double hydraulicLoadAp,
                double hydraulicLoadBp,
                double hydraulicLoadCp,
                double hydraulicLoadNp,
                double hydraulicLoadAs,
                double hydraulicLoadBs,
                double hydraulicLoadCs,
                double hydraulicLoadNs,
                double hydraulicLoadXib);

            [[nodiscard]]
            double GetHydraulicLoadAp() const;

            [[nodiscard]]
            double GetHydraulicLoadBp() const;

            [[nodiscard]]
            double GetHydraulicLoadCp() const;

            [[nodiscard]]
            double GetHydraulicLoadNp() const;

            [[nodiscard]]
            double GetHydraulicLoadAs() const;

            [[nodiscard]]
            double GetHydraulicLoadBs() const;

            [[nodiscard]]
            double GetHydraulicLoadCs() const;

            [[nodiscard]]
            double GetHydraulicLoadNs() const;

            [[nodiscard]]
            double GetHydraulicLoadXib() const;

        private:
            double _hydraulicLoadAp;
            double _hydraulicLoadBp;
            double _hydraulicLoadCp;
            double _hydraulicLoadNp;
            double _hydraulicLoadAs;
            double _hydraulicLoadBs;
            double _hydraulicLoadCs;
            double _hydraulicLoadNs;
            double _hydraulicLoadXib;
    };
}
