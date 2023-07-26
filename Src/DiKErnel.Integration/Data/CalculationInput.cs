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
    internal class CalculationInput : Core::ICalculationInput
    {
        public void CalculationInput(
                unique_ptr<Core::IProfileData> profileData,
                vector<unique_ptr<Core::ILocationDependentInput>> locationDependentInputItems,
                vector<unique_ptr<Core::ITimeDependentInput>> timeDependentInputItems);

    public Core::IProfileData& GetProfileData() override;

    public vector<reference_wrapper<Core::ILocationDependentInput>>& GetLocationDependentInputItems() override;

    public vector<reference_wrapper<Core::ITimeDependentInput>>& GetTimeDependentInputItems() override;

            private unique_ptr<Core::IProfileData> _profileData;
            private vector<unique_ptr<Core::ILocationDependentInput>> _locationDependentInputItems;
            private vector<reference_wrapper<Core::ILocationDependentInput>> _locationDependentInputItemReferences;
            private vector<unique_ptr<Core::ITimeDependentInput>> _timeDependentInputItems;
            private vector<reference_wrapper<Core::ITimeDependentInput>> _timeDependentInputItemReferences;
    }
}
