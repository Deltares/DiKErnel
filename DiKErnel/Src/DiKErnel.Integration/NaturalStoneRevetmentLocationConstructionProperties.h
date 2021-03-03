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
             * \brief The relative density of the location.
             */
            std::unique_ptr<double> _relativeDensityPtr;

            /*!
             * \brief The plunging coefficient A of the location.
             */
            std::unique_ptr<double> _plungingCoefficientAPtr;

            /*!
             * \brief The plunging coefficient B of the location.
             */
            std::unique_ptr<double> _plungingCoefficientBPtr;

            /*!
             * \brief The plunging coefficient C of the location.
             */
            std::unique_ptr<double> _plungingCoefficientCPtr;

            /*!
             * \brief The plunging coefficient N of the location.
             */
            std::unique_ptr<double> _plungingCoefficientNPtr;

            /*!
             * \brief The surging coefficient A of the location.
             */
            std::unique_ptr<double> _surgingCoefficientAPtr;

            /*!
             * \brief The surging coefficient B of the location.
             */
            std::unique_ptr<double> _surgingCoefficientBPtr;

            /*!
             * \brief The surging coefficient C of the location.
             */
            std::unique_ptr<double> _surgingCoefficientCPtr;

            /*!
             * \brief The surging coefficient N of the location.
             */
            std::unique_ptr<double> _surgingCoefficientNPtr;

            /*!
             * \brief The similarity parameter threshold of the location.
             */
            std::unique_ptr<double> _similarityParameterThresholdPtr;

        private:
            double _initialDamage;
            double _slopeAngle;
            double _thicknessTopLayer;
    };
}
