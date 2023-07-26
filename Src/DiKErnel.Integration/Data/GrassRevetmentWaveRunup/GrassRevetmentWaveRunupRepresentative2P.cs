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

namespace DiKErnel.Integration.Data.GrassRevetmentWaveRunup
{
    internal class GrassRevetmentWaveRunupRepresentative2P
    {
        public void GrassRevetmentWaveRunupRepresentative2P(
                double representative2PAru,
                double representative2PBru,
                double representative2PCru,
                double gammab,
                double gammaf);

        public double GetRepresentative2PAru();

        public double GetRepresentative2PBru();

        public double GetRepresentative2PCru();

        public double GetGammab();

        public double GetGammaf();

            private double _representative2PAru;
            private double _representative2PBru;
            private double _representative2PCru;
            private double _gammab;
            private double _gammaf;
    }
}