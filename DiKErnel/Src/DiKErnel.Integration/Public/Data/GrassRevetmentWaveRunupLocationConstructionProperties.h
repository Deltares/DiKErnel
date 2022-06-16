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

#include "GrassRevetmentTopLayerType.h"
#include "RevetmentLocationConstructionPropertiesBase.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Construction properties to construct grass revetment wave run-up location dependent
     *        input.
     */
    class GrassRevetmentWaveRunupLocationConstructionProperties : public RevetmentLocationConstructionPropertiesBase
    {
        public:
            virtual ~GrassRevetmentWaveRunupLocationConstructionProperties() = default;

            #pragma region Set methods

            /*!
             * \brief Sets the critical cumulative overload.
             * \param criticalCumulativeOverload
             *        The critical cumulative overload.
             */
            void SetCriticalCumulativeOverload(
                std::unique_ptr<double> criticalCumulativeOverload);

            /*!
             * \brief Sets the critical front velocity.
             * \param criticalFrontVelocity
             *        The critical front velocity.
             */
            void SetCriticalFrontVelocity(
                std::unique_ptr<double> criticalFrontVelocity);

            /*!
             * \brief Sets the alpha M coefficient.
             * \param increasedLoadTransitionAlphaM
             *        The alpha M coefficient.
             */
            void SetIncreasedLoadTransitionAlphaM(
                std::unique_ptr<double> increasedLoadTransitionAlphaM);

            /*!
             * \brief Sets the alpha S coefficient.
             * \param reducedStrengthTransitionAlphaS
             *        The alpha S coefficient.
             */
            void SetReducedStrengthTransitionAlphaS(
                std::unique_ptr<double> reducedStrengthTransitionAlphaS);

            /*!
             * \brief Sets the Ctm coefficient.
             * \param averageNumberOfWavesCtm
             *        The Ctm coefficient.
             */
            void SetAverageNumberOfWavesCtm(
                std::unique_ptr<double> averageNumberOfWavesCtm);

            /*!
             * \brief Sets the 2P Aru coefficient.
             * \param representativeWaveRunup2PAru
             *        The 2P Aru coefficient.
             */
            void SetRepresentativeWaveRunup2PAru(
                std::unique_ptr<double> representativeWaveRunup2PAru);

            /*!
             * \brief Sets the 2P Bru coefficient.
             * \param representativeWaveRunup2PBru
             *        The 2P Bru coefficient.
             */
            void SetRepresentativeWaveRunup2PBru(
                std::unique_ptr<double> representativeWaveRunup2PBru);

            /*!
             * \brief Sets the 2P Cru coefficient.
             * \param representativeWaveRunup2PCru
             *        The 2P Cru coefficient.
             */
            void SetRepresentativeWaveRunup2PCru(
                std::unique_ptr<double> representativeWaveRunup2PCru);

            /*!
             * \brief Sets the 2P Gammab coefficient.
             * \param representativeWaveRunup2PGammab
             *        The 2P Gammab coefficient.
             */
            void SetRepresentativeWaveRunup2PGammab(
                std::unique_ptr<double> representativeWaveRunup2PGammab);

            /*!
             * \brief Sets the 2P Gammaf coefficient.
             * \param representativeWaveRunup2PGammaf
             *        The 2P Gammaf coefficient.
             */
            void SetRepresentativeWaveRunup2PGammaf(
                std::unique_ptr<double> representativeWaveRunup2PGammaf);

            /*!
             * \brief Sets the Abeta coefficient.
             * \param waveAngleImpactAbeta
             *        The Abeta coefficient.
             */
            void SetWaveAngleImpactAbeta(
                std::unique_ptr<double> waveAngleImpactAbeta);

            /*!
             * \brief Sets the Betamax coefficient.
             * \param waveAngleImpactBetamax
             *        The Betamax coefficient.
             */
            void SetWaveAngleImpactBetamax(
                std::unique_ptr<double> waveAngleImpactBetamax);

            #pragma endregion

            #pragma region Get methods

            /*!
             * \brief Gets the outer slope.
             * \return The outer slope.
             */
            [[nodiscard]]
            double GetOuterSlope() const;

            /*!
             * \brief Gets the type of the top layer.
             * \return The type of the top layer.
             */
            [[nodiscard]]
            GrassRevetmentTopLayerType GetTopLayerType() const;

            /*!
             * \brief Gets the critical cumulative overload.
             * \return The critical cumulative overload.
             */
            [[nodiscard]]
            const double* GetCriticalCumulativeOverload() const;

            /*!
             * \brief Gets the critical front velocity.
             * \return The critical front velocity.
             */
            [[nodiscard]]
            const double* GetCriticalFrontVelocity() const;

            /*!
             * \brief Gets the alpha M coefficient.
             * \return The alpha M coefficient.
             */
            [[nodiscard]]
            const double* GetIncreasedLoadTransitionAlphaM() const;

            /*!
             * \brief Gets the alpha S coefficient.
             * \return The alpha S coefficient.
             */
            [[nodiscard]]
            const double* GetReducedStrengthTransitionAlphaS() const;

            /*!
             * \brief Gets the Ctm coefficient.
             * \return The Ctm coefficient.
             */
            [[nodiscard]]
            const double* GetAverageNumberOfWavesCtm() const;

            /*!
             * \brief Gets the 2P Aru coefficient.
             * \return The 2P Aru coefficient.
             */
            [[nodiscard]]
            const double* GetRepresentativeWaveRunup2PAru() const;

            /*!
             * \brief Gets the 2P Bru coefficient.
             * \return The 2P Bru coefficient.
             */
            [[nodiscard]]
            const double* GetRepresentativeWaveRunup2PBru() const;

            /*!
             * \brief Gets the 2P Cru coefficient.
             * \return The 2P Cru coefficient.
             */
            [[nodiscard]]
            const double* GetRepresentativeWaveRunup2PCru() const;

            /*!
             * \brief Gets the 2P Gammab coefficient.
             * \return The 2P Gammab coefficient.
             */
            [[nodiscard]]
            const double* GetRepresentativeWaveRunup2PGammab() const;

            /*!
             * \brief Gets the 2P Gammaf coefficient.
             * \return The 2P Gammaf coefficient.
             */
            [[nodiscard]]
            const double* GetRepresentativeWaveRunup2PGammaf() const;

            /*!
             * \brief Gets the Abeta coefficient.
             * \return The Abeta coefficient.
             */
            [[nodiscard]]
            const double* GetWaveAngleImpactAbeta() const;

            /*!
             * \brief Gets the Betamax coefficient.
             * \return The Betamax coefficient.
             */
            [[nodiscard]]
            const double* GetWaveAngleImpactBetamax() const;

            #pragma endregion

        protected:
            /*!
             * \brief Creates a new instance.
             * \param x
             *        The x coordinate.
             * \param outerSlope
             *        The outer slope.
             * \param topLayerType
             *        The type of the top layer.
             */
            explicit GrassRevetmentWaveRunupLocationConstructionProperties(
                double x,
                double outerSlope,
                GrassRevetmentTopLayerType topLayerType);

        private:
            double _outerSlope;
            GrassRevetmentTopLayerType _topLayerType;
            std::unique_ptr<double> _criticalCumulativeOverload = nullptr;
            std::unique_ptr<double> _criticalFrontVelocity = nullptr;
            std::unique_ptr<double> _increasedLoadTransitionAlphaM = nullptr;
            std::unique_ptr<double> _reducedStrengthTransitionAlphaS = nullptr;
            std::unique_ptr<double> _averageNumberOfWavesCtm = nullptr;
            std::unique_ptr<double> _representativeWaveRunup2PAru = nullptr;
            std::unique_ptr<double> _representativeWaveRunup2PBru = nullptr;
            std::unique_ptr<double> _representativeWaveRunup2PCru = nullptr;
            std::unique_ptr<double> _representativeWaveRunup2PGammab;
            std::unique_ptr<double> _representativeWaveRunup2PGammaf;
            std::unique_ptr<double> _waveAngleImpactAbeta = nullptr;
            std::unique_ptr<double> _waveAngleImpactBetamax = nullptr;
    };
}
