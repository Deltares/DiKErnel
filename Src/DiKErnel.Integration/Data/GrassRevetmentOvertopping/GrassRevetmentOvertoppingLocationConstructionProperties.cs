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

using DiKErnel.Integration.Data.GrassRevetment;

namespace DiKErnel.Integration.Data.GrassRevetmentOvertopping
{
    /// <summary>
    /// Construction properties to construct grass revetment overtopping location dependent
    /// input.
    /// </summary>
    public class GrassRevetmentOvertoppingLocationConstructionProperties : RevetmentLocationConstructionPropertiesBase
    {
        /// <inheritdoc/>
        /// <param name="topLayerType">The type of the top layer.</param>
        public GrassRevetmentOvertoppingLocationConstructionProperties(double x,
                                                                       GrassRevetmentTopLayerType topLayerType)
            : base(x)
        {
            TopLayerType = topLayerType;
        }

        /// <summary>
        /// Gets the type of the top layer.
        /// </summary>
        public GrassRevetmentTopLayerType TopLayerType { get; }

        /// <summary>
        /// Gets or sets the critical cumulative overload.
        /// </summary>
        public double? CriticalCumulativeOverload { get; set; }

        /// <summary>
        /// Gets or sets the critical front velocity.
        /// </summary>
        public double? CriticalFrontVelocity { get; set; }

        /// <summary>
        /// Gets or sets the alpha M coefficient.
        /// </summary>
        public double? IncreasedLoadTransitionAlphaM { get; set; }

        /// <summary>
        /// Gets or sets the alpha S coefficient.
        /// </summary>
        public double? ReducedStrengthTransitionAlphaS { get; set; }

        /// <summary>
        /// Gets or sets the Ctm coefficient.
        /// </summary>
        public double? AverageNumberOfWavesCtm { get; set; }

        /// <summary>
        /// Gets or sets the fixed number of waves.
        /// </summary>
        public int? FixedNumberOfWaves { get; set; }

        /// <summary>
        /// Gets or sets the Cwo coefficient.
        /// </summary>
        public double? FrontVelocityCwo { get; set; }

        /// <summary>
        /// Gets or sets the acceleration alpha A for the crest.
        /// </summary>
        public double? AccelerationAlphaAForCrest { get; set; }

        /// <summary>
        /// Gets or sets the acceleration alpha A for the inner slope.
        /// </summary>
        public double? AccelerationAlphaAForInnerSlope { get; set; }

        /// <summary>
        /// Gets or sets the dike height.
        /// </summary>
        public double? DikeHeight { get; set; }
    }
}