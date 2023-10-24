// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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

using System;
using System.Collections.Generic;
using DiKErnel.FunctionLibrary.GrassRevetmentOvertopping;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.FunctionLibrary.Test.GrassRevetmentOvertopping
{
    [TestFixture]
    public class GrassRevetmentOvertoppingRepresentative2PInputTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            double waterLevel = Random.NextDouble();
            double waveHeightHm0 = Random.NextDouble();
            double wavePeriodTm10 = Random.NextDouble();
            double waveDirection = Random.NextDouble();
            IReadOnlyList<double> xValuesProfile = Array.Empty<double>();
            IReadOnlyList<double> zValuesProfile = Array.Empty<double>();
            IReadOnlyList<double> roughnessCoefficients = Array.Empty<double>();
            double dikeHeight = Random.NextDouble();
            double dikeOrientation = Random.NextDouble();

            // Call
            var input = new GrassRevetmentOvertoppingRepresentative2PInput(waterLevel, waveHeightHm0, wavePeriodTm10,
                                                                           waveDirection, xValuesProfile, zValuesProfile,
                                                                           roughnessCoefficients, dikeHeight,
                                                                           dikeOrientation);

            // Assert
            Assert.That(input.WaterLevel, Is.EqualTo(waterLevel));
            Assert.That(input.WaveHeightHm0, Is.EqualTo(waveHeightHm0));
            Assert.That(input.WavePeriodTm10, Is.EqualTo(wavePeriodTm10));
            Assert.That(input.WaveDirection, Is.EqualTo(waveDirection));
            Assert.AreSame(xValuesProfile, input.XValuesProfile);
            Assert.AreSame(zValuesProfile, input.ZValuesProfile);
            Assert.AreSame(roughnessCoefficients, input.RoughnessCoefficients);
            Assert.That(input.DikeHeight, Is.EqualTo(dikeHeight));
            Assert.That(input.DikeOrientation, Is.EqualTo(dikeOrientation));
        }
    }
}