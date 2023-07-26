// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

namespace DiKErnel.Integration.Data
{
    internal class LocationDependentInput : ILocationDependentInput
    {
    public bool Validate(
                vector<reference_wrapper<ITimeDependentInput>>& timeDependentInputs,
                IProfileData& profileData) override;

    public unique_ptr<TimeDependentOutput> Calculate(
                double initialDamage,
                ITimeDependentInput& timeDependentInput,
                IProfileData& profileData) override;

    public double GetX() override;

    public double GetInitialDamage() override;

    public double GetFailureNumber() override;

    public double GetZ() override;

        protected void LocationDependentInput(
                double x,
                double initialDamage,
                double failureNumber);

    protected virtual void InitializeDerivedLocationDependentInput(
                IProfileData& profileData);

    protected virtual unique_ptr<TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                ITimeDependentInput& timeDependentInput,
                IProfileData& profileData) = 0;

            private double _x;
            private double _initialDamage;
            private double _failureNumber;
            private bool _derivedLocationDependentInputInitialized = false;
            private double _z = numeric_limits<double>::infinity();
    }
}