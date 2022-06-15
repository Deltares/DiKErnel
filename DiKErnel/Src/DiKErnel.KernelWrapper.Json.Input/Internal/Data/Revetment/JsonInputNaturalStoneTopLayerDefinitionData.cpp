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

#include "JsonInputNaturalStoneTopLayerDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    #pragma region Set methods

    void JsonInputNaturalStoneTopLayerDefinitionData::SetHydraulicLoadAp(
        unique_ptr<double> hydraulicLoadAp)
    {
        _hydraulicLoadAp = move(hydraulicLoadAp);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetHydraulicLoadBp(
        unique_ptr<double> hydraulicLoadBp)
    {
        _hydraulicLoadBp = move(hydraulicLoadBp);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetHydraulicLoadCp(
        unique_ptr<double> hydraulicLoadCp)
    {
        _hydraulicLoadCp = move(hydraulicLoadCp);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetHydraulicLoadNp(
        unique_ptr<double> hydraulicLoadNp)
    {
        _hydraulicLoadNp = move(hydraulicLoadNp);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetHydraulicLoadAs(
        unique_ptr<double> hydraulicLoadAs)
    {
        _hydraulicLoadAs = move(hydraulicLoadAs);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetHydraulicLoadBs(
        unique_ptr<double> hydraulicLoadBs)
    {
        _hydraulicLoadBs = move(hydraulicLoadBs);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetHydraulicLoadCs(
        unique_ptr<double> hydraulicLoadCs)
    {
        _hydraulicLoadCs = move(hydraulicLoadCs);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetHydraulicLoadNs(
        unique_ptr<double> hydraulicLoadNs)
    {
        _hydraulicLoadNs = move(hydraulicLoadNs);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetHydraulicLoadXib(
        unique_ptr<double> hydraulicLoadXib)
    {
        _hydraulicLoadXib = move(hydraulicLoadXib);
    }

    #pragma endregion

    #pragma region Get methods

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetHydraulicLoadXib() const
    {
        return _hydraulicLoadXib.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetHydraulicLoadAp() const
    {
        return _hydraulicLoadAp.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetHydraulicLoadBp() const
    {
        return _hydraulicLoadBp.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetHydraulicLoadCp() const
    {
        return _hydraulicLoadCp.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetHydraulicLoadNp() const
    {
        return _hydraulicLoadNp.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetHydraulicLoadAs() const
    {
        return _hydraulicLoadAs.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetHydraulicLoadBs() const
    {
        return _hydraulicLoadBs.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetHydraulicLoadCs() const
    {
        return _hydraulicLoadCs.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetHydraulicLoadNs() const
    {
        return _hydraulicLoadNs.get();
    }

    #pragma endregion
}
