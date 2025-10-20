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

namespace DiKErnel.FunctionLibrary.AsphaltWaveImpact
{
    /// <summary>
    /// Input for the asphalt wave impact calculations.
    /// </summary>
    public class AsphaltWaveImpactInput
    {
        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="logFlexuralStrength">The logarithm of the flexural
        /// strength [MPa].</param>
        /// <param name="averageNumberOfWaves">The average number of waves [-].</param>
        /// <param name="maximumPeakStress">The maximum peak stress [MPa].</param>
        /// <param name="stiffnessRelation">The stiffness relation [m^-1].</param>
        /// <param name="computationalThickness">The computational thickness [m].</param>
        /// <param name="outerSlope">The outer slope [-].</param>
        /// <param name="widthFactors">The width factors [-].</param>
        /// <param name="depthFactors">The depth factors [-].</param>
        /// <param name="impactFactors">The impact factors [-].</param>
        /// <param name="z">The z coordinate [m].</param>
        /// <param name="waterLevel">The water level [m].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="fatigueAlpha">The fatigue alpha coefficient [-].</param>
        /// <param name="fatigueBeta">The fatigue beta coefficient [-].</param>
        /// <param name="impactNumberC">The impact number c coefficient [-].</param>
        public AsphaltWaveImpactInput(double logFlexuralStrength, double averageNumberOfWaves, double maximumPeakStress,
                                      double stiffnessRelation, double computationalThickness, double outerSlope,
                                      IReadOnlyList<(double, double)> widthFactors,
                                      IReadOnlyList<(double, double)> depthFactors,
                                      IReadOnlyList<(double, double)> impactFactors,
                                      double z, double waterLevel, double waveHeightHm0, double fatigueAlpha,
                                      double fatigueBeta, double impactNumberC)
        {
            LogFlexuralStrength = logFlexuralStrength;
            AverageNumberOfWaves = averageNumberOfWaves;
            MaximumPeakStress = maximumPeakStress;
            StiffnessRelation = stiffnessRelation;
            ComputationalThickness = computationalThickness;
            OuterSlope = outerSlope;
            WidthFactors = widthFactors;
            DepthFactors = depthFactors;
            ImpactFactors = impactFactors;
            Z = z;
            WaterLevel = waterLevel;
            WaveHeightHm0 = waveHeightHm0;
            FatigueAlpha = fatigueAlpha;
            FatigueBeta = fatigueBeta;
            ImpactNumberC = impactNumberC;
        }

        /// <summary>
        /// Gets the logarithm of the flexural strength [MPa].
        /// </summary>
        public double LogFlexuralStrength { get; }

        /// <summary>
        /// Gets the average number of waves [-].
        /// </summary>
        public double AverageNumberOfWaves { get; }

        /// <summary>
        /// Gets the maximum peak stress [MPa].
        /// </summary>
        public double MaximumPeakStress { get; }

        /// <summary>
        /// Gets the stiffness relation [m^-1].
        /// </summary>
        public double StiffnessRelation { get; }

        /// <summary>
        /// Gets the computational thickness [m].
        /// </summary>
        public double ComputationalThickness { get; }

        /// <summary>
        /// Gets the outer slope [-].
        /// </summary>
        public double OuterSlope { get; }

        /// <summary>
        /// Gets the width factors [-].
        /// </summary>
        public IReadOnlyList<(double, double)> WidthFactors { get; }

        /// <summary>
        /// Gets the depth factors [-].
        /// </summary>
        public IReadOnlyList<(double, double)> DepthFactors { get; }

        /// <summary>
        /// Gets the impact factors [-].
        /// </summary>
        public IReadOnlyList<(double, double)> ImpactFactors { get; }

        /// <summary>
        /// Gets the z coordinate [m].
        /// </summary>
        public double Z { get; }

        /// <summary>
        /// Gets the water level [m].
        /// </summary>
        public double WaterLevel { get; }

        /// <summary>
        /// Gets the wave height [m].
        /// </summary>
        public double WaveHeightHm0 { get; }

        /// <summary>
        /// Gets the fatigue alpha coefficient [-].
        /// </summary>
        public double FatigueAlpha { get; }

        /// <summary>
        /// Gets the fatigue beta coefficient [-].
        /// </summary>
        public double FatigueBeta { get; }

        /// <summary>
        /// Gets the impact number c coefficient [-].
        /// </summary>
        public double ImpactNumberC { get; }
    }
}