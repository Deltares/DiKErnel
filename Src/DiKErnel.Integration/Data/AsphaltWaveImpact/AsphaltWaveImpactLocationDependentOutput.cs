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

using System.Collections.Generic;
using DiKErnel.Core.Data;

namespace DiKErnel.Integration.Data.AsphaltWaveImpact
{
    /// <summary>
    /// Location dependent output of an asphalt wave impact calculation.
    /// </summary>
    public class AsphaltWaveImpactLocationDependentOutput : LocationDependentOutput
    {
        /// <inheritdoc/>
        /// <param name="z">The calculated z.</param>
        /// <param name="outerSlope">The calculated outer slope.</param>
        /// <param name="logFlexuralStrength">The calculated log flexural strength.</param>
        /// <param name="stiffnessRelation">The calculated stiffness relation.</param>
        /// <param name="computationalThickness">The calculated computational thickness.</param>
        /// <param name="equivalentElasticModulus">The calculated equivalent elastic modulus.</param>
        public AsphaltWaveImpactLocationDependentOutput(double initialDamage, double failureNumber,
                                                        IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                                        IReadOnlyList<TimeDependentOutput> timeDependentOutputItems, double z,
                                                        double outerSlope, double logFlexuralStrength, double stiffnessRelation,
                                                        double computationalThickness, double equivalentElasticModulus)
            : base(initialDamage, failureNumber, timeDependentInputItems, timeDependentOutputItems)
        {
            Z = z;
            OuterSlope = outerSlope;
            LogFlexuralStrength = logFlexuralStrength;
            StiffnessRelation = stiffnessRelation;
            ComputationalThickness = computationalThickness;
            EquivalentElasticModulus = equivalentElasticModulus;
        }

        /// <summary>
        /// Gets the calculated z.
        /// </summary>
        public double Z { get; }

        /// <summary>
        /// Gets the calculated outer slope.
        /// </summary>
        public double OuterSlope { get; }

        /// <summary>
        /// Gets the calculated log flexural strength.
        /// </summary>
        public double LogFlexuralStrength { get; }

        /// <summary>
        /// Gets the calculated stiffness relation.
        /// </summary>
        public double StiffnessRelation { get; }

        /// <summary>
        /// Gets the calculated computational thickness.
        /// </summary>
        public double ComputationalThickness { get; }

        /// <summary>
        /// Gets the calculated equivalent elastic modulus.
        /// </summary>
        public double EquivalentElasticModulus { get; }
    }
}