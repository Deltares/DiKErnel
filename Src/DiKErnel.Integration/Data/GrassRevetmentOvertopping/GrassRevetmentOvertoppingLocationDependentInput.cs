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
    class GrassRevetmentOvertoppingLocationDependentInput : public LocationDependentInput
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

    public double GetCriticalCumulativeOverload() const;

    public double GetCriticalFrontVelocity() const;

    public double GetIncreasedLoadTransitionAlphaM() const;

    public double GetReducedStrengthTransitionAlphaS() const;

    public double GetAverageNumberOfWavesCtm() const;

    public int GetFixedNumberOfWaves() const;

    public double GetFrontVelocityCwo() const;

    public GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA& GetLocationDependentAccelerationAlphaA() const;

    public const double* GetEnforcedDikeHeight() const;

    public bool Validate(
                const std::vector<std::reference_wrapper<Core::ITimeDependentInput>>& timeDependentInputs,
                const Core::IProfileData& profileData) const override;

    public std::unique_ptr<Core::LocationDependentOutput> GetLocationDependentOutput(
                std::vector<std::unique_ptr<Core::TimeDependentOutput>> timeDependentOutputItems) override;

    protected void InitializeDerivedLocationDependentInput(
                const Core::IProfileData& profileData) override;

    protected std::unique_ptr<Core::TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                const Core::ITimeDependentInput& timeDependentInput,
                const Core::IProfileData& profileData) override;

        private:
            const double _criticalCumulativeOverload;
            const double _criticalFrontVelocity;
            const double _increasedLoadTransitionAlphaM;
            const double _reducedStrengthTransitionAlphaS;
            const double _averageNumberOfWavesCtm;
            const int _fixedNumberOfWaves;
            const double _frontVelocityCwo;
            std::unique_ptr<GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA> _locationDependentAccelerationAlphaA;
            std::unique_ptr<double> _enforcedDikeHeight;

            std::vector<double> _xValuesProfile;
            std::vector<double> _zValuesProfile;
            std::vector<double> _roughnessCoefficients;
            double _dikeHeight = std::numeric_limits<double>::infinity();
            double _accelerationAlphaA = std::numeric_limits<double>::infinity();

            double _verticalDistanceWaterLevelElevation = std::numeric_limits<double>::infinity();
            double _representativeWaveRunup2P = std::numeric_limits<double>::infinity();
            double _cumulativeOverload = std::numeric_limits<double>::infinity();

            void InitializeCalculationProfile(
                const std::pair<double, double>& outerToe,
                const std::pair<double, double>& outerCrest,
                const std::vector<std::reference_wrapper<Core::ProfileSegment>>& profileSegments);

            void InitializeDikeHeight(
                const std::pair<double, double>& outerCrest,
                const std::vector<std::reference_wrapper<Core::ProfileSegment>>& profileSegments);

            void InitializeAccelerationAlphaA(
                const std::pair<double, double>& outerCrest,
                const std::pair<double, double>& innerCrest);

            double CalculateRepresentativeWaveRunup2P(
                double waterLevel,
                double waveHeightHm0,
                double wavePeriodTm10,
                double waveDirection) const;

            double CalculateCumulativeOverload(
                double averageNumberOfWaves) const;

            double CalculateDikeHeight(
                const std::pair<double, double>& outerCrest,
                const std::vector<std::reference_wrapper<Core::ProfileSegment>>& profileSegments,
                double locationHeight) const;

            std::unique_ptr<GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties> CreateConstructionProperties(
                double incrementDamage,
                double damage,
                std::unique_ptr<int> timeOfFailure);
    };
}
