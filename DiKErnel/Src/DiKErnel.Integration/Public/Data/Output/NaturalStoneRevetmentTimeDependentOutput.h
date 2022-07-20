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

#include "NaturalStoneRevetmentTimeDependentOutputConstructionProperties.h"
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
             * \param constructionProperties
             *        The construction properties.
             */
            explicit NaturalStoneRevetmentTimeDependentOutput(
                NaturalStoneRevetmentTimeDependentOutputConstructionProperties& constructionProperties);

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
            std::unique_ptr<double> _outerSlope = nullptr;
            std::unique_ptr<double> _slopeUpperLevel = nullptr;
            std::unique_ptr<double> _slopeUpperPosition = nullptr;
            std::unique_ptr<double> _slopeLowerLevel = nullptr;
            std::unique_ptr<double> _slopeLowerPosition = nullptr;
            std::unique_ptr<bool> _loadingRevetment = nullptr;
            std::unique_ptr<double> _surfSimilarityParameter = nullptr;
            std::unique_ptr<double> _waveSteepnessDeepWater = nullptr;
            std::unique_ptr<double> _upperLimitLoading = nullptr;
            std::unique_ptr<double> _lowerLimitLoading = nullptr;
            std::unique_ptr<double> _depthMaximumWaveLoad = nullptr;
            std::unique_ptr<double> _distanceMaximumWaveElevation = nullptr;
            std::unique_ptr<double> _normativeWidthOfWaveImpact = nullptr;
            std::unique_ptr<double> _hydraulicLoad = nullptr;
            std::unique_ptr<double> _waveAngleImpact = nullptr;
            std::unique_ptr<double> _resistance = nullptr;
            std::unique_ptr<double> _referenceTimeDegradation = nullptr;
            std::unique_ptr<double> _referenceDegradation = nullptr;
    };
}
