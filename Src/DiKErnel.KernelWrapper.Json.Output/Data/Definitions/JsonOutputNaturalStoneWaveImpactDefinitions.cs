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

namespace DiKErnel.KernelWrapper.Json.Output.Data.Definitions
{
    internal static class JsonOutputNaturalStoneWaveImpactDefinitions
    {
        public const string SlopeUpperLevel = "bovenzijdeHellingvlak";
        public const string SlopeUpperPosition = "rechterzijdeHellingvlak";
        public const string SlopeLowerLevel = "onderzijdeHellingvlak";
        public const string SlopeLowerPosition = "linkerzijdeHellingvlak";

        public const string SurfSimilarityParameter = "golfbrekingparameter";
        public const string WaveSteepnessDeepWater = "golfsteilheidDiepWater";

        public const string DepthMaximumWaveLoad = "diepteMaximaleGolfbelasting";
        public const string DistanceMaximumWaveElevation = "afstandMaximaleStijghoogte";
        public const string NormativeWidthWaveImpact = "maatgevendeBreedteGolfklap";
        public const string HydraulicLoad = "hydraulischeBelasting";
        public const string Resistance = "sterkteBekleding";
        public const string ReferenceTimeDegradation = "referentietijdDegradatie";
        public const string ReferenceDegradation = "referentieDegradatie";
    }
}