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

using System;
using System.Collections.Generic;

namespace DiKErnel.DomainLibrary.Defaults.AsphaltRevetmentWaveImpact
{
    /// <summary>
    /// Class that contains default values for asphalt revetments.
    /// </summary>
    public static class AsphaltRevetmentWaveImpactDefaults
    {
        /// <summary>
        /// Gets the default value of the density of water [kg/m^3].
        /// </summary>
        public static double DensityOfWater => 1025.0;

        /// <summary>
        /// Gets the default value of the Ctm coefficient [-].
        /// </summary>
        public static double AverageNumberOfWavesCtm => 1.0;

        /// <summary>
        /// Gets the default value of the impact number C coefficient [-].
        /// </summary>
        public static double ImpactNumberC => 1.0;

        /// <summary>
        /// Gets the default values of the width factors [-].
        /// </summary>
        public static IEnumerable<Tuple<double, double>> WidthFactors
        {
            get
            {
                yield return new Tuple<double, double>(0.1, 0.0392);
                yield return new Tuple<double, double>(0.2, 0.0738);
                yield return new Tuple<double, double>(0.3, 0.1002);
                yield return new Tuple<double, double>(0.4, 0.1162);
                yield return new Tuple<double, double>(0.5, 0.1213);
                yield return new Tuple<double, double>(0.6, 0.1168);
                yield return new Tuple<double, double>(0.7, 0.1051);
                yield return new Tuple<double, double>(0.8, 0.0890);
                yield return new Tuple<double, double>(0.9, 0.0712);
                yield return new Tuple<double, double>(1.0, 0.0541);
                yield return new Tuple<double, double>(1.1, 0.0391);
                yield return new Tuple<double, double>(1.2, 0.0269);
                yield return new Tuple<double, double>(1.3, 0.0216);
                yield return new Tuple<double, double>(1.4, 0.0150);
                yield return new Tuple<double, double>(1.5, 0.0105);
            }
        }

        /// <summary>
        /// Gets the default values of the depth factors [-].
        /// </summary>
        public static IEnumerable<Tuple<double, double>> DepthFactors
        {
            get
            {
                yield return new Tuple<double, double>(-1.0, 0.0244);
                yield return new Tuple<double, double>(-0.875, 0.0544);
                yield return new Tuple<double, double>(-0.750, 0.0938);
                yield return new Tuple<double, double>(-0.625, 0.1407);
                yield return new Tuple<double, double>(-0.500, 0.1801);
                yield return new Tuple<double, double>(-0.375, 0.1632);
                yield return new Tuple<double, double>(-0.250, 0.1426);
                yield return new Tuple<double, double>(-0.125, 0.0994);
                yield return new Tuple<double, double>(0.0, 0.06);
                yield return new Tuple<double, double>(0.125, 0.0244);
                yield return new Tuple<double, double>(0.250, 0.0169);
            }
        }

        /// <summary>
        /// Gets the default values of the impact factors [-].
        /// </summary>
        public static IEnumerable<Tuple<double, double>> ImpactFactors
        {
            get
            {
                yield return new Tuple<double, double>(2.0, 0.039);
                yield return new Tuple<double, double>(2.4, 0.1);
                yield return new Tuple<double, double>(2.8, 0.18);
                yield return new Tuple<double, double>(3.2, 0.235);
                yield return new Tuple<double, double>(3.6, 0.2);
                yield return new Tuple<double, double>(4.0, 0.13);
                yield return new Tuple<double, double>(4.4, 0.08);
                yield return new Tuple<double, double>(4.8, 0.02);
                yield return new Tuple<double, double>(5.2, 0.01);
                yield return new Tuple<double, double>(5.6, 0.005);
                yield return new Tuple<double, double>(6.0, 0.001);
            }
        }
    }
}