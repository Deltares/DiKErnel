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
                GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA locationDependentAccelerationAlphaA,
                double? enforcedDikeHeight);

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

            private double _criticalCumulativeOverload;
            private double _criticalFrontVelocity;
            private double _increasedLoadTransitionAlphaM;
            private double _reducedStrengthTransitionAlphaS;
            private double _averageNumberOfWavesCtm;
            private int _fixedNumberOfWaves;
            private double _frontVelocityCwo;
            private GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA _locationDependentAccelerationAlphaA;
            private double? _enforcedDikeHeight;

            private vector<double> _xValuesProfile;
            private vector<double> _zValuesProfile;
            private vector<double> _roughnessCoefficients;
            private double _dikeHeight = numeric_limits<double>::infinity();
            private double _accelerationAlphaA = numeric_limits<double>::infinity();

            private double _verticalDistanceWaterLevelElevation = numeric_limits<double>::infinity();
            private double _representativeWaveRunup2P = numeric_limits<double>::infinity();
            private double _cumulativeOverload = numeric_limits<double>::infinity();

    private void InitializeCalculationProfile(
                pair<double, double>& outerToe,
                pair<double, double>& outerCrest,
                vector<reference_wrapper<ProfileSegment>>& profileSegments);

    private void InitializeDikeHeight(
                pair<double, double>& outerCrest,
                vector<reference_wrapper<ProfileSegment>>& profileSegments);

    private void InitializeAccelerationAlphaA(
                pair<double, double>& outerCrest,
                pair<double, double>& innerCrest);

    private double CalculateRepresentativeWaveRunup2P(
                double waterLevel,
                double waveHeightHm0,
                double wavePeriodTm10,
                double waveDirection);

    private double CalculateCumulativeOverload(
                double averageNumberOfWaves);

    private double CalculateDikeHeight(
                pair<double, double>& outerCrest,
                vector<reference_wrapper<ProfileSegment>>& profileSegments,
                double locationHeight);

    private GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties CreateConstructionProperties(
                double incrementDamage,
                double damage,
                int? timeOfFailure);
    }
}
