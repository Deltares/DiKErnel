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
    internal class CalculationInput : ICalculationInput
    {
        public CalculationInput(
                IProfileData profileData,
                IReadOnlyList<ILocationDependentInput> locationDependentInputItems,
                IReadOnlyList<ITimeDependentInput> timeDependentInputItems) {}

    public IProfileData GetProfileData() override;

    public IReadOnlyList<ILocationDependentInput> GetLocationDependentInputItems() override;

    public IReadOnlyList<ITimeDependentInput> GetTimeDependentInputItems() override;

            private IProfileData _profileData;
            private IReadOnlyList<ILocationDependentInput> _locationDependentInputItems;
            private IReadOnlyList<ILocationDependentInput> _locationDependentInputItemReferences;
            private IReadOnlyList<ITimeDependentInput> _timeDependentInputItems;
            private IReadOnlyList<ITimeDependentInput> _timeDependentInputItemReferences;
    }
}
