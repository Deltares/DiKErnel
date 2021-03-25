// Copyright (C) Stichting Deltares 2020. All rights reserved.
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

#include <memory>
#include <string>

namespace DiKErnel::Integration
{
    /*!
     * \brief Construction properties to construct natural stone revetment location dependent
     *        input.
     */
    class NaturalStoneRevetmentLocationConstructionProperties
    {
        public:

            /*!
             * \brief The types of the top layer.
             */
            enum class TopLayerType
            {
                NordicStone
            };

            /*!
             * \brief Creates a new instance.
             * \param topLayerType
             *        The type of the top layer.
             * \param name
             *        The name of the location.
             * \param initialDamage
             *        The initial damage of the location.
             * \param slopeAngle
             *        The slope angle of the location.
             * \param thicknessTopLayer
             *        The thickness of the top layer of the location.
             * \param relativeDensity
             *        The relative density of the location.
             */
            explicit NaturalStoneRevetmentLocationConstructionProperties(
                TopLayerType topLayerType,
                std::string name,
                double initialDamage,
                double slopeAngle,
                double thicknessTopLayer,
                double relativeDensity);

            #pragma region Set methods

            /*!
             * \brief Sets the plunging coefficient A.
             */
            void SetPlungingCoefficientA(
                std::unique_ptr<double> plungingCoefficientA);

            /*!
             * \brief Sets the plunging coefficient B.
             */
            void SetPlungingCoefficientB(
                std::unique_ptr<double> plungingCoefficientB);

            /*!
             * \brief Sets the plunging coefficient C.
             */
            void SetPlungingCoefficientC(
                std::unique_ptr<double> plungingCoefficientC);

            /*!
             * \brief Sets the plunging coefficient N.
             */
            void SetPlungingCoefficientN(
                std::unique_ptr<double> plungingCoefficientN);

            /*!
             * \brief Sets the surging coefficient A.
             */
            void SetSurgingCoefficientA(
                std::unique_ptr<double> surgingCoefficientA);

            /*!
             * \brief Sets the surging coefficient B.
             */
            void SetSurgingCoefficientB(
                std::unique_ptr<double> surgingCoefficientB);

            /*!
             * \brief Sets the surging coefficient C.
             */
            void SetSurgingCoefficientC(
                std::unique_ptr<double> surgingCoefficientC);

            /*!
             * \brief Sets the surging coefficient N.
             */
            void SetSurgingCoefficientN(
                std::unique_ptr<double> surgingCoefficientN);

            /*!
             * \brief Sets the similarity parameter threshold.
             */
            void SetSimilarityParameterThreshold(
                std::unique_ptr<double> similarityParameterThreshold);

            /*!
             * \brief Sets the upper limit loading Aul.
             */
            void SetUpperLimitLoadingAul(
                std::unique_ptr<double> upperLimitLoadingAul);

            /*!
             * \brief Sets the upper limit loading Bul.
             */
            void SetUpperLimitLoadingBul(
                std::unique_ptr<double> upperLimitLoadingBul);

            /*!
             * \brief Sets the upper limit loading Cul.
             */
            void SetUpperLimitLoadingCul(
                std::unique_ptr<double> upperLimitLoadingCul);

            /*!
             * \brief Sets the lower limit loading All.
             */
            void SetLowerLimitLoadingAll(
                std::unique_ptr<double> lowerLimitLoadingAll);

            /*!
             * \brief Sets the lower limit loading Bll.
             */
            void SetLowerLimitLoadingBll(
                std::unique_ptr<double> lowerLimitLoadingBll);

            /*!
             * \brief Sets the lower limit loading Cll.
             */
            void SetLowerLimitLoadingCll(
                std::unique_ptr<double> lowerLimitLoadingCll);

            /*!
             * \brief Sets the distance maximum wave elevation Asmax.
             */
            void SetDistanceMaximumWaveElevationAsmax(
                std::unique_ptr<double> distanceMaximumWaveElevationAsmax);

            /*!
             * \brief Sets the distance maximum wave elevation Bsmax.
             */
            void SetDistanceMaximumWaveElevationBsmax(
                std::unique_ptr<double> distanceMaximumWaveElevationBsmax);

            /*!
             * \brief Sets the normative width of wave impact Awi.
             */
            void SetNormativeWidthOfWaveImpactAwi(
                std::unique_ptr<double> normativeWidthOfWaveImpactAwi);

            /*!
             * \brief Sets the normative width of wave impact Bwi.
             */
            void SetNormativeWidthOfWaveImpactBwi(
                std::unique_ptr<double> normativeWidthOfWaveImpactBwi);

            /*!
             * \brief Sets the wave angle impact beta max
             * \param waveAngleImpactBetamax
             *        The wave angle impact beta max.
             */
            void SetWaveAngleImpactBetamax(
                std::unique_ptr<double> waveAngleImpactBetamax);

            #pragma endregion

            #pragma region Get methods

            /*!
             * \brief Gets the type of the top layer.
             * \return The type of the top layer.
             */
            TopLayerType GetTopLayerType() const;

            /*!
             * \brief Gets the name of the location.
             * \return The name of the location.
             */
            std::string GetName() const;

            /*!
             * \brief Gets the initial damage of the location.
             * \return The initial damage of the location.
             */
            double GetInitialDamage() const;

            /*!
             * \brief Gets the slope angle of the location.
             * \return The slope angle of the location.
             */
            double GetSlopeAngle() const;

