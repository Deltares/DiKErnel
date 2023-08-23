﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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

using DiKErnel.Core.Data;
using DiKErnel.Core.Exceptions;

namespace DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact
{
    /// <summary>
    /// Time dependent output of an asphalt revetment wave impact location.
    /// </summary>
    public class AsphaltRevetmentWaveImpactTimeDependentOutput : TimeDependentOutput
    {
        /// <inheritdoc/>
        public AsphaltRevetmentWaveImpactTimeDependentOutput(
            AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties)
            : base(constructionProperties)
        {
            LogFailureTension = constructionProperties.IncrementDamage
                                ?? throw new InvalidTimeDependentOutputException(
                                    nameof(constructionProperties.LogFailureTension));
            MaximumPeakStress = constructionProperties.MaximumPeakStress
                                ?? throw new InvalidTimeDependentOutputException(
                                    nameof(constructionProperties.MaximumPeakStress));
            StiffnessRelation = constructionProperties.StiffnessRelation
                                ?? throw new InvalidTimeDependentOutputException(
                                    nameof(constructionProperties.StiffnessRelation));
            ComputationalThickness = constructionProperties.ComputationalThickness
                                     ?? throw new InvalidTimeDependentOutputException(
                                         nameof(constructionProperties.ComputationalThickness));
            EquivalentElasticModulus = constructionProperties.EquivalentElasticModulus
                                       ?? throw new InvalidTimeDependentOutputException(
                                           nameof(constructionProperties.EquivalentElasticModulus));
        }

        /// <summary>
        /// Gets the log failure tension.
        /// </summary>
        public double LogFailureTension { get; }

        /// <summary>
        /// Gets the maximum peak stress.
        /// </summary>
        public double MaximumPeakStress { get; }

        /// <summary>
        /// Gets the stiffness relation.
        /// </summary>
        public double StiffnessRelation { get; }

        /// <summary>
        /// Gets the computational thickness.
        /// </summary>
        public double ComputationalThickness { get; }

        /// <summary>
        /// Gets the equivalent elastic modulus.
        /// </summary>
        public double EquivalentElasticModulus { get; }
    }
}