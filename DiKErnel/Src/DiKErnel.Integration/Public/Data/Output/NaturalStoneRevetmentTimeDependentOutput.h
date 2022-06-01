// Copyright (C) Stichting Deltares 2022. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#pragma once

#include "TimeDependentOutput.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Time dependent output of a natural stone revetment location.
     */
    class NaturalStoneRevetmentTimeDependentOutput : public Core::TimeDependentOutput
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param incrementDamage
             *        The increment damage.
             * \param damage
             *        The damage.
             * \param timeOfFailure
             *        The time of failure.
             * \param outerSlope
             *        The outer slope.
             * \param slopeUpperLevel
             *        The slope upper level.
             * \param slopeUpperPosition
             *        The slope upper position.
             * \param slopeLowerLevel
             *        The slope lower level.
             * \param slopeLowerPosition
             *        The slope lower position.
             * \param loadingRevetment
             *        The loading revetment.
             * \param surfSimilarityParameter
             *        The surf similarity parameter.
             * \param waveSteepnessDeepWater
             *        The wave steepness deep water.
             * \param upperLimitLoading
             *        The upper limit loading.
             * \param lowerLimitLoading
             *        The lower limit loading.
             * \param depthMaximumWaveLoad
             *        The depth maximum wave load.
             * \param distanceMaximumWaveElevation
             *        The distance maximum wave elevation.
             * \param normativeWidthOfWaveImpact
             *        The normative width of wave impact.
             * \param waveAngleImpact
             *        The wave angle impact.
             * \param hydraulicLoad
             *        The hydraulic load.
             * \param resistance
             *        The resistance.
             * \param referenceTimeDegradation
             *        The reference time degradation.
             * \param referenceDegradation
             *        The reference degradation.
             */
            explicit NaturalStoneRevetmentTimeDependentOutput(
                double incrementDamage,
                double damage,
                std::unique_ptr<int> timeOfFailure,
                double outerSlope,
                double slopeUpperLevel,
                double slopeUpperPosition,
                double slopeLowerLevel,
                double slopeLowerPosition,
                bool loadingRevetment,
                double surfSimilarityParameter,
                double waveSteepnessDeepWater,
                double upperLimitLoading,
                double lowerLimitLoading,
                double depthMaximumWaveLoad,
                double distanceMaximumWaveElevation,
                double normativeWidthOfWaveImpact,
                std::unique_ptr<double> hydraulicLoad,
                std::unique_ptr<double> waveAngleImpact,
                std::unique_ptr<double> resistance,
                std::unique_ptr<double> referenceTimeDegradation,
                std::unique_ptr<double> referenceDegradation);

            /*!
             * \brief Gets the outer slope.
             * \return The outer slope.
             */
            [[nodiscard]]
            double GetOuterSlope() const;

            /*!
             * \brief Gets the slope upper level.
             * \return The slope upper level.
             */
            [[nodiscard]]
            double GetSlopeUpperLevel() const;

            /*!
             * \brief Gets the slope upper position.
             * \return The slope upper position.
             */
            [[nodiscard]]
            double GetSlopeUpperPosition() const;

            /*!
             * \brief Gets the slope lower level.
             * \return The slope lower level.
             */
            [[nodiscard]]
            double GetSlopeLowerLevel() const;

            /*!
             * \brief Gets the slope lower position.
             * \return The slope lower position.
             */
            [[nodiscard]]
            double GetSlopeLowerPosition() const;

            /*!
             * \brief Gets the loading revetment.
             * \return The loading revetment.
             */
            [[nodiscard]]
            bool GetLoadingRevetment() const;

            /*!
             * \brief Gets the surf similarity parameter.
             * \return The surf similarity parameter.
             */
            [[nodiscard]]
            double GetSurfSimilarityParameter() const;

            /*!
             * \brief Gets the wave steepness deep water.
             * \return The wave steepness deep water.
             */
            [[nodiscard]]
            double GetWaveSteepnessDeepWater() const;

            /*!
             * \brief Gets the upper limit loading.
             * \return The upper limit loading.
             */
            [[nodiscard]]
            double GetUpperLimitLoading() const;

            /*!
             * \brief Gets the lower limit loading.
             * \return The lower limit loading.
             */
            [[nodiscard]]
            double GetLowerLimitLoading() const;

            /*!
             * \brief Gets the depth maximum wave load.
             * \return The depth maximum wave load.
             */
            [[nodiscard]]
            double GetDepthMaximumWaveLoad() const;

            /*!
             * \brief Gets the distance maximum wave elevation.
             * \return The distance maximum wave elevation.
             */
            [[nodiscard]]
            double GetDistanceMaximumWaveElevation() const;

            /*!
             * \brief Gets the normative width of wave impact.
             * \return The normative width of wave impact.
             */
            [[nodiscard]]
            double GetNormativeWidthOfWaveImpact() const;

            /*!
             * \brief Gets the hydraulic load.
             * \return The hydraulic load.
             */
            [[nodiscard]]
            const double* GetHydraulicLoad() const;

            /*!
             * \brief Gets the wave angle impact.
             * \return The wave angle impact.
             */
            [[nodiscard]]
            const double* GetWaveAngleImpact() const;

            /*!
             * \brief Gets the resistance.
             * \return The resistance.
             */
            [[nodiscard]]
            const double* GetResistance() const;

            /*!
             * \brief Gets the reference time degradation.
             * \return The reference time degradation.
             */
            [[nodiscard]]
            const double* GetReferenceTimeDegradation() const;

            /*!
             * \brief Gets the reference degradation.
             * \return The reference degradation.
             */
            [[nodiscard]]
            const double* GetReferenceDegradation() const;

        private:
            const double _outerSlope;
            const double _slopeUpperLevel;
            const double _slopeUpperPosition;
            const double _slopeLowerLevel;
            const double _slopeLowerPosition;
            const bool _loadingRevetment;
            const double _surfSimilarityParameter;
            const double _waveSteepnessDeepWater;
            const double _upperLimitLoading;
            const double _lowerLimitLoading;
            const double _depthMaximumWaveLoad;
            const double _distanceMaximumWaveElevation;
            const double _normativeWidthOfWaveImpact;
            std::unique_ptr<double> _hydraulicLoad;
            std::unique_ptr<double> _waveAngleImpact;
            std::unique_ptr<double> _resistance;
            std::unique_ptr<double> _referenceTimeDegradation;
            std::unique_ptr<double> _referenceDegradation;
    };
}
