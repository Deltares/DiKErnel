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
             * \param initialDamage
             *        The initial damage.
             * \param similarityParameterThreshold
             *        The similarity parameter threshold.
             * \param coefficientPlungingAp
             *        The A coefficient for plunging.
             * \param coefficientPlungingBp
             *        The B coefficient for plunging.
             * \param coefficientPlungingCp
             *        The C coefficient for plunging.
             * \param coefficientPlungingNp
             *        The N coefficient for plunging.
             * \param coefficientSurgingAs
             *        The A coefficient for surging.
             * \param coefficientSurgingBs
             *        The B coefficient for surging.
             * \param coefficientSurgingCs
             *        The C coefficient for surging.
             * \param coefficientSurgingNs
             *        The N coefficient for surging.
             */
            explicit Revetment(
                std::string typeTopLayer,
                double relativeDensity,
                double thicknessTopLayer,
                double initialDamage,
                double similarityParameterThreshold,
                double coefficientPlungingAp,
                double coefficientPlungingBp,
                double coefficientPlungingCp,
                double coefficientPlungingNp,
                double coefficientSurgingAs,
                double coefficientSurgingBs,
                double coefficientSurgingCs,
                double coefficientSurgingNs
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
             * \brief Gets the initial damage.
             * \return The initial damage.
             */
            double GetInitialDamage() const;

            /*!
             * \brief Gets the similarity parameter threshold.
             * \return The similarity parameter threshold.
             */
            double GetSimilarityParameterThreshold() const;

            /*!
             * \brief Gets the A coefficient for plunging.
             * \return The A coefficient for plunging.
             */
            double GetCoefficientPlungingAp() const;

            /*!
             * \brief Gets the B coefficient for plunging.
             * \return The B coefficient for plunging.
             */
            double GetCoefficientPlungingBp() const;

            /*!
             * \brief Gets the C coefficient for plunging.
             * \return The C coefficient for plunging.
             */
            double GetCoefficientPlungingCp() const;

            /*!
             * \brief Gets the N coefficient for plunging.
             * \return The N coefficient for plunging.
             */
            double GetCoefficientPlungingNp() const;

            /*!
             * \brief Gets the A coefficient for surging.
             * \return The A coefficient for surging.
             */
            double GetCoefficientSurgingAs() const;

            /*!
             * \brief Gets the B coefficient for surging.
             * \return The B coefficient for surging.
             */
            double GetCoefficientSurgingBs() const;

            /*!
             * \brief Gets the C coefficient for surging.
             * \return The C coefficient for surging.
             */
            double GetCoefficientSurgingCs() const;

            /*!
             * \brief Gets the D coefficient for surging.
             * \return The D coefficient for surging.
             */
            double GetCoefficientSurgingNs() const;

        private:
            std::string name;
            double relativeDensity;
            double thicknessTopLayer;
            double initialDamage;
            double similarityParameterThreshold;
            double coefficientPlungingAp;
            double coefficientPlungingBp;
            double coefficientPlungingCp;
            double coefficientPlungingNp;
            double coefficientSurgingAs;
            double coefficientSurgingBs;
            double coefficientSurgingCs;
            double coefficientSurgingNs;
    };
}
