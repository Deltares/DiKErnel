// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

namespace DiKErnel.Integration.Data.GrassRevetmentWaveRunup
{
    internal class GrassRevetmentWaveRunupRepresentative2P
    {
        public GrassRevetmentWaveRunupRepresentative2P(double representative2PAru, double representative2PBru,
                                                       double representative2PCru, double gammab, double gammaf)
        {
            Representative2PAru = representative2PAru;
            Representative2PBru = representative2PBru;
            Representative2PCru = representative2PCru;
            Gammab = gammab;
            Gammaf = gammaf;
        }

        public double Representative2PAru { get; }

        public double Representative2PBru { get; }

        public double Representative2PCru { get; }

        public double Gammab { get; }

        public double Gammaf { get; }
    }
}