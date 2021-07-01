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
        auto output = JsonOutputDamageLocationData::CreateJson();

        output["FysicaBekleding"] = ordered_json(
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
                    Select<NaturalStoneRevetmentTimeDependentOutput*, double>(_timeDependentOutputItems, [](
                                                                          NaturalStoneRevetmentTimeDependentOutput* tdo) -> double
                                                                              {
                                                                                  return tdo->GetIncrementDamage();
                                                                              })
                },
                {
                    "BelastingBekleding",
                    Select<NaturalStoneRevetmentTimeDependentOutput*, double>(_timeDependentOutputItems, [](
                                                                          NaturalStoneRevetmentTimeDependentOutput* tdo) -> double
                                                                              {
                                                                                  return tdo->GetLoadingRevetment();
                                                                              })
                },
                {
                    "Golfbrekingparameter",
                    Select<NaturalStoneRevetmentTimeDependentOutput*, double>(_timeDependentOutputItems, [](
                                                                          NaturalStoneRevetmentTimeDependentOutput* tdo) -> double
                                                                              {
                                                                                  return tdo->GetSurfSimilarityParameter();
                                                                              })
                },
                {
                    "GolfsteilheidDiepWater",
                    Select<NaturalStoneRevetmentTimeDependentOutput*, double>(_timeDependentOutputItems, [](
                                                                          NaturalStoneRevetmentTimeDependentOutput* tdo) -> double
                                                                              {
                                                                                  return tdo->GetWaveSteepnessDeepWater();
                                                                              })
                },
                {
                    "BovengrensBelastingNatuursteen",
                     Select<NaturalStoneRevetmentTimeDependentOutput*, double>(_timeDependentOutputItems, [](
                                                                          NaturalStoneRevetmentTimeDependentOutput* tdo) -> double
                                                                              {
                                                                                  return tdo->GetUpperLimitLoading();
                                                                              })
                },
                {
                    "OndergrensBelastingNatuursteen",
                     Select<NaturalStoneRevetmentTimeDependentOutput*, double>(_timeDependentOutputItems, [](
                                                                          NaturalStoneRevetmentTimeDependentOutput* tdo) -> double
                                                                              {
                                                                                  return tdo->GetLowerLimitLoading();
                                                                              })
                },
                {
                    "DiepteMaximaleGolfbelastingNatuursteen",
                     Select<NaturalStoneRevetmentTimeDependentOutput*, double>(_timeDependentOutputItems, [](
                                                                          NaturalStoneRevetmentTimeDependentOutput* tdo) -> double
                                                                              {
                                                                                  return tdo->GetDepthMaximumWaveLoad();
                                                                              })
                },
                {
                    "AfstandMaximaleStijghoogteNatuursteen",
                     Select<NaturalStoneRevetmentTimeDependentOutput*, double>(_timeDependentOutputItems, [](
                                                                          NaturalStoneRevetmentTimeDependentOutput* tdo) -> double
                                                                              {
                                                                                  return tdo->GetDistanceMaximumWaveElevation();
                                                                              })
                },
                {
                    "MaatgevendeBreedteGolfklapNatuursteen",
                     Select<NaturalStoneRevetmentTimeDependentOutput*, double>(_timeDependentOutputItems, [](
                                                                          NaturalStoneRevetmentTimeDependentOutput* tdo) -> double
                                                                              {
                                                                                  return tdo->GetNormativeWidthOfWaveImpact();
                                                                              })
                }
            });

        return output;
    }

    template <typename TSource, typename TResult>
    vector<TResult> JsonOutputNaturalStoneRevetmentPhysicsLocationData::Select(
        vector<TSource> source,
        function<TResult(
            TSource)> f)
    {
        auto result = vector<TResult>();

        for (auto item : source)
        {
            result.emplace_back(f(item));
        }

        return result;
    }
}
