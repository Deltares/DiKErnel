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

#include <memory>

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputNaturalStoneTopLayerDefinitionData
    {
        public:
            #pragma region Set methods

            void SetStabilityPlungingA(
                std::unique_ptr<double> stabilityPlungingA);

            void SetStabilityPlungingB(
                std::unique_ptr<double> stabilityPlungingB);

            void SetStabilityPlungingC(
                std::unique_ptr<double> stabilityPlungingC);

            void SetStabilityPlungingN(
                std::unique_ptr<double> stabilityPlungingN);

            void SetStabilitySurgingA(
                std::unique_ptr<double> stabilitySurgingA);

            void SetStabilitySurgingB(
                std::unique_ptr<double> stabilitySurgingB);

            void SetStabilitySurgingC(
                std::unique_ptr<double> stabilitySurgingC);

            void SetStabilitySurgingN(
                std::unique_ptr<double> stabilitySurgingN);

            void SetStabilityXib(
                std::unique_ptr<double> stabilityXib);

            #pragma endregion

            #pragma region Get methods

            [[nodiscard]]
            const double* GetStabilityXib() const;

            [[nodiscard]]
            const double* GetStabilityPlungingA() const;

            [[nodiscard]]
            const double* GetStabilityPlungingB() const;

            [[nodiscard]]
            const double* GetStabilityPlungingC() const;

            [[nodiscard]]
            const double* GetStabilityPlungingN() const;

            [[nodiscard]]
            const double* GetStabilitySurgingA() const;

            [[nodiscard]]
            const double* GetStabilitySurgingB() const;

            [[nodiscard]]
            const double* GetStabilitySurgingC() const;

            [[nodiscard]]
            const double* GetStabilitySurgingN() const;

            #pragma endregion

        private:
            std::unique_ptr<double> _stabilityXib = nullptr;
            std::unique_ptr<double> _stabilityPlungingA = nullptr;
            std::unique_ptr<double> _stabilityPlungingB = nullptr;
            std::unique_ptr<double> _stabilityPlungingC = nullptr;
            std::unique_ptr<double> _stabilityPlungingN = nullptr;
            std::unique_ptr<double> _stabilitySurgingA = nullptr;
            std::unique_ptr<double> _stabilitySurgingB = nullptr;
            std::unique_ptr<double> _stabilitySurgingC = nullptr;
            std::unique_ptr<double> _stabilitySurgingN = nullptr;
    };
}
