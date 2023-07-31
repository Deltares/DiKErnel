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

using DiKErnel.Integration.Data.GrassRevetment;

namespace DiKErnel.Integration.Data.GrassRevetmentWaveRunup
{
    /// <summary>
    /// Construction properties to construct grass revetment wave run-up location dependent
    /// input.
    /// </summary>
    public abstract class GrassRevetmentWaveRunupLocationConstructionProperties
        : RevetmentLocationConstructionPropertiesBase

    {
        /// <inheritdoc/>
        /// <param name="outerSlope">The outer slope.</param>
        /// <param name="topLayerType">The type of the top layer.</param>
        protected GrassRevetmentWaveRunupLocationConstructionProperties(double x, double outerSlope,
                                                                        GrassRevetmentTopLayerType topLayerType)
            : base(x)
        {
            OuterSlope = outerSlope;
            TopLayerType = topLayerType;
        }

        /// <summary>
        /// Gets the outer slope.
        /// </summary>
        public double OuterSlope { get; }

        /// <summary>
        /// Gets the type of the top layer.
        /// </summary>
        public GrassRevetmentTopLayerType TopLayerType { get; }

        /// <summary>
        /// Gets or sets the critical cumulative overload.
        /// </summary>
        public double? SetCriticalCumulativeOverload { get; set; }

        /// <summary>
        /// Gets or sets the critical front velocity.
        /// </summary>
        public double? SetCriticalFrontVelocity { get; set; }

        /// <summary>
        /// Gets or sets the alpha M coefficient.
        /// </summary>
        public double? SetIncreasedLoadTransitionAlphaM { get; set; }

        /// <summary>
        /// Gets or sets the alpha S coefficient.
        /// </summary>
        public double? SetReducedStrengthTransitionAlphaS { get; set; }

        /// <summary>
        /// Gets or sets the Ctm coefficient.
        /// </summary>
        public double? SetAverageNumberOfWavesCtm { get; set; }

        /// <summary>
        /// Gets or sets the 2P Aru coefficient.
        /// </summary>
        public double? SetRepresentativeWaveRunup2PAru { get; set; }

        /// <summary>
        /// Gets or sets the 2P Bru coefficient.
        /// </summary>
        public double? SetRepresentativeWaveRunup2PBru { get; set; }

        /// <summary>
        /// Gets or sets the 2P Cru coefficient.
        /// </summary>
        public double? SetRepresentativeWaveRunup2PCru { get; set; }

        /// <summary>
        /// Gets or sets the 2P Gammab coefficient.
        /// </summary>
        public double? SetRepresentativeWaveRunup2PGammab { get; set; }

        /// <summary>
        /// Gets or sets the 2P Gammaf coefficient.
        /// </summary>
        public double? SetRepresentativeWaveRunup2PGammaf { get; set; }

        /// <summary>
        /// Gets or sets the Abeta coefficient.
        /// </summary>
        public double? SetWaveAngleImpactAbeta { get; set; }

        /// <summary>
        /// Gets or sets the Betamax coefficient.
        /// </summary>
        public double? SetWaveAngleImpactBetamax { get; set; }
    }
}