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

#pragma once
#include <string>

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * \brief Class containing Json related constants.
     */
    class JsonDefinitions
    {
        public:
            inline static std::string calculationData = "Rekendata";
            inline static std::string hydraulicLoads = "HydraulischeBelastingen";
            inline static std::string locations = "Locaties";

            inline static std::string time = "Tijd";
            inline static std::string maximumWaveAngle = "GolfhoekMaximum";
            inline static std::string boundaryConditionsPerTimeStep = "RandvoorwaardenPerTijdstap";
            inline static std::string waveHeightHm0 = "GolfhoogteHm0";
            inline static std::string wavePeriodTm10 = "GolfperiodeTm10";
            inline static std::string waveAngle = "Golfhoek";

            inline static std::string name = "Naam";
            inline static std::string revetment = "Bekleding";
            inline static std::string typeTopLayer = "TypeToplaag";
            inline static std::string relativeDensity = "RelatieveDichtheid";
            inline static std::string thicknessTopLayer = "DikteToplaag";
            inline static std::string initialDamage = "BeginSchade";
            inline static std::string similarityParameterThreshold = "BrekerIndexGrenswaarde";
            inline static std::string coefficientPlungingAp = "CoefficientPlungingAp";
            inline static std::string coefficientPlungingBp = "CoefficientPlungingBp";
            inline static std::string coefficientPlungingCp = "CoefficientPlungingCp";
            inline static std::string coefficientPlungingNp = "CoefficientPlungingNp";
            inline static std::string coefficientSurgingAs = "CoefficientSurgingAs";
            inline static std::string coefficientSurgingBs = "CoefficientSurgingBs";
            inline static std::string coefficientSurgingCs = "CoefficientSurgingCs";
            inline static std::string coefficientSurgingNs = "CoefficientSurgingNs";
            inline static std::string profileSchematisation = "Profielschematisatie";
            inline static std::string tanA = "TanA";
        };
}
