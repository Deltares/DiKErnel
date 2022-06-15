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

            void SetHydraulicLoadAp(
                std::unique_ptr<double> hydraulicLoadAp);

            void SetHydraulicLoadBp(
                std::unique_ptr<double> hydraulicLoadBp);

            void SetHydraulicLoadCp(
                std::unique_ptr<double> hydraulicLoadCp);

            void SetHydraulicLoadNp(
                std::unique_ptr<double> hydraulicLoadNp);

            void SetHydraulicLoadAs(
                std::unique_ptr<double> hydraulicLoadAs);

            void SetHydraulicLoadBs(
                std::unique_ptr<double> hydraulicLoadBs);

            void SetHydraulicLoadCs(
                std::unique_ptr<double> hydraulicLoadCs);

            void SetHydraulicLoadNs(
                std::unique_ptr<double> hydraulicLoadNs);

            void SetHydraulicLoadXib(
                std::unique_ptr<double> hydraulicLoadXib);

            #pragma endregion

            #pragma region Get methods

            [[nodiscard]]
            const double* GetHydraulicLoadXib() const;

            [[nodiscard]]
            const double* GetHydraulicLoadAp() const;

            [[nodiscard]]
            const double* GetHydraulicLoadBp() const;

            [[nodiscard]]
            const double* GetHydraulicLoadCp() const;

            [[nodiscard]]
            const double* GetHydraulicLoadNp() const;

            [[nodiscard]]
            const double* GetHydraulicLoadAs() const;

            [[nodiscard]]
            const double* GetHydraulicLoadBs() const;

            [[nodiscard]]
            const double* GetHydraulicLoadCs() const;

            [[nodiscard]]
            const double* GetHydraulicLoadNs() const;

            #pragma endregion

        private:
            std::unique_ptr<double> _hydraulicLoadXib = nullptr;
            std::unique_ptr<double> _hydraulicLoadAp = nullptr;
            std::unique_ptr<double> _hydraulicLoadBp = nullptr;
            std::unique_ptr<double> _hydraulicLoadCp = nullptr;
            std::unique_ptr<double> _hydraulicLoadNp = nullptr;
            std::unique_ptr<double> _hydraulicLoadAs = nullptr;
            std::unique_ptr<double> _hydraulicLoadBs = nullptr;
            std::unique_ptr<double> _hydraulicLoadCs = nullptr;
            std::unique_ptr<double> _hydraulicLoadNs = nullptr;
    };
}
