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
                std::unique_ptr<GrassRevetmentWaveImpactWaveAngleImpact> waveAngleImpact,
                double minimumWaveHeightTemax,
                double maximumWaveHeightTemin,
                std::unique_ptr<GrassRevetmentWaveImpactTimeLine> timeLine,
                double upperLimitLoadingAul,
                double lowerLimitLoadingAll);

    public GrassRevetmentWaveImpactWaveAngleImpact& GetWaveAngleImpact();

    public double GetMinimumWaveHeightTemax();

    public double GetMaximumWaveHeightTemin();

    public GrassRevetmentWaveImpactTimeLine& GetTimeLine();

    public double GetUpperLimitLoadingAul();

    public double GetLowerLimitLoadingAll();

    public bool Validate(
                const std::vector<std::reference_wrapper<Core::ITimeDependentInput>>& timeDependentInputs,
                const Core::IProfileData& profileData) override;

    public std::unique_ptr<Core::LocationDependentOutput> GetLocationDependentOutput(
                std::vector<std::unique_ptr<Core::TimeDependentOutput>> timeDependentOutputItems) override;

    protected void InitializeDerivedLocationDependentInput(
                const Core::IProfileData& profileData) override;

    protected std::unique_ptr<Core::TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                const Core::ITimeDependentInput& timeDependentInput,
                const Core::IProfileData& profileData) override;

            private std::unique_ptr<GrassRevetmentWaveImpactWaveAngleImpact> _waveAngleImpactInput;
            private double _minimumWaveHeightTemax;
            private double _maximumWaveHeightTemin;
            private std::unique_ptr<GrassRevetmentWaveImpactTimeLine> _timeLine;
            private double _upperLimitLoadingAul;
            private double _lowerLimitLoadingAll;

            private double _minimumWaveHeight = std::numeric_limits<double>::infinity();
            private double _maximumWaveHeight = std::numeric_limits<double>::infinity();
            private double _lowerLimitLoading = std::numeric_limits<double>::infinity();
            private double _upperLimitLoading = std::numeric_limits<double>::infinity();
            private bool _loadingRevetment = false;
            private double _waveAngleImpact = std::numeric_limits<double>::infinity();
            private double _waveHeightImpact = std::numeric_limits<double>::infinity();

    private bool CalculateLoadingRevetment(
                double waterLevel,
                double waveHeightHm0);

    private std::unique_ptr<GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties> CreateConstructionProperties(
                double incrementDamage,
                double damage,
                std::unique_ptr<int> timeOfFailure);
    }
}
