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

using DiKErnel.Core.Data;

namespace DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact
{
    /// <summary>
    /// Construction properties to construct asphalt revetment wave impact time dependent
    /// output.
    /// </summary>
    public class AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties
        : TimeDependentOutputConstructionProperties
    {
        /// <summary>
        /// Gets or sets the log failure tension.
        /// </summary>
        double? LogFailureTension { get; set; }

        /// <summary>
        /// Gets or sets the maximum peak stress.
        /// </summary>
        double? MaximumPeakStress { get; set; }

        /// <summary>
        /// Gets or sets the stiffness relation.
        /// </summary>
        double? StiffnessRelation { get; set; }

        /// <summary>
        /// Gets or sets the computational thickness.
        /// </summary>
        double? ComputationalThickness { get; set; }

        /// <summary>
        /// Gets or sets the equivalent elastic modulus.
        /// </summary>
        double? EquivalentElasticModulus { get; set; }
    }
}