// Copyright (C) Stichting Deltares 2020. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#include <gtest/gtest.h>

#include "AsphaltRevetmentWaveImpact.h"

namespace DiKErnel::FunctionLibrary::Test
{
    using namespace std;

    TEST(AsphaltRevetmentWaveImpactTest, IncrementDamage_ValidInput_ExpectedValue)
    {
        // Setup
        const auto logFailureTension = 0.193124598;
        const auto averageNumberOfWaves = 6492.937853;
        const auto maximumPeakStress = 0.0160884;
        const auto stiffnessRelation = 1.185626183;
        const auto computationalThickness = 0.16;
        const auto tanA = 0.232914161;

        vector<tuple<double, double>> widthFactors;
        widthFactors.emplace_back(0.1, 0.0392);
        widthFactors.emplace_back(0.2, 0.0738);
        widthFactors.emplace_back(0.3, 0.1002);
        widthFactors.emplace_back(0.4, 0.1162);
        widthFactors.emplace_back(0.5, 0.1213);
        widthFactors.emplace_back(0.6, 0.1168);
        widthFactors.emplace_back(0.7, 0.1051);
        widthFactors.emplace_back(0.8, 0.089);
        widthFactors.emplace_back(0.9, 0.0712);
        widthFactors.emplace_back(1.0, 0.0541);
        widthFactors.emplace_back(1.1, 0.0391);
        widthFactors.emplace_back(1.2, 0.0269);
        widthFactors.emplace_back(1.3, 0.0216);
        widthFactors.emplace_back(1.4, 0.015);
        widthFactors.emplace_back(1.5, 0.0105);

        vector<tuple<double, double>> depthFactors;
        depthFactors.emplace_back(-1.0, 0.0244);
        depthFactors.emplace_back(-0.875, 0.0544);
        depthFactors.emplace_back(-0.75, 0.0938);
        depthFactors.emplace_back(-0.625, 0.1407);
        depthFactors.emplace_back(-0.5, 0.1801);
        depthFactors.emplace_back(-0.375, 0.1632);
        depthFactors.emplace_back(-0.25, 0.1426);
        depthFactors.emplace_back(-0.125, 0.0994);
        depthFactors.emplace_back(0.0, 0.06);
        depthFactors.emplace_back(0.125, 0.0244);
        depthFactors.emplace_back(0.25, 0.0169);

        vector<tuple<double, double>> impactFactors;
        impactFactors.emplace_back(2.0, 0.039);
        impactFactors.emplace_back(2.4, 0.1);
        impactFactors.emplace_back(2.8, 0.18);
        impactFactors.emplace_back(3.2, 0.235);
        impactFactors.emplace_back(3.6, 0.2);
        impactFactors.emplace_back(4.0, 0.13);
        impactFactors.emplace_back(4.4, 0.08);
        impactFactors.emplace_back(4.8, 0.02);
        impactFactors.emplace_back(5.2, 0.01);
        impactFactors.emplace_back(5.6, 0.005);
        impactFactors.emplace_back(6.0, 0.001);

        const auto positionZ = 2.988;
        const auto waterLevel = 3.8;
        const auto waveHeightHm0 = 1.6;
        const auto fatigueAlpha = 0.42;
        const auto fatigueBeta = 4.76;
        const auto impactNumberC = 1.0;

        // Call
        const auto incrementDamage = AsphaltRevetmentWaveImpact::IncrementDamage(
            logFailureTension,
            averageNumberOfWaves,
            maximumPeakStress,
            stiffnessRelation,
            computationalThickness,
            tanA,
            widthFactors,
            depthFactors,
            impactFactors,
            positionZ,
            waterLevel,
            waveHeightHm0,
            fatigueAlpha,
            fatigueBeta,
            impactNumberC);

        // Assert
        ASSERT_DOUBLE_EQ(9.257776511818653, incrementDamage);
    }
}
