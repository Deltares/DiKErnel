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

namespace DiKErnel::Integration
{
    /*!
     * \brief Construction properties to construct a natural stone revetment location.
     */
    class NaturalStoneRevetmentLocationConstructionProperties
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param initialDamage
             *        The initial damage of the location.
             * \param slopeAngle
             *        The slope angle of the location.
             * \param thicknessTopLayer
             *        The thickness of the top layer of the location.
             */
            explicit NaturalStoneRevetmentLocationConstructionProperties(
                double initialDamage,
                double slopeAngle,
                double thicknessTopLayer);

            /*!
             * \brief Sets the relative density.
             */
            void SetRelativeDensity(
                std::unique_ptr<double> relativeDensity);

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
            const double* GetRelativeDensity() const;

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

        private:
            double _initialDamage;
            double _slopeAngle;
            double _thicknessTopLayer;

            std::unique_ptr<double> _relativeDensity = nullptr;
            std::unique_ptr<double> _plungingCoefficientA = nullptr;
            std::unique_ptr<double> _plungingCoefficientB = nullptr;
            std::unique_ptr<double> _plungingCoefficientC = nullptr;
            std::unique_ptr<double> _plungingCoefficientN = nullptr;
            std::unique_ptr<double> _surgingCoefficientA = nullptr;
            std::unique_ptr<double> _surgingCoefficientB = nullptr;
            std::unique_ptr<double> _surgingCoefficientC = nullptr;
            std::unique_ptr<double> _surgingCoefficientN = nullptr;
            std::unique_ptr<double> _similarityParameterThreshold = nullptr;
    };
}
