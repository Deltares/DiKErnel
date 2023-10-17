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

namespace DiKErnel.KernelWrapper.Json.Input.Data.Generic.Definitions
{
    internal static class JsonInputDefinitions
    {
        public const string HydraulicLoads = "hydraulischeBelastingen";
        public const string Locations = "locaties";

        public const string Time = "tijdstippen";
        public const string WaterLevels = "waterstanden";
        public const string WaveHeightsHm0 = "golfhoogtenHm0";
        public const string WavePeriodsTm10 = "golfperiodenTm10";
        public const string WaveDirections = "golfrichtingen";

        public const string DikeProfile = "dijkprofiel";
        public const string DikeOrientation = "dijkorientatie";
        public const string DikeProfilePointsX = "posities";
        public const string DikeProfilePointsZ = "hoogten";
        public const string DikeProfileRoughnessCoefficients = "ruwheidscoefficienten";

        public const string CharacteristicPointTypeOuterToe = "teenBuitenzijde";
        public const string CharacteristicPointTypeOuterCrest = "kruinBuitenzijde";
        public const string CharacteristicPointTypeCrestOuterBerm = "kruinBermBuitenzijde";
        public const string CharacteristicPointTypeNotchOuterBerm = "insteekBermBuitenzijde";
        public const string CharacteristicPointTypeInnerCrest = "kruinBinnenzijde";
        public const string CharacteristicPointTypeInnerToe = "teenBinnenzijde";

        public const string Id = "id";
        public const string X = "positie";
        public const string InitialDamage = "beginschade";
        public const string FailureNumber = "faalgetal";

        public const string CalculationMethods = "rekenmethoden";
        public const string CalculationMethodType = "rekenmethode";

        public const string CalculationMethodTypeAsphaltWaveImpact = "asfaltGolfklap";
        public const string CalculationMethodTypeGrassOvertopping = "grasGolfoverslag";
        public const string CalculationMethodTypeGrassWaveImpact = "grasGolfklap";
        public const string CalculationMethodTypeGrassWaveRunup = "grasGolfoploop";
        public const string CalculationMethodTypeNaturalStone = "natuursteen";

        public const string TopLayers = "toplagen";
        public const string TypeTopLayer = "typeToplaag";

        public const string A = "a";
        public const string B = "b";
        public const string C = "c";

        public const string LoadingArea = "belastingzone";
        public const string UpperLimit = "bovengrens";
        public const string LowerLimit = "ondergrens";

        public const string WaveAngleImpact = "impactGolfhoek";
        public const string BetaMax = "betaMax";

        public const string FactorCtm = "factorCtm";
    }
}