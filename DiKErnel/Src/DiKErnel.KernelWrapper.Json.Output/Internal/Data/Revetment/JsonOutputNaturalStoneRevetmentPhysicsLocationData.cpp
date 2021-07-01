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

#include "JsonOutputNaturalStoneRevetmentPhysicsLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    using namespace Core;
    using namespace Integration;
    using namespace nlohmann;
    using namespace std;

    JsonOutputNaturalStoneRevetmentPhysicsLocationData::JsonOutputNaturalStoneRevetmentPhysicsLocationData(
        const LocationDependentOutput& locationOutput,
        const NaturalStoneRevetmentLocationDependentInput& locationInput)
        : JsonOutputDamageLocationData(locationOutput, locationInput)
    {
        for (auto timeDependentOutput : locationOutput.GetTimeDependentOutputItems())
        {
            _timeDependentOutputItems.emplace_back(dynamic_cast<NaturalStoneRevetmentTimeDependentOutput*>(&timeDependentOutput.get()));
        }
    }

    ordered_json JsonOutputNaturalStoneRevetmentPhysicsLocationData::CreateJson() const
    {
        auto physicsJson = ordered_json(
            {
                {
                    "TypeToplaag",
                    "NoorseSteen"
                },
                {
                    "RekenmethodeSoort",
                    "Natuursteen"
                },
                {
                    "ToenameschadeNatuursteen",
                    json::array({})
                },
                {
                    "BelastingBekleding",
                    json::array({})
                },
                {
                    "Golfbrekingparameter",
                    json::array({})
                },
                {
                    "GolfsteilheidDiepWater",
                    json::array({})
                },
                {
                    "BovengrensBelastingNatuursteen",
                    json::array({})
                },
                {
                    "OndergrensBelastingNatuursteen",
                    json::array({})
                },
                {
                    "DiepteMaximaleGolfbelastingNatuursteen",
                    json::array({})
                },
                {
                    "AfstandMaximaleStijghoogteNatuursteen",
                    json::array({})
                },
                {
                    "MaatgevendeBreedteGolfklapNatuursteen",
                    json::array({})
                },
                {
                    "HydraulischeBelastingNatuursteen",
                    json::array({})
                },
                {
                    "ImpactGolfhoekBekledingNatuursteen",
                    json::array({})
                },
                {
                    "SterkteBekledingNatuursteen",
                    json::array({})
                },
                {
                    "ReferentieTijdDegradatieNatuursteen",
                    json::array({})
                },
                {
                    "ReferentieDegradatieNatuursteen",
                    json::array({})
                }
            });

        for (int i = 0; i < static_cast<int>(_timeDependentOutputItems.size()); ++i)
        {
            const auto* outputItem = _timeDependentOutputItems[i];

            physicsJson["ToenameschadeNatuursteen"][i] = outputItem->GetIncrementDamage();
            physicsJson["BelastingBekleding"][i] = outputItem->GetLoadingRevetment();
            physicsJson["Golfbrekingparameter"][i] = outputItem->GetSurfSimilarityParameter();
            physicsJson["GolfsteilheidDiepWater"][i] = outputItem->GetWaveSteepnessDeepWater();
            physicsJson["BovengrensBelastingNatuursteen"][i] = outputItem->GetUpperLimitLoading();
            physicsJson["OndergrensBelastingNatuursteen"][i] = outputItem->GetLowerLimitLoading();
            physicsJson["DiepteMaximaleGolfbelastingNatuursteen"][i] = outputItem->GetDepthMaximumWaveLoad();
            physicsJson["AfstandMaximaleStijghoogteNatuursteen"][i] = outputItem->GetDistanceMaximumWaveElevation();
            physicsJson["MaatgevendeBreedteGolfklapNatuursteen"][i] = outputItem->GetNormativeWidthOfWaveImpact();
            physicsJson["HydraulischeBelastingNatuursteen"][i] = nullptr;
            physicsJson["ImpactGolfhoekBekledingNatuursteen"][i] = nullptr;
            physicsJson["SterkteBekledingNatuursteen"][i] = nullptr;
            physicsJson["ReferentieTijdDegradatieNatuursteen"][i] = nullptr;
            physicsJson["ReferentieDegradatieNatuursteen"][i] = nullptr;

            SetPropertyWhenApplicable(physicsJson["HydraulischeBelastingNatuursteen"][i], outputItem->GetHydraulicLoad());
            SetPropertyWhenApplicable(physicsJson["ImpactGolfhoekBekledingNatuursteen"][i], outputItem->GetWaveAngleImpact());
            SetPropertyWhenApplicable(physicsJson["SterkteBekledingNatuursteen"][i], outputItem->GetResistance());
            SetPropertyWhenApplicable(physicsJson["ReferentieTijdDegradatieNatuursteen"][i], outputItem->GetReferenceTimeDegradation());
            SetPropertyWhenApplicable(physicsJson["ReferentieDegradatieNatuursteen"][i], outputItem->GetReferenceDegradation());
        }

        auto output = JsonOutputDamageLocationData::CreateJson();
        output["FysicaBekleding"] = physicsJson;
        return output;
    }

    void JsonOutputNaturalStoneRevetmentPhysicsLocationData::SetPropertyWhenApplicable(
        ordered_json& jsonObject,
        const double* value)
    {
        if (value != nullptr)
        {
            jsonObject = *value;
        }
    }
}
