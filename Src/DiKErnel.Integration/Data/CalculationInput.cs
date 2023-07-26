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
    internal class CalculationInput : public Core::ICalculationInput
    {
        public void CalculationInput(
                std::unique_ptr<Core::IProfileData> profileData,
                std::vector<std::unique_ptr<Core::ILocationDependentInput>> locationDependentInputItems,
                std::vector<std::unique_ptr<Core::ITimeDependentInput>> timeDependentInputItems);

    public const Core::IProfileData& GetProfileData() const override;

    public const std::vector<std::reference_wrapper<Core::ILocationDependentInput>>& GetLocationDependentInputItems() const override;

    public const std::vector<std::reference_wrapper<Core::ITimeDependentInput>>& GetTimeDependentInputItems() const override;

            private std::unique_ptr<Core::IProfileData> _profileData;
            private std::vector<std::unique_ptr<Core::ILocationDependentInput>> _locationDependentInputItems;
            private std::vector<std::reference_wrapper<Core::ILocationDependentInput>> _locationDependentInputItemReferences;
            private std::vector<std::unique_ptr<Core::ITimeDependentInput>> _timeDependentInputItems;
            private std::vector<std::reference_wrapper<Core::ITimeDependentInput>> _timeDependentInputItemReferences;
    }
}
