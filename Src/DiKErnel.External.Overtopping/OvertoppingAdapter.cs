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

using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using DiKErnel.External.Overtopping.Data;

namespace DiKErnel.External.Overtopping
{
    /// <summary>
    /// Adapter for the overtopping validation and calculation.
    /// </summary>
    public static class OvertoppingAdapter
    {
        private const string dikesOvertoppingDllName = "dllDikesOvertopping.dll";
        private const string languageCode = "UK";
        private const int bufferCapacity = 3072;

        /// <summary>
        /// Validates the input arguments for an overtopping calculation.
        /// </summary>
        /// <param name="xValues">The x values of the profile points [m].</param>
        /// <param name="zValues">The z values of the profile points [m].</param>
        /// <param name="roughnessCoefficients">The roughness coefficients of the profile
        /// segments [-].</param>
        /// <param name="dikeHeight">The dike height [m].</param>
        /// <returns>A collection of validation messages.</returns>
        public static IEnumerable<string> Validate(IEnumerable<double> xValues, IEnumerable<double> zValues,
                                                   IEnumerable<double> roughnessCoefficients, double dikeHeight)
        {
            Geometry geometry = CreateGeometry(xValues, zValues, roughnessCoefficients);
            ModelFactors modelFactors = GetDefaultModelFactors();

            var success = false;
            var messageBuffer = new char[bufferCapacity];

            SetLanguage(languageCode.ToCharArray(), languageCode.Length);
            ValidateInputC(ref geometry, ref dikeHeight, ref modelFactors, ref success, messageBuffer, bufferCapacity);

            return success
                       ? Enumerable.Empty<string>()
                       : new string(messageBuffer).TrimEnd('\0').Split('\t');
        }

        /// <summary>
        /// Calculates the representative wave run-up (2 percent).
        /// </summary>
        /// <param name="waterLevel">The water level [m].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="wavePeriodTm10">The wave period Tm10 [s].</param>
        /// <param name="waveDirection">The wave direction with respect to the
        /// North [deg].</param>
        /// <param name="xValues">The x values of the profile points [m].</param>
        /// <param name="zValues">The z values of the profile points [m].</param>
        /// <param name="roughnessCoefficients">The roughness coefficients of the profile
        /// segments [-].</param>
        /// <param name="dikeHeight">The dike height [m].</param>
        /// <returns>The representative wave run-up (2 percent) [m].</returns>
        public static double CalculateZ2(double waterLevel, double waveHeightHm0, double wavePeriodTm10, double waveDirection,
                                         IEnumerable<double> xValues, IEnumerable<double> zValues,
                                         IEnumerable<double> roughnessCoefficients, double dikeHeight)
        {
            var load = new Load
            {
                WaterLevel = waterLevel,
                Height = waveHeightHm0,
                Period = wavePeriodTm10,
                Direction = waveDirection
            };

            Geometry geometry = CreateGeometry(xValues, zValues, roughnessCoefficients);
            ModelFactors modelFactors = GetDefaultModelFactors();
            var result = new Result();

            var success = false;
            int verbosity = -1;
            var messageBuffer = new char[bufferCapacity];
            var logFileName = new char[bufferCapacity];

            SetLanguage(languageCode.ToCharArray(), languageCode.Length);
            calculateQo(ref load, ref geometry, ref dikeHeight, ref modelFactors, ref result, ref success, messageBuffer,
                        ref verbosity, logFileName, bufferCapacity, bufferCapacity);

            return result.Z2;
        }

        private static Geometry CreateGeometry(IEnumerable<double> xValues, IEnumerable<double> zValues,
                                               IEnumerable<double> roughnessCoefficients)
        {
            double[] xValuesArray = xValues.ToArray();
            double[] zValuesArray = zValues.ToArray();
            double[] roughnessCoefficientsArray = roughnessCoefficients.ToArray();

            var geometry = new Geometry
            {
                Normal = 0.0,
                NPoints = xValuesArray.Length,
                XCoords = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * xValuesArray.Length),
                YCoords = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * zValuesArray.Length),
                Roughness = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(double)) * roughnessCoefficientsArray.Length)
            };

            Marshal.Copy(xValuesArray, 0, geometry.XCoords, xValuesArray.Length);
            Marshal.Copy(zValuesArray, 0, geometry.YCoords, zValuesArray.Length);
            Marshal.Copy(roughnessCoefficientsArray, 0, geometry.Roughness, roughnessCoefficientsArray.Length);

            return geometry;
        }

        private static ModelFactors GetDefaultModelFactors()
        {
            return new ModelFactors
            {
                FactorDeterminationQnFn = 1.0,
                FactorDeterminationQbFb = 1.0,
                Mz2 = 1.0,
                FShallow = 1.0,
                ComputedOvertopping = 1.0,
                CriticalOvertopping = 1.0,
                RelaxationFactor = 1.0,
                ReductionFactorForeshore = 0.5
            };
        }

        [DllImport(dikesOvertoppingDllName, CallingConvention = CallingConvention.Cdecl)]
        private static extern void ValidateInputC(ref Geometry geometryInput, ref double dikeHeight, ref ModelFactors modelFactors,
                                                  ref bool success, [Out] char[] message, int size);

        [DllImport(dikesOvertoppingDllName, CallingConvention = CallingConvention.Cdecl)]
        private static extern void SetLanguage([In] char[] languageCode, int languageCodeLength);

        [DllImport(dikesOvertoppingDllName, CallingConvention = CallingConvention.Cdecl)]
        private static extern void calculateQo(ref Load loadInput, ref Geometry geometryInput, ref double dikeHeight,
                                               ref ModelFactors modelFactors, ref Result result, ref bool success,
                                               [Out] char[] message, ref int verbosity, [Out] char[] logFile, int messageSize,
                                               int logFileSize);
    }
}