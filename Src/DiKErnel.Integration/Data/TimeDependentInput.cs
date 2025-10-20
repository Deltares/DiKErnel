// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.DomainLibrary.Validators;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data
{
    internal class TimeDependentInput : ITimeDependentInput
    {
        public TimeDependentInput(double beginTime, double endTime, double waterLevel, double waveHeightHm0,
                                  double wavePeriodTm10, double waveDirection)
        {
            BeginTime = beginTime;
            EndTime = endTime;
            WaterLevel = waterLevel;
            WaveHeightHm0 = waveHeightHm0;
            WavePeriodTm10 = wavePeriodTm10;
            WaveDirection = waveDirection;
        }

        public double BeginTime { get; }

        public double EndTime { get; }

        public double WaterLevel { get; }

        public double WaveHeightHm0 { get; }

        public double WavePeriodTm10 { get; }

        public double WaveDirection { get; }

        public bool Validate()
        {
            var validationIssues = new List<ValidationIssue>
            {
                HydraulicLoadsValidator.WaveHeightHm0(WaveHeightHm0),
                HydraulicLoadsValidator.WavePeriodTm10(WavePeriodTm10),
                HydraulicLoadsValidator.WaveDirection(WaveDirection)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues);
        }
    }
}