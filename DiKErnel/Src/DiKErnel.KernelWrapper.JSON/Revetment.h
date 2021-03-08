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

#include <string>

#include "CalculationMethod.h"

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * \brief Container for revetment data.
     */
    class Revetment
    {
        public:
            /*! 
             * \brief Creates a new instance.
             * \param typeTopLayer
             *        The type of top layer.
             * \param relativeDensity
             *        The relative density.
             * \param thicknessTopLayer
             *        The thickness of the top layer.
             * \param calculationMethod
             *        The calculation method.
             */
            explicit Revetment(
                std::string typeTopLayer,
                double relativeDensity,
                double thicknessTopLayer,
                std::unique_ptr<CalculationMethod> calculationMethod
            );

            /*!
             * \brief Gets the type of top layer.
             * \return The type of top layer.
             */
            const std::string& GetTypeTopLayer() const;

            /*!
             * \brief Gets the relative density.
             * \return The relative density.
             */
            double GetRelativeDensity() const;

            /*!
             * \brief Gets the thickness of the top layer.
             * \return The thickness of the top layer.
             */
            double GetThicknessTopLayer() const;

            /*!
             * \brief Gets the calculation method.
             * \return The calculation method.
             */
            const CalculationMethod& GetCalculationMethod() const;

        private:
            std::string _typeTopLayer;
            double _relativeDensity;
            double _thicknessTopLayer;
            std::unique_ptr<CalculationMethod> _calculationMethod;
    };
}
