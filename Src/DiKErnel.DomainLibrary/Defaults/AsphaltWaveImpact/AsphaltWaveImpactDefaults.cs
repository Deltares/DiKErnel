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

namespace DiKErnel.DomainLibrary.Defaults.AsphaltWaveImpact
{
    /// <summary>
    /// Class that contains default values for asphalt wave impact calculations.
    /// </summary>
    public static class AsphaltWaveImpactDefaults
    {
        /// <summary>
        /// Gets the default value of the density of water [kg/m^3].
        /// </summary>
        public static double DensityOfWater => 1025;

        /// <summary>
        /// Gets the default value of the Ctm coefficient [-].
        /// </summary>
        public static double AverageNumberOfWavesCtm => 1;

        /// <summary>
        /// Gets the default value of the impact number C coefficient [-].
        /// </summary>
        public static double ImpactNumberC => 1;

        /// <summary>
        /// Gets the default values of the width factors [-].
        /// </summary>
        public static IReadOnlyList<(double, double)> WidthFactors => new[]
        {
            (0.1, 0.0392),
            (0.2, 0.0738),
            (0.3, 0.1002),
            (0.4, 0.1162),
            (0.5, 0.1213),
            (0.6, 0.1168),
            (0.7, 0.1051),
            (0.8, 0.089),
            (0.9, 0.0712),
            (1, 0.0541),
            (1.1, 0.0391),
            (1.2, 0.0269),
            (1.3, 0.0216),
            (1.4, 0.015),
            (1.5, 0.0105)
        };

        /// <summary>
        /// Gets the default values of the depth factors [-].
        /// </summary>
        public static IReadOnlyList<(double, double)> DepthFactors => new[]
        {
            (-1, 0.005040816326530646),
            (-0.9744897959183674, 0.00596482278562177),
            (-0.9489795918367347, 0.007049651822326582),
            (-0.923469387755102, 0.008280657034496978),
            (-0.8979591836734694, 0.009643192019984783),
            (-0.8724489795918368, 0.011122610376641823),
            (-0.846938775510204, 0.012704265702320014),
            (-0.8214285714285714, 0.014373511594871225),
            (-0.7959183673469388, 0.016115701652147284),
            (-0.7704081632653061, 0.017916189471999994),
            (-0.7448979591836735, 0.019760328652281334),
            (-0.7193877551020409, 0.02163347279084307),
            (-0.6938775510204082, 0.02352097548553716),
            (-0.6683673469387754, 0.025408190334215378),
            (-0.6428571428571429, 0.027280470934729583),
            (-0.6173469387755102, 0.029123170884931715),
            (-0.5918367346938775, 0.030921643782673508),
            (-0.5663265306122449, 0.03266124322580695),
            (-0.5408163265306123, 0.034327322812183814),
            (-0.5153061224489797, 0.03590523613965599),
            (-0.4897959183673469, 0.036419783440920166),
            (-0.4642857142857143, 0.03634372210983519),
            (-0.4387755102040817, 0.03603984556448696),
            (-0.41326530612244894, 0.0355249692161967),
            (-0.3877551020408163, 0.03481590847628564),
            (-0.3622448979591837, 0.033929478756075014),
            (-0.33673469387755095, 0.032882495466886014),
            (-0.31122448979591844, 0.03169177402003989),
            (-0.2857142857142858, 0.03037412982685786),
            (-0.2602040816326531, 0.028946378298661132),
            (-0.23469387755102034, 0.02742533484677094),
            (-0.2091836734693877, 0.02582781488250851),
            (-0.1836734693877552, 0.024170633817195083),
            (-0.15816326530612246, 0.022470607062151843),
            (-0.13265306122448983, 0.02074455002870004),
            (-0.1071428571428571, 0.019009278128160882),
            (-0.08163265306122447, 0.01728160677185561),
            (-0.056122448979591955, 0.015578351371105446),
            (-0.030612244897959218, 0.01391632733723159),
            (-0.005102040816326481, 0.012312350081555283),
            (0.020408163265306145, 0.010783235015397755),
            (0.04591836734693877, 0.00934579755008022),
            (0.0714285714285714, 0.008016853096923902),
            (0.09693877551020402, 0.006813217067250026),
            (0.12244897959183665, 0.005751704872379814),
            (0.1479591836734695, 0.004849131923634483),
            (0.17346938775510212, 0.004122313632335269),
            (0.19897959183673475, 0.0035880654098033892),
            (0.22448979591836737, 0.003263202667360069),
            (0.25, 0.0031645408163265307)
        };

        /// <summary>
        /// Gets the default values of the impact factors [-].
        /// </summary>
        public static IReadOnlyList<(double, double)> ImpactFactors => new[]
        {
            (2, 0.039),
            (2.4, 0.1),
            (2.8, 0.18),
            (3.2, 0.235),
            (3.6, 0.2),
            (4, 0.13),
            (4.4, 0.08),
            (4.8, 0.02),
            (5.2, 0.01),
            (5.6, 0.005),
            (6, 0.001)
        };

        /// <summary>
        /// Gets the default value of the fatigue alpha coefficient [-].
        /// </summary>
        public static double FatigueAlpha => 0.42;

        /// <summary>
        /// Gets the default value of the fatigue beta coefficient [-].
        /// </summary>
        public static double FatigueBeta => 4.76;
    }
}