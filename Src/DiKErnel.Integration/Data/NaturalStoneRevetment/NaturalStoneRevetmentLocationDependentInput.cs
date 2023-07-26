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

namespace DiKErnel.Integration.Data.NaturalStoneRevetment
{
    class NaturalStoneRevetmentLocationDependentInput : public LocationDependentInput
    {
        public void NaturalStoneRevetmentLocationDependentInput(
                double x,
                double initialDamage,
                double failureNumber,
                double relativeDensity,
                double thicknessTopLayer,
                std::unique_ptr<NaturalStoneRevetmentHydraulicLoads> hydraulicLoads,
                std::unique_ptr<NaturalStoneRevetmentSlope> slope,
                std::unique_ptr<NaturalStoneRevetmentUpperLimitLoading> upperLimitLoading,
                std::unique_ptr<NaturalStoneRevetmentLowerLimitLoading> lowerLimitLoading,
                std::unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> distanceMaximumWaveElevation,
                std::unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> normativeWidthOfWaveImpact,
                std::unique_ptr<NaturalStoneRevetmentWaveAngleImpact> waveAngleImpact);

    public double GetRelativeDensity() const;

    public double GetThicknessTopLayer() const;

    public NaturalStoneRevetmentHydraulicLoads& GetHydraulicLoads() const;

    public NaturalStoneRevetmentSlope& GetSlope() const;

    public NaturalStoneRevetmentUpperLimitLoading& GetUpperLimitLoading() const;

    public NaturalStoneRevetmentLowerLimitLoading& GetLowerLimitLoading() const;

    public NaturalStoneRevetmentDistanceMaximumWaveElevation& GetDistanceMaximumWaveElevation() const;

    public NaturalStoneRevetmentNormativeWidthOfWaveImpact& GetNormativeWidthOfWaveImpact() const;

    public NaturalStoneRevetmentWaveAngleImpact& GetWaveAngleImpact() const;

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

            private double _relativeDensity;
            private double _thicknessTopLayer;
            private std::unique_ptr<NaturalStoneRevetmentHydraulicLoads> _hydraulicLoadsInput;
            private std::unique_ptr<NaturalStoneRevetmentSlope> _slopeInput;
            private std::unique_ptr<NaturalStoneRevetmentUpperLimitLoading> _upperLimitLoadingInput;
            private std::unique_ptr<NaturalStoneRevetmentLowerLimitLoading> _lowerLimitLoadingInput;
            private std::unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> _distanceMaximumWaveElevationInput;
            private std::unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> _normativeWidthOfWaveImpactInput;
            private std::unique_ptr<NaturalStoneRevetmentWaveAngleImpact> _waveAngleImpactInput;
            private double _outerToeHeight = std::numeric_limits<double>::infinity();
            private double _outerCrestHeight = std::numeric_limits<double>::infinity();
            private std::unique_ptr<std::pair<double, double>> _notchOuterBerm = nullptr;
            private std::unique_ptr<std::pair<double, double>> _crestOuterBerm = nullptr;

            private double _resistance = std::numeric_limits<double>::infinity();
            private double _slopeLowerPosition = std::numeric_limits<double>::infinity();
            private double _slopeLowerLevel = std::numeric_limits<double>::infinity();
            private double _slopeUpperPosition = std::numeric_limits<double>::infinity();
            private double _slopeUpperLevel = std::numeric_limits<double>::infinity();
            private double _outerSlope = std::numeric_limits<double>::infinity();
            private double _waveSteepnessDeepWater = std::numeric_limits<double>::infinity();
            private double _distanceMaximumWaveElevation = std::numeric_limits<double>::infinity();
            private double _surfSimilarityParameter = std::numeric_limits<double>::infinity();
            private double _normativeWidthWaveImpact = std::numeric_limits<double>::infinity();
            private double _depthMaximumWaveLoad = std::numeric_limits<double>::infinity();
            private double _upperLimitLoading = std::numeric_limits<double>::infinity();
            private double _lowerLimitLoading = std::numeric_limits<double>::infinity();
            private bool _loadingRevetment = false;
            private double _hydraulicLoad = std::numeric_limits<double>::infinity();
            private double _waveAngleImpact = std::numeric_limits<double>::infinity();
            private double _referenceTimeDegradation = std::numeric_limits<double>::infinity();
            private double _referenceDegradation = std::numeric_limits<double>::infinity();

    private double CalculateOuterSlope(
                double waterLevel,
                double waveHeightHm0,
                const Core::IProfileData& profileData);

    private bool CalculateLoadingRevetment(
                double depthMaximumWaveLoad,
                double surfSimilarityParameter,
                double waterLevel,
                double waveHeightHm0);

    private double CalculateHydraulicLoad(
                double surfSimilarityParameter,
                double waveHeightHm0) const;

    private int CalculateTimeOfFailure(
                double failureNumber,
                double wavePeriodTm10,
                double beginTime) const;

    private std::unique_ptr<NaturalStoneRevetmentTimeDependentOutputConstructionProperties> CreateConstructionProperties(
                double incrementDamage,
                double damage,
                std::unique_ptr<int> timeOfFailure);
    }
}