            /*!
             * \brief Gets the thickness of the top layer of the location.
             * \return The thickness of the top layer of the location.
             */
            double GetThicknessTopLayer() const;

            /*!
             * \brief Gets the relative density.
             * \return The relative density.
             */
            double GetRelativeDensity() const;

            /*!
             * \brief Gets the plunging coefficient A.
             * \return The plunging coefficient A.
             */
            const double* GetPlungingCoefficientA() const;

            /*!
             * \brief Gets the plunging coefficient B.
             * \return The plunging coefficient B.
             */
            const double* GetPlungingCoefficientB() const;

            /*!
             * \brief Gets the plunging coefficient C.
             * \return The plunging coefficient C.
             */
            const double* GetPlungingCoefficientC() const;

            /*!
             * \brief Gets the plunging coefficient N.
             * \return The plunging coefficient N.
             */
            const double* GetPlungingCoefficientN() const;

            /*!
             * \brief Gets the surging coefficient A.
             * \return The surging coefficient A.
             */
            const double* GetSurgingCoefficientA() const;

            /*!
             * \brief Gets the surging coefficient B.
             * \return The surging coefficient B.
             */
            const double* GetSurgingCoefficientB() const;

            /*!
             * \brief Gets the surging coefficient C.
             * \return The surging coefficient C.
             */
            const double* GetSurgingCoefficientC() const;

            /*!
             * \brief Gets the surging coefficient N.
             * \return The surging coefficient N.
             */
            const double* GetSurgingCoefficientN() const;

            /*!
             * \brief Gets the similarity parameter threshold.
             * \return The similarity parameter threshold.
             */
            const double* GetSimilarityParameterThreshold() const;

            /*!
             * \brief Gets the upper limit loading Aul.
             * \return The upper limit loading Aul.
             */
            const double* GetUpperLimitLoadingAul() const;

            /*!
             * \brief Gets the upper limit loading Bul.
             * \return The upper limit loading Bul.
             */
            const double* GetUpperLimitLoadingBul() const;

            /*!
             * \brief Gets the upper limit loading Cul.
             * \return The upper limit loading Cul.
             */
            const double* GetUpperLimitLoadingCul() const;

            /*!
             * \brief Gets the lower limit loading All.
             * \return The lower limit loading All.
             */
            const double* GetLowerLimitLoadingAll() const;

            /*!
             * \brief Gets the lower limit loading Bll.
             * \return The lower limit loading Bll.
             */
            const double* GetLowerLimitLoadingBll() const;

            /*!
             * \brief Gets the lower limit loading Cll.
             * \return The lower limit loading Cll.
             */
            const double* GetLowerLimitLoadingCll() const;

            /*!
             * \brief Gets the distance maximum wave elevation Asmax.
             * \return The distance maximum wave elevation Asmax.
             */
            const double* GetDistanceMaximumWaveElevationAsmax() const;

            /*!
             * \brief Gets the distance maximum wave elevation Bsmax.
             * \return The distance maximum wave elevation Bsmax.
             */
            const double* GetDistanceMaximumWaveElevationBsmax() const;

            /*!
             * \brief Gets the normative width of wave impact Awi.
             * \return The normative width of wave impact Awi.
             */
            const double* GetNormativeWidthOfWaveImpactAwi() const;

            /*!
             * \brief Gets the normative width of wave impact Bwi.
             * \return The normative width of wave impact Bwi.
             */
            const double* GetNormativeWidthOfWaveImpactBwi() const;

            /*!
             * \brief Gets the wave angle impact beta max
             * \return The wave angle impact beta max.
             */
            const double* GetWaveAngleImpactBetamax() const;

            #pragma endregion

        private:
            TopLayerType _topLayerType;
            std::string _name;
            double _initialDamage;
            double _slopeAngle;
            double _thicknessTopLayer;
            double _relativeDensity;
            std::unique_ptr<double> _plungingCoefficientA = nullptr;
            std::unique_ptr<double> _plungingCoefficientB = nullptr;
            std::unique_ptr<double> _plungingCoefficientC = nullptr;
            std::unique_ptr<double> _plungingCoefficientN = nullptr;
            std::unique_ptr<double> _surgingCoefficientA = nullptr;
            std::unique_ptr<double> _surgingCoefficientB = nullptr;
            std::unique_ptr<double> _surgingCoefficientC = nullptr;
            std::unique_ptr<double> _surgingCoefficientN = nullptr;
            std::unique_ptr<double> _similarityParameterThreshold = nullptr;
            std::unique_ptr<double> _upperLimitLoadingAul = nullptr;
            std::unique_ptr<double> _upperLimitLoadingBul = nullptr;
            std::unique_ptr<double> _upperLimitLoadingCul = nullptr;
            std::unique_ptr<double> _lowerLimitLoadingAll = nullptr;
            std::unique_ptr<double> _lowerLimitLoadingBll = nullptr;
            std::unique_ptr<double> _lowerLimitLoadingCll = nullptr;
            std::unique_ptr<double> _distanceMaximumWaveElevationAsmax = nullptr;
            std::unique_ptr<double> _distanceMaximumWaveElevationBsmax = nullptr;
            std::unique_ptr<double> _normativeWidthOfWaveImpactAwi = nullptr;
            std::unique_ptr<double> _normativeWidthOfWaveImpactBwi = nullptr;
            std::unique_ptr<double> _waveAngleImpactBetamax = nullptr;
    };
}
