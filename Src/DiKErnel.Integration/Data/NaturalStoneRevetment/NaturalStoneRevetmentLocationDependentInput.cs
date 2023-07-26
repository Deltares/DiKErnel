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
    internal class NaturalStoneRevetmentLocationDependentInput : LocationDependentInput
    {
        public void NaturalStoneRevetmentLocationDependentInput(
                double x,
                double initialDamage,
                double failureNumber,
                double relativeDensity,
                double thicknessTopLayer,
                unique_ptr<NaturalStoneRevetmentHydraulicLoads> hydraulicLoads,
                unique_ptr<NaturalStoneRevetmentSlope> slope,
                unique_ptr<NaturalStoneRevetmentUpperLimitLoading> upperLimitLoading,
                unique_ptr<NaturalStoneRevetmentLowerLimitLoading> lowerLimitLoading,
                unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> distanceMaximumWaveElevation,
                unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> normativeWidthOfWaveImpact,
                unique_ptr<NaturalStoneRevetmentWaveAngleImpact> waveAngleImpact);

    public double GetRelativeDensity();

    public double GetThicknessTopLayer();

    public NaturalStoneRevetmentHydraulicLoads& GetHydraulicLoads();

    public NaturalStoneRevetmentSlope& GetSlope();

    public NaturalStoneRevetmentUpperLimitLoading& GetUpperLimitLoading();

    public NaturalStoneRevetmentLowerLimitLoading& GetLowerLimitLoading();

    public NaturalStoneRevetmentDistanceMaximumWaveElevation& GetDistanceMaximumWaveElevation();

    public NaturalStoneRevetmentNormativeWidthOfWaveImpact& GetNormativeWidthOfWaveImpact();

    public NaturalStoneRevetmentWaveAngleImpact& GetWaveAngleImpact();

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

            private double _relativeDensity;
            private double _thicknessTopLayer;
            private unique_ptr<NaturalStoneRevetmentHydraulicLoads> _hydraulicLoadsInput;
            private unique_ptr<NaturalStoneRevetmentSlope> _slopeInput;
            private unique_ptr<NaturalStoneRevetmentUpperLimitLoading> _upperLimitLoadingInput;
            private unique_ptr<NaturalStoneRevetmentLowerLimitLoading> _lowerLimitLoadingInput;
            private unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> _distanceMaximumWaveElevationInput;
            private unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> _normativeWidthOfWaveImpactInput;
            private unique_ptr<NaturalStoneRevetmentWaveAngleImpact> _waveAngleImpactInput;
            private double _outerToeHeight = numeric_limits<double>::infinity();
            private double _outerCrestHeight = numeric_limits<double>::infinity();
            private unique_ptr<pair<double, double>> _notchOuterBerm = nullptr;
            private unique_ptr<pair<double, double>> _crestOuterBerm = nullptr;

            private double _resistance = numeric_limits<double>::infinity();
            private double _slopeLowerPosition = numeric_limits<double>::infinity();
            private double _slopeLowerLevel = numeric_limits<double>::infinity();
            private double _slopeUpperPosition = numeric_limits<double>::infinity();
            private double _slopeUpperLevel = numeric_limits<double>::infinity();
            private double _outerSlope = numeric_limits<double>::infinity();
            private double _waveSteepnessDeepWater = numeric_limits<double>::infinity();
            private double _distanceMaximumWaveElevation = numeric_limits<double>::infinity();
            private double _surfSimilarityParameter = numeric_limits<double>::infinity();
            private double _normativeWidthWaveImpact = numeric_limits<double>::infinity();
            private double _depthMaximumWaveLoad = numeric_limits<double>::infinity();
            private double _upperLimitLoading = numeric_limits<double>::infinity();
            private double _lowerLimitLoading = numeric_limits<double>::infinity();
            private bool _loadingRevetment = false;
            private double _hydraulicLoad = numeric_limits<double>::infinity();
            private double _waveAngleImpact = numeric_limits<double>::infinity();
            private double _referenceTimeDegradation = numeric_limits<double>::infinity();
            private double _referenceDegradation = numeric_limits<double>::infinity();

    private double CalculateOuterSlope(
                double waterLevel,
                double waveHeightHm0,
                IProfileData& profileData);

    private bool CalculateLoadingRevetment(
                double depthMaximumWaveLoad,
                double surfSimilarityParameter,
                double waterLevel,
                double waveHeightHm0);

    private double CalculateHydraulicLoad(
                double surfSimilarityParameter,
                double waveHeightHm0);

    private int CalculateTimeOfFailure(
                double failureNumber,
                double wavePeriodTm10,
                double beginTime);

    private unique_ptr<NaturalStoneRevetmentTimeDependentOutputConstructionProperties> CreateConstructionProperties(
                double incrementDamage,
                double damage,
                int? timeOfFailure);
    }
}
