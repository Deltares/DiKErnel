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
        public NaturalStoneRevetmentLocationDependentInput(
                double x,
                double initialDamage,
                double failureNumber,
                double relativeDensity,
                double thicknessTopLayer,
                NaturalStoneRevetmentHydraulicLoads hydraulicLoads,
                NaturalStoneRevetmentSlope slope,
                NaturalStoneRevetmentUpperLimitLoading upperLimitLoading,
                NaturalStoneRevetmentLowerLimitLoading lowerLimitLoading,
                NaturalStoneRevetmentDistanceMaximumWaveElevation distanceMaximumWaveElevation,
                NaturalStoneRevetmentNormativeWidthOfWaveImpact normativeWidthOfWaveImpact,
                NaturalStoneRevetmentWaveAngleImpact waveAngleImpact) {}

    public double GetRelativeDensity();

    public double GetThicknessTopLayer();

    public NaturalStoneRevetmentHydraulicLoads GetHydraulicLoads();

    public NaturalStoneRevetmentSlope GetSlope();

    public NaturalStoneRevetmentUpperLimitLoading GetUpperLimitLoading();

    public NaturalStoneRevetmentLowerLimitLoading GetLowerLimitLoading();

    public NaturalStoneRevetmentDistanceMaximumWaveElevation GetDistanceMaximumWaveElevation();

    public NaturalStoneRevetmentNormativeWidthOfWaveImpact GetNormativeWidthOfWaveImpact();

    public NaturalStoneRevetmentWaveAngleImpact GetWaveAngleImpact();

    public bool Validate(
                IReadOnlyList<ITimeDependentInput> timeDependentInputs,
                IProfileData profileData) override;

    public LocationDependentOutput GetLocationDependentOutput(
                IReadOnlyList<TimeDependentOutput> timeDependentOutputItems) override;

    protected void InitializeDerivedLocationDependentInput(
                IProfileData profileData) override;

    protected TimeDependentOutput CalculateTimeDependentOutput(
                double initialDamage,
                ITimeDependentInput timeDependentInput,
                IProfileData profileData) override;

            private double _relativeDensity;
            private double _thicknessTopLayer;
            private NaturalStoneRevetmentHydraulicLoads _hydraulicLoadsInput;
            private NaturalStoneRevetmentSlope _slopeInput;
            private NaturalStoneRevetmentUpperLimitLoading _upperLimitLoadingInput;
            private NaturalStoneRevetmentLowerLimitLoading _lowerLimitLoadingInput;
            private NaturalStoneRevetmentDistanceMaximumWaveElevation _distanceMaximumWaveElevationInput;
            private NaturalStoneRevetmentNormativeWidthOfWaveImpact _normativeWidthOfWaveImpactInput;
            private NaturalStoneRevetmentWaveAngleImpact _waveAngleImpactInput;
            private double _outerToeHeight = double.PositiveInfinity;
            private double _outerCrestHeight = double.PositiveInfinity;
            private pair<double, double>? _notchOuterBerm = nullptr;
            private pair<double, double>? _crestOuterBerm = nullptr;

            private double _resistance = double.PositiveInfinity;
            private double _slopeLowerPosition = double.PositiveInfinity;
            private double _slopeLowerLevel = double.PositiveInfinity;
            private double _slopeUpperPosition = double.PositiveInfinity;
            private double _slopeUpperLevel = double.PositiveInfinity;
            private double _outerSlope = double.PositiveInfinity;
            private double _waveSteepnessDeepWater = double.PositiveInfinity;
            private double _distanceMaximumWaveElevation = double.PositiveInfinity;
            private double _surfSimilarityParameter = double.PositiveInfinity;
            private double _normativeWidthWaveImpact = double.PositiveInfinity;
            private double _depthMaximumWaveLoad = double.PositiveInfinity;
            private double _upperLimitLoading = double.PositiveInfinity;
            private double _lowerLimitLoading = double.PositiveInfinity;
            private bool _loadingRevetment = false;
            private double _hydraulicLoad = double.PositiveInfinity;
            private double _waveAngleImpact = double.PositiveInfinity;
            private double _referenceTimeDegradation = double.PositiveInfinity;
            private double _referenceDegradation = double.PositiveInfinity;

    private double CalculateOuterSlope(
                double waterLevel,
                double waveHeightHm0,
                IProfileData profileData);

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

    private NaturalStoneRevetmentTimeDependentOutputConstructionProperties CreateConstructionProperties(
                double incrementDamage,
                double damage,
                int? timeOfFailure);
    }
}
