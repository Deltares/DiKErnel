// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
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

namespace DiKErnel.SpecFlow.Test.Steps.Definitions
{
    internal static class GeneralDefinitions
    {
        public const string LocationDependentOutputWithoutParallelization = "Location dependent output without parallelization";
        public const string LocationDependentOutputWithLocationsInParallel = "Location dependent output with locations in parallel";
        public const string LocationDependentOutputWithTimeStepsInParallel = "Location dependent output with time steps in parallel";
        public const string LocationDependentOutputWithFullParallelization = "Location dependent output with full parallelization";

        public const string NotApplicable = "N.A.";
        public const string CalculationPosition = "Position";

        public const string TopLayerType = "Top layer type";
        public const string FailureNumber = "Failure number";
        public const string InitialDamage = "Initial damage";

        public const string AverageNumberOfWavesCtm = "Factor Ctm";
    }
}