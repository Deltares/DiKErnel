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

namespace DiKErnel.Integration.Data.GrassRevetmentWaveImpact
{
    internal class GrassRevetmentWaveImpactLocationDependentInput : LocationDependentInput
    {
        public void GrassRevetmentWaveImpactLocationDependentInput(
                double x,
                double initialDamage,
                double failureNumber,
                unique_ptr<GrassRevetmentWaveImpactWaveAngleImpact> waveAngleImpact,
                double minimumWaveHeightTemax,
                double maximumWaveHeightTemin,
                unique_ptr<GrassRevetmentWaveImpactTimeLine> timeLine,
                double upperLimitLoadingAul,
                double lowerLimitLoadingAll);

    public GrassRevetmentWaveImpactWaveAngleImpact& GetWaveAngleImpact();

    public double GetMinimumWaveHeightTemax();

    public double GetMaximumWaveHeightTemin();

    public GrassRevetmentWaveImpactTimeLine& GetTimeLine();

    public double GetUpperLimitLoadingAul();

    public double GetLowerLimitLoadingAll();

    public bool Validate(
                vector<reference_wrapper<Core::ITimeDependentInput>>& timeDependentInputs,
                Core::IProfileData& profileData) override;

    public unique_ptr<Core::LocationDependentOutput> GetLocationDependentOutput(
                vector<unique_ptr<Core::TimeDependentOutput>> timeDependentOutputItems) override;

    protected void InitializeDerivedLocationDependentInput(
                Core::IProfileData& profileData) override;

    protected unique_ptr<Core::TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                Core::ITimeDependentInput& timeDependentInput,
                Core::IProfileData& profileData) override;

            private unique_ptr<GrassRevetmentWaveImpactWaveAngleImpact> _waveAngleImpactInput;
            private double _minimumWaveHeightTemax;
            private double _maximumWaveHeightTemin;
            private unique_ptr<GrassRevetmentWaveImpactTimeLine> _timeLine;
            private double _upperLimitLoadingAul;
            private double _lowerLimitLoadingAll;

            private double _minimumWaveHeight = numeric_limits<double>::infinity();
            private double _maximumWaveHeight = numeric_limits<double>::infinity();
            private double _lowerLimitLoading = numeric_limits<double>::infinity();
            private double _upperLimitLoading = numeric_limits<double>::infinity();
            private bool _loadingRevetment = false;
            private double _waveAngleImpact = numeric_limits<double>::infinity();
            private double _waveHeightImpact = numeric_limits<double>::infinity();

    private bool CalculateLoadingRevetment(
                double waterLevel,
                double waveHeightHm0);

    private unique_ptr<GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties> CreateConstructionProperties(
                double incrementDamage,
                double damage,
                unique_ptr<int> timeOfFailure);
    }
}
