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
             * \param similarityParameterThreshold
             *        The similarity parameter threshold.
             * \param plungingCoefficientA
             *        The A coefficient for plunging.
             * \param plungingCoefficientB
             *        The B coefficient for plunging.
             * \param plungingCoefficientC
             *        The C coefficient for plunging.
             * \param plungingCoefficientN
             *        The N coefficient for plunging.
             * \param surgingCoefficientA
             *        The A coefficient for surging.
             * \param surgingCoefficientB
             *        The B coefficient for surging.
             * \param surgingCoefficientC
             *        The C coefficient for surging.
             * \param surgingCoefficientN
             *        The N coefficient for surging.
             */
            explicit Revetment(
                std::string typeTopLayer,
                double relativeDensity,
                double thicknessTopLayer,
                double similarityParameterThreshold,
                double plungingCoefficientA,
                double plungingCoefficientB,
                double plungingCoefficientC,
                double plungingCoefficientN,
                double surgingCoefficientA,
                double surgingCoefficientB,
                double surgingCoefficientC,
                double surgingCoefficientN
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
             * \brief Gets the similarity parameter threshold.
             * \return The similarity parameter threshold.
             */
            double GetSimilarityParameterThreshold() const;

            /*!
             * \brief Gets the A coefficient for plunging.
             * \return The A coefficient for plunging.
             */
            double GetPlungingCoefficientA() const;

            /*!
             * \brief Gets the B coefficient for plunging.
             * \return The B coefficient for plunging.
             */
            double GetPlungingCoefficientB() const;

            /*!
             * \brief Gets the C coefficient for plunging.
             * \return The C coefficient for plunging.
             */
            double GetPlungingCoefficientC() const;

            /*!
             * \brief Gets the N coefficient for plunging.
             * \return The N coefficient for plunging.
             */
            double GetPlungingCoefficientN() const;

            /*!
             * \brief Gets the A coefficient for surging.
             * \return The A coefficient for surging.
             */
            double GetSurgingCoefficientA() const;

            /*!
             * \brief Gets the B coefficient for surging.
             * \return The B coefficient for surging.
             */
            double GetSurgingCoefficientB() const;

            /*!
             * \brief Gets the C coefficient for surging.
             * \return The C coefficient for surging.
             */
            double GetSurgingCoefficientC() const;

            /*!
             * \brief Gets the D coefficient for surging.
             * \return The D coefficient for surging.
             */
            double GetSurgingCoefficientN() const;

        private:
            std::string _typeTopLayer;
            double _relativeDensity;
            double _thicknessTopLayer;
            double _similarityParameterThreshold;
            double _plungingCoefficientA;
            double _plungingCoefficientB;
            double _plungingCoefficientC;
            double _plungingCoefficientN;
            double _surgingCoefficientA;
            double _surgingCoefficientB;
            double _surgingCoefficientC;
            double _surgingCoefficientN;
    };
}
