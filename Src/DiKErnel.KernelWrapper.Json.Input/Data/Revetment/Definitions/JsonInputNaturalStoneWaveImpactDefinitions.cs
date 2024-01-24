// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

namespace DiKErnel.KernelWrapper.Json.Input.Data.Revetment.Definitions
{
    internal static class JsonInputNaturalStoneWaveImpactDefinitions
    {
        public const string TopLayerTypeNordicStone = "noorseSteen";

        public const string RelativeDensity = "relatieveDichtheid";
        public const string ThicknessTopLayer = "dikteToplaag";

        public const string Stability = "stabiliteit";
        public const string StabilityPlunging = "plunging";
        public const string StabilitySurging = "surging";

        public const string N = "n";
        public const string Xib = "xib";

        public const string Slope = "hellingvlak";
        public const string SlopeUpperLevel = "bovenzijde";
        public const string SlopeLowerLevel = "onderzijde";

        public const string DistanceMaximumWaveElevation = "afstandMaximaleStijghoogte";

        public const string NormativeWidthOfWaveImpact = "maatgevendeBreedteGolfklap";

        public const string BetaMax = "betaMax";
    }
}