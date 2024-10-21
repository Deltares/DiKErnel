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

#include "NaturalStoneRevetmentLocationDependentOutput.h"

#include <utility>

#include "NaturalStoneRevetmentFunctions.h"
#include "NaturalStoneRevetmentTimeDependentOutput.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace FunctionLibrary;
    using namespace std;

    NaturalStoneRevetmentLocationDependentOutput::NaturalStoneRevetmentLocationDependentOutput(
        vector<unique_ptr<TimeDependentOutput>> timeDependentOutputItems,
        const double z)
        : LocationDependentOutput(move(timeDependentOutputItems)),
          _z(z) {}

    double NaturalStoneRevetmentLocationDependentOutput::GetZ() const
    {
        return _z;
    }

    double NaturalStoneRevetmentLocationDependentOutput::CalculateTimeOfFailure(
        double failureNumber,
        std::reference_wrapper<ITimeDependentInput> timeDependentInput,
        std::reference_wrapper<TimeDependentOutput> timeDependentOutput,
        double damageAtStartOfCalculation) const
    {
        const auto* naturalStoneWaveImpactTimeDependentOutput = dynamic_cast<NaturalStoneRevetmentTimeDependentOutput*>(&timeDependentOutput.get());

        const double referenceFailure = NaturalStoneRevetmentFunctions::ReferenceFailure(
            *naturalStoneWaveImpactTimeDependentOutput->GetResistance(),
            *naturalStoneWaveImpactTimeDependentOutput->GetHydraulicLoad(),
            *naturalStoneWaveImpactTimeDependentOutput->GetWaveAngleImpact(),
            failureNumber);

        const double referenceTimeFailure = NaturalStoneRevetmentFunctions::ReferenceTimeFailure(
            referenceFailure, timeDependentInput.get().GetWavePeriodTm10());

        const double durationInTimeStepFailure = NaturalStoneRevetmentFunctions::DurationInTimeStepFailure(
            referenceTimeFailure, *naturalStoneWaveImpactTimeDependentOutput->GetReferenceTimeDegradation());

        return timeDependentInput.get().GetBeginTime() + durationInTimeStepFailure;
    }
}
