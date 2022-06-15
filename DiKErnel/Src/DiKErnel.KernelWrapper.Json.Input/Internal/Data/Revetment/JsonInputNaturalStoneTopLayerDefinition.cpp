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

#include "JsonInputNaturalStoneTopLayerDefinition.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    #pragma region Set methods

    void JsonInputNaturalStoneTopLayerDefinition::SetHydraulicLoadAp(
        unique_ptr<double> hydraulicLoadAp)
    {
        _hydraulicLoadAp = move(hydraulicLoadAp);
    }

    void JsonInputNaturalStoneTopLayerDefinition::SetHydraulicLoadBp(
        unique_ptr<double> hydraulicLoadBp)
    {
        _hydraulicLoadBp = move(hydraulicLoadBp);
    }

    void JsonInputNaturalStoneTopLayerDefinition::SetHydraulicLoadCp(
        unique_ptr<double> hydraulicLoadCp)
    {
        _hydraulicLoadCp = move(hydraulicLoadCp);
    }

    void JsonInputNaturalStoneTopLayerDefinition::SetHydraulicLoadNp(
        unique_ptr<double> hydraulicLoadNp)
    {
        _hydraulicLoadNp = move(hydraulicLoadNp);
    }

    void JsonInputNaturalStoneTopLayerDefinition::SetHydraulicLoadAs(
        unique_ptr<double> hydraulicLoadAs)
    {
        _hydraulicLoadAs = move(hydraulicLoadAs);
    }

    void JsonInputNaturalStoneTopLayerDefinition::SetHydraulicLoadBs(
        unique_ptr<double> hydraulicLoadBs)
    {
        _hydraulicLoadBs = move(hydraulicLoadBs);
    }

    void JsonInputNaturalStoneTopLayerDefinition::SetHydraulicLoadCs(
        unique_ptr<double> hydraulicLoadCs)
    {
        _hydraulicLoadCs = move(hydraulicLoadCs);
    }

    void JsonInputNaturalStoneTopLayerDefinition::SetHydraulicLoadNs(
        unique_ptr<double> hydraulicLoadNs)
    {
        _hydraulicLoadNs = move(hydraulicLoadNs);
    }

    void JsonInputNaturalStoneTopLayerDefinition::SetHydraulicLoadXib(
        unique_ptr<double> hydraulicLoadXib)
    {
        _hydraulicLoadXib = move(hydraulicLoadXib);
    }

    #pragma endregion

    #pragma region Get methods

    const double* JsonInputNaturalStoneTopLayerDefinition::GetHydraulicLoadXib() const
    {
        return _hydraulicLoadXib.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinition::GetHydraulicLoadAp() const
    {
        return _hydraulicLoadAp.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinition::GetHydraulicLoadBp() const
    {
        return _hydraulicLoadBp.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinition::GetHydraulicLoadCp() const
    {
        return _hydraulicLoadCp.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinition::GetHydraulicLoadNp() const
    {
        return _hydraulicLoadNp.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinition::GetHydraulicLoadAs() const
    {
        return _hydraulicLoadAs.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinition::GetHydraulicLoadBs() const
    {
        return _hydraulicLoadBs.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinition::GetHydraulicLoadCs() const
    {
        return _hydraulicLoadCs.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinition::GetHydraulicLoadNs() const
    {
        return _hydraulicLoadNs.get();
    }

    #pragma endregion
}
