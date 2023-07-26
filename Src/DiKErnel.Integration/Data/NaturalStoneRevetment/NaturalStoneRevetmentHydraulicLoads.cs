// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

namespace DiKErnel.Integration.Data.NaturalStoneRevetment
{
    class NaturalStoneRevetmentHydraulicLoads
    {
        public void NaturalStoneRevetmentHydraulicLoads(
                double hydraulicLoadAp,
                double hydraulicLoadBp,
                double hydraulicLoadCp,
                double hydraulicLoadNp,
                double hydraulicLoadAs,
                double hydraulicLoadBs,
                double hydraulicLoadCs,
                double hydraulicLoadNs,
                double hydraulicLoadXib);

        public double GetHydraulicLoadAp() const;

        public double GetHydraulicLoadBp() const;

        public double GetHydraulicLoadCp() const;

        public double GetHydraulicLoadNp() const;

        public double GetHydraulicLoadAs() const;

        public double GetHydraulicLoadBs() const;

        public double GetHydraulicLoadCs() const;

        public double GetHydraulicLoadNs() const;

        public double GetHydraulicLoadXib() const;

            private double _hydraulicLoadAp;
            private double _hydraulicLoadBp;
            private double _hydraulicLoadCp;
            private double _hydraulicLoadNp;
            private double _hydraulicLoadAs;
            private double _hydraulicLoadBs;
            private double _hydraulicLoadCs;
            private double _hydraulicLoadNs;
            private double _hydraulicLoadXib;
    };
}
