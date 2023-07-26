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
                GrassRevetmentWaveImpactWaveAngleImpact waveAngleImpact,
                double minimumWaveHeightTemax,
                double maximumWaveHeightTemin,
                GrassRevetmentWaveImpactTimeLine timeLine,
                double upperLimitLoadingAul,
                double lowerLimitLoadingAll);

    public GrassRevetmentWaveImpactWaveAngleImpact& GetWaveAngleImpact();

    public double GetMinimumWaveHeightTemax();

    public double GetMaximumWaveHeightTemin();

    public GrassRevetmentWaveImpactTimeLine& GetTimeLine();

    public double GetUpperLimitLoadingAul();

    public double GetLowerLimitLoadingAll();

    public bool Validate(
                vector<reference_wrapper<ITimeDependentInput>>& timeDependentInputs,
                IProfileData& profileData) override;

    public LocationDependentOutput GetLocationDependentOutput(
                vector<TimeDependentOutput> timeDependentOutputItems) override;

    protected void InitializeDerivedLocationDependentInput(
                IProfileData& profileData) override;

    protected TimeDependentOutput CalculateTimeDependentOutput(
                double initialDamage,
                ITimeDependentInput& timeDependentInput,
                IProfileData& profileData) override;

            private GrassRevetmentWaveImpactWaveAngleImpact _waveAngleImpactInput;
            private double _minimumWaveHeightTemax;
            private double _maximumWaveHeightTemin;
            private GrassRevetmentWaveImpactTimeLine _timeLine;
            private double _upperLimitLoadingAul;
            private double _lowerLimitLoadingAll;

            private double _minimumWaveHeight = double.PositiveInfinity;
            private double _maximumWaveHeight = double.PositiveInfinity;
            private double _lowerLimitLoading = double.PositiveInfinity;
            private double _upperLimitLoading = double.PositiveInfinity;
            private bool _loadingRevetment = false;
            private double _waveAngleImpact = double.PositiveInfinity;
            private double _waveHeightImpact = double.PositiveInfinity;

    private bool CalculateLoadingRevetment(
                double waterLevel,
                double waveHeightHm0);

    private GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties CreateConstructionProperties(
                double incrementDamage,
                double damage,
                int? timeOfFailure);
    }
}
