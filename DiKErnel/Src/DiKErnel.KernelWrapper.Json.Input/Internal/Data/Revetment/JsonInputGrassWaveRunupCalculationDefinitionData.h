// Copyright (C) Stichting Deltares 2022. All rights reserved.
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

#include <map>
#include <memory>

#include "JsonInputCalculationDefinitionData.h"
#include "JsonInputGrassRevetmentTopLayerType.h"
#include "JsonInputGrassWaveRunupCalculationProtocolData.h"
#include "JsonInputGrassWaveRunupTopLayerDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputGrassWaveRunupCalculationDefinitionData : public JsonInputCalculationDefinitionData
    {
        public:
            explicit JsonInputGrassWaveRunupCalculationDefinitionData(
                std::unique_ptr<double> failureNumber,
                std::unique_ptr<JsonInputGrassWaveRunupCalculationProtocolData> calculationProtocolData,
                std::map<JsonInputGrassRevetmentTopLayerType, std::unique_ptr<JsonInputGrassWaveRunupTopLayerDefinitionData>>
                topLayerDefinitionData);

            #pragma region Set methods

            void SetFactorCtm(
                std::unique_ptr<double> factorCtm);

            void SetRepresentativeWaveRunup2PA(
                std::unique_ptr<double> representativeWaveRunup2PA);

            void SetRepresentativeWaveRunup2PB(
                std::unique_ptr<double> representativeWaveRunup2PB);

            void SetRepresentativeWaveRunup2PC(
                std::unique_ptr<double> representativeWaveRunup2PC);

            void SetWaveAngleImpactABeta(
                std::unique_ptr<double> waveAngleImpactABeta);

            void SetWaveAngleImpactBetaMax(
                std::unique_ptr<double> waveAngleImpactBetaMax);

            #pragma endregion

            #pragma region Get methods

            [[nodiscard]]
            const JsonInputGrassWaveRunupCalculationProtocolData* GetCalculationProtocolData() const;

            [[nodiscard]]
            const std::map<JsonInputGrassRevetmentTopLayerType, std::reference_wrapper<JsonInputGrassWaveRunupTopLayerDefinitionData>>&
            GetTopLayerDefinitionData() const;

            [[nodiscard]]
            const double* GetFactorCtm() const;

            [[nodiscard]]
            const double* GetRepresentativeWaveRunup2PA() const;

            [[nodiscard]]
            const double* GetRepresentativeWaveRunup2PB() const;

            [[nodiscard]]
            const double* GetRepresentativeWaveRunup2PC() const;

            [[nodiscard]]
            const double* GetWaveAngleImpactABeta() const;

            [[nodiscard]]
            const double* GetWaveAngleImpactBetaMax() const;

            #pragma endregion

        private:
            std::unique_ptr<JsonInputGrassWaveRunupCalculationProtocolData> _calculationProtocolData;
            std::map<JsonInputGrassRevetmentTopLayerType, std::unique_ptr<JsonInputGrassWaveRunupTopLayerDefinitionData>>
            _topLayerDefinitionData;
            std::map<JsonInputGrassRevetmentTopLayerType, std::reference_wrapper<JsonInputGrassWaveRunupTopLayerDefinitionData>>
            _topLayerDefinitionDataReferences;
            std::unique_ptr<double> _factorCtm = nullptr;
            std::unique_ptr<double> _representativeWaveRunup2PA = nullptr;
            std::unique_ptr<double> _representativeWaveRunup2PB = nullptr;
            std::unique_ptr<double> _representativeWaveRunup2PC = nullptr;
            std::unique_ptr<double> _waveAngleImpactABeta = nullptr;
            std::unique_ptr<double> _waveAngleImpactBetaMax = nullptr;
    };
}
