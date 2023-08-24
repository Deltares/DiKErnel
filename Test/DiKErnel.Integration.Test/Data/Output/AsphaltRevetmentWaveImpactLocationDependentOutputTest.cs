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

using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.Output
{
    [TestFixture]
    public class AsphaltRevetmentWaveImpactLocationDependentOutputTest
    {
        
    }
    
    [Test]
    public void Constructor_ExpectedValues()
    {
        // Setup
        var incrementDamage = 0.1;
        var damage = 0.2;
        var timeOfFailure = 3;
        var z = 0.4;
        var outerSlope = 0.5;

        var timeDependentOutputItems = vector<unique_ptr<TimeDependentOutput>>();

        TimeDependentOutputConstructionProperties timeDependentOutputConstructionProperties;
        timeDependentOutputConstructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        timeDependentOutputConstructionProperties._damage = make_unique<double>(damage);
        timeDependentOutputConstructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);

        timeDependentOutputItems.push_back(make_unique<TimeDependentOutputMock>(timeDependentOutputConstructionProperties));

        // Call
        const AsphaltRevetmentWaveImpactLocationDependentOutput output(move(timeDependentOutputItems), z, outerSlope);

        // Assert
        AssertHelper::AssertIsInstanceOf<LocationDependentOutput>(&output);
        ASSERT_EQ(vector{ damage }, output.GetDamages());
        ASSERT_EQ(timeOfFailure, *output.GetTimeOfFailure());
        ASSERT_EQ(1, output.GetTimeDependentOutputItems().size());
        ASSERT_DOUBLE_EQ(z, output.GetZ());
        ASSERT_DOUBLE_EQ(outerSlope, output.GetOuterSlope());
    }
}
