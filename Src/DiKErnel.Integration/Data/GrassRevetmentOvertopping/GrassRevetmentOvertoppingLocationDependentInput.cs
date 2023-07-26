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

namespace DiKErnel.Integration.Data.GrassRevetmentOvertopping
{
    internal class GrassRevetmentOvertoppingLocationDependentInput : LocationDependentInput
    {
        public void GrassRevetmentOvertoppingLocationDependentInput(
                double x,
                double initialDamage,
                double failureNumber,
                double criticalCumulativeOverload,
                double criticalFrontVelocity,
                double increasedLoadTransitionAlphaM,
                double reducedStrengthTransitionAlphaS,
                double averageNumberOfWavesCtm,
                int fixedNumberOfWaves,
                double frontVelocityCwo,
                std::unique_ptr<GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA> locationDependentAccelerationAlphaA,
                std::unique_ptr<double> enforcedDikeHeight);

    public double GetCriticalCumulativeOverload();

    public double GetCriticalFrontVelocity();

    public double GetIncreasedLoadTransitionAlphaM();

    public double GetReducedStrengthTransitionAlphaS();

    public double GetAverageNumberOfWavesCtm();

    public int GetFixedNumberOfWaves();

    public double GetFrontVelocityCwo();

    public GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA& GetLocationDependentAccelerationAlphaA();

    public double* GetEnforcedDikeHeight();

    public bool Validate(
                std::vector<std::reference_wrapper<Core::ITimeDependentInput>>& timeDependentInputs,
                Core::IProfileData& profileData) override;

    public std::unique_ptr<Core::LocationDependentOutput> GetLocationDependentOutput(
                std::vector<std::unique_ptr<Core::TimeDependentOutput>> timeDependentOutputItems) override;

    protected void InitializeDerivedLocationDependentInput(
                Core::IProfileData& profileData) override;

    protected std::unique_ptr<Core::TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                Core::ITimeDependentInput& timeDependentInput,
                Core::IProfileData& profileData) override;

            private double _criticalCumulativeOverload;
            private double _criticalFrontVelocity;
            private double _increasedLoadTransitionAlphaM;
            private double _reducedStrengthTransitionAlphaS;
            private double _averageNumberOfWavesCtm;
            private int _fixedNumberOfWaves;
            private double _frontVelocityCwo;
            private std::unique_ptr<GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA> _locationDependentAccelerationAlphaA;
            private std::unique_ptr<double> _enforcedDikeHeight;

            private std::vector<double> _xValuesProfile;
            private std::vector<double> _zValuesProfile;
            private std::vector<double> _roughnessCoefficients;
            private double _dikeHeight = std::numeric_limits<double>::infinity();
            private double _accelerationAlphaA = std::numeric_limits<double>::infinity();

            private double _verticalDistanceWaterLevelElevation = std::numeric_limits<double>::infinity();
            private double _representativeWaveRunup2P = std::numeric_limits<double>::infinity();
            private double _cumulativeOverload = std::numeric_limits<double>::infinity();

    private void InitializeCalculationProfile(
                std::pair<double, double>& outerToe,
                std::pair<double, double>& outerCrest,
                std::vector<std::reference_wrapper<Core::ProfileSegment>>& profileSegments);

    private void InitializeDikeHeight(
                std::pair<double, double>& outerCrest,
                std::vector<std::reference_wrapper<Core::ProfileSegment>>& profileSegments);

    private void InitializeAccelerationAlphaA(
                std::pair<double, double>& outerCrest,
                std::pair<double, double>& innerCrest);

    private double CalculateRepresentativeWaveRunup2P(
                double waterLevel,
                double waveHeightHm0,
                double wavePeriodTm10,
                double waveDirection);

    private double CalculateCumulativeOverload(
                double averageNumberOfWaves);

    private double CalculateDikeHeight(
                std::pair<double, double>& outerCrest,
                std::vector<std::reference_wrapper<Core::ProfileSegment>>& profileSegments,
                double locationHeight);

    private std::unique_ptr<GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties> CreateConstructionProperties(
                double incrementDamage,
                double damage,
                std::unique_ptr<int> timeOfFailure);
    }
}
