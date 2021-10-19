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

#include <vector>

#include "AsphaltRevetmentTopLayerType.h"
#include "RevetmentLocationConstructionPropertiesBase.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Construction properties to construct asphalt revetment wave impact location dependent
     *        input.
     */
    class AsphaltRevetmentWaveImpactLocationConstructionProperties : public RevetmentLocationConstructionPropertiesBase
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param x
             *        The x coordinate.
             * \param outerSlope
             *        The outer slope.
             * \param topLayerType
             *        The type of the top layer.
             * \param failureTension
             *        The failure tension.
             * \param densityOfWater
             *        The density of water.
             * \param soilElasticity
             *        The elasticity of the soil.
             * \param thicknessUpperLayer
             *        The thickness of the upper layer.
             * \param elasticModulusUpperLayer
             *        The elastic modulus of the upper layer.
             */
            explicit AsphaltRevetmentWaveImpactLocationConstructionProperties(
                double x,
                double outerSlope,
                AsphaltRevetmentTopLayerType topLayerType,
                double failureTension,
                double densityOfWater,
                double soilElasticity,
                double thicknessUpperLayer,
                double elasticModulusUpperLayer);

            #pragma region Set methods

            /*!
             * \brief Sets the thickness of the sub layer.
             * \param thicknessSubLayer
             *        The thickness of the sub layer.
             */
            void SetThicknessSubLayer(
                std::unique_ptr<double> thicknessSubLayer);

            /*!
             * \brief Sets the elastic modulus of the sub layer.
             * \param elasticModulusSubLayer
             *        The elastic modulus of the sub layer.
             */
            void SetElasticModulusSubLayer(
                std::unique_ptr<double> elasticModulusSubLayer);

            /*!
             * \brief Sets the Ctm coefficient.
             * \param averageNumberOfWavesCtm
             *        The Ctm coefficient.
             */
            void SetAverageNumberOfWavesCtm(
                std::unique_ptr<double> averageNumberOfWavesCtm);

            /*!
             * \brief Sets the fatigue alpha coefficient.
             * \param fatigueAlpha
             *        The fatigue alpha coefficient.
             */
            void SetFatigueAlpha(
                std::unique_ptr<double> fatigueAlpha);

            /*!
             * \brief Sets the fatigue beta coefficient.
             * \param fatigueBeta
             *        The fatigue beta coefficient.
             */
            void SetFatigueBeta(
                std::unique_ptr<double> fatigueBeta);

            /*!
             * \brief Sets the impact number C coefficient.
             * \param impactNumberC
             *        The impact number C coefficient.
             */
            void SetImpactNumberC(
                std::unique_ptr<double> impactNumberC);

            /*!
             * \brief Sets the Nu coefficient.
             * \param stiffnessRelationNu
             *        The Nu coefficient.
             */
            void SetStiffnessRelationNu(
                std::unique_ptr<double> stiffnessRelationNu);

            /*!
             * \brief Sets the width factors.
             * \param widthFactors
             *        The width factors.
             */
            void SetWidthFactors(
                std::unique_ptr<std::vector<std::tuple<double, double>>> widthFactors);

            /*!
             * \brief Sets the depth factors.
             * \param depthFactors
             *        The depth factors.
             */
            void SetDepthFactors(
                std::unique_ptr<std::vector<std::tuple<double, double>>> depthFactors);

            /*!
             * \brief Sets the impact factors.
             * \param impactFactors
             *        The impact factors.
             */
            void SetImpactFactors(
                std::unique_ptr<std::vector<std::tuple<double, double>>> impactFactors);

            #pragma endregion

            #pragma region Get methods

            /*!
             * \brief Gets the outer slope.
             * \return The outer slope.
             */
            double GetOuterSlope() const;

            /*!
             * \brief Gets the type of the top layer.
             * \return The type of the top layer.
             */
            AsphaltRevetmentTopLayerType GetTopLayerType() const;

            /*!
             * \brief Gets the failure tension.
             * \return The failure tension.
             */
            double GetFailureTension() const;

            /*!
             * \brief Gets the density of water.
             * \return The density of water.
             */
            double GetDensityOfWater() const;

            /*!
             * \brief Gets the soil elasticity.
             * \return The soil elasticity.
             */
            double GetSoilElasticity() const;

            /*!
             * \brief Gets the thickness of the upper layer.
             * \return The thickness of the upper layer.
             */
            double GetThicknessUpperLayer() const;

            /*!
             * \brief Gets the elastic modulus of the upper layer.
             * \return The elastic modulus of the upper layer.
             */
            double GetElasticModulusUpperLayer() const;

            /*!
             * \brief Gets the thickness of the sub layer.
             * \return The thickness of the sub layer.
             */
            const double* GetThicknessSubLayer() const;

            /*!
             * \brief Gets the elastic modulus of the sub layer.
             * \return The elastic modulus of the sub layer.
             */
            const double* GetElasticModulusSubLayer() const;

            /*!
             * \brief Gets the Ctm coefficient.
             * \return The Ctm coefficient.
             */
            const double* GetAverageNumberOfWavesCtm() const;

            /*!
             * \brief Gets the fatigue alpha coefficient.
             * \return The fatigue alpha coefficient.
             */
            const double* GetFatigueAlpha() const;

            /*!
             * \brief Gets the fatigue beta coefficient.
             * \return The fatigue beta coefficient.
             */
            const double* GetFatigueBeta() const;

            /*!
             * \brief Gets the impact number C coefficient.
             * \return The impact number C coefficient.
             */
            const double* GetImpactNumberC() const;

            /*!
             * \brief Gets the Nu coefficient.
             * \return The Nu coefficient.
             */
            const double* GetStiffnessRelationNu() const;

            /*!
             * \brief Gets the width factors.
             * \return The width factors.
             */
            const std::vector<std::tuple<double, double>>* GetWidthFactors() const;

            /*!
             * \brief Gets the depth factors.
             * \return The depth factors.
             */
            const std::vector<std::tuple<double, double>>* GetDepthFactors() const;

            /*!
             * \brief Gets the impact factors.
             * \return The impact factors.
             */
            const std::vector<std::tuple<double, double>>* GetImpactFactors() const;

            #pragma endregion

        private:
            double _outerSlope;
            AsphaltRevetmentTopLayerType _topLayerType;
            double _failureTension;
            double _densityOfWater;
            double _soilElasticity;
            double _thicknessUpperLayer;
            double _elasticModulusUpperLayer;
            std::unique_ptr<double> _thicknessSubLayer = nullptr;
            std::unique_ptr<double> _elasticModulusSubLayer = nullptr;
            std::unique_ptr<double> _averageNumberOfWavesCtm = nullptr;
            std::unique_ptr<double> _fatigueAlpha = nullptr;
            std::unique_ptr<double> _fatigueBeta = nullptr;
            std::unique_ptr<double> _impactNumberC = nullptr;
            std::unique_ptr<double> _stiffnessRelationNu = nullptr;
            std::unique_ptr<std::vector<std::tuple<double, double>>> _widthFactors = nullptr;
            std::unique_ptr<std::vector<std::tuple<double, double>>> _depthFactors = nullptr;
            std::unique_ptr<std::vector<std::tuple<double, double>>> _impactFactors = nullptr;
    };
}
