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

namespace DiKErnel.Integration.Data.GrassRevetmentWaveRunup
{
    internal class GrassRevetmentWaveRunupLocationDependentInput : public LocationDependentInput
    {
    public double GetOuterSlope() const;

    public double GetCriticalCumulativeOverload() const;

    public double GetCriticalFrontVelocity() const;

    public double GetIncreasedLoadTransitionAlphaM() const;

    public double GetReducedStrengthTransitionAlphaS() const;

    public double GetAverageNumberOfWavesCtm() const;

    public GrassRevetmentWaveRunupRepresentative2P& GetRepresentative2P() const;

    public GrassRevetmentWaveRunupWaveAngleImpact& GetWaveAngleImpact() const;

    public bool Validate(
                const std::vector<std::reference_wrapper<Core::ITimeDependentInput>>& timeDependentInputs,
                const Core::IProfileData& profileData) const override;

        protected void GrassRevetmentWaveRunupLocationDependentInput(
                double x,
                double initialDamage,
                double failureNumber,
                double outerSlope,
                double criticalCumulativeOverload,
                double criticalFrontVelocity,
                double increasedLoadTransitionAlphaM,
                double reducedStrengthTransitionAlphaS,
                double averageNumberOfWavesCtm,
                std::unique_ptr<GrassRevetmentWaveRunupRepresentative2P> representative2P,
                std::unique_ptr<GrassRevetmentWaveRunupWaveAngleImpact> waveAngleImpact);

    protected std::unique_ptr<Core::TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                const Core::ITimeDependentInput& timeDependentInput,
                const Core::IProfileData& profileData) override = 0;

            private double _outerSlope;
            private double _criticalCumulativeOverload;
            private double _criticalFrontVelocity;
            private double _increasedLoadTransitionAlphaM;
            private double _reducedStrengthTransitionAlphaS;
            private double _averageNumberOfWavesCtm;
            private std::unique_ptr<GrassRevetmentWaveRunupRepresentative2P> _representative2P;
            private std::unique_ptr<GrassRevetmentWaveRunupWaveAngleImpact> _waveAngleImpactInput;
    }
}
