// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using DiKErnel.Util.Validation;

namespace DiKErnel.DomainLibrary.Validators.AsphaltWaveImpact
{
    /// <summary>
    /// Class that holds asphalt wave impact validation routines.
    /// </summary>
    public static class AsphaltWaveImpactValidator
    {
        /// <summary>
        /// Validates the fatigue alpha coefficient.
        /// </summary>
        /// <param name="fatigueAlpha">The fatigue alpha coefficient [-].</param>
        /// <returns>A validation issue when the fatigue alpha coefficient is not valid;
        /// <c>null</c> otherwise.</returns>
        public static ValidationIssue FatigueAlpha(double fatigueAlpha)
        {
            return ValidateLargerThanZero(fatigueAlpha, "FatigueAlpha");
        }

        /// <summary>
        /// Validates the fatigue beta coefficient.
        /// </summary>
        /// <param name="fatigueBeta">The fatigue beta coefficient [-].</param>
        /// <returns>A validation issue when the fatigue beta coefficient is not valid;
        /// <c>null</c> otherwise.</returns>
        public static ValidationIssue FatigueBeta(double fatigueBeta)
        {
            return ValidateLargerThanZero(fatigueBeta, "FatigueBeta");
        }

        /// <summary>
        /// Validates the flexural strength.
        /// </summary>
        /// <param name="flexuralStrength">The flexural strength [MPa].</param>
        /// <returns>A validation issue when the flexural strength is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue FlexuralStrength(double flexuralStrength)
        {
            return ValidateLargerThanZero(flexuralStrength, "FlexuralStrength");
        }

        /// <summary>
        /// Validates the impact number C coefficient.
        /// </summary>
        /// <param name="impactNumberC">The impact number C coefficient [-].</param>
        /// <returns>A validation issue when the impact number C coefficient is not valid;
        /// <c>null</c> otherwise.</returns>
        public static ValidationIssue ImpactNumberC(double impactNumberC)
        {
            return ValidateLargerThanZero(impactNumberC, "ImpactNumberC");
        }

        /// <summary>
        /// Validates the density of water.
        /// </summary>
        /// <param name="densityOfWater">The density of water [kg/m^3].</param>
        /// <returns>A validation issue when the density of water is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue DensityOfWater(double densityOfWater)
        {
            if (densityOfWater < 950d || densityOfWater > 1050d)
            {
                return new ValidationIssue(ValidationIssueType.Error, "DensityOfWater must be in range [950, 1050].");
            }

            return null;
        }

        /// <summary>
        /// Validates the soil elasticity.
        /// </summary>
        /// <param name="soilElasticity">The soil elasticity [MPa/m].</param>
        /// <returns>A validation issue when the soil elasticity is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue SoilElasticity(double soilElasticity)
        {
            return ValidateLargerThanZero(soilElasticity, "SoilElasticity");
        }

        /// <summary>
        /// Validates the Nu coefficient.
        /// </summary>
        /// <param name="stiffnessRelationNu">The Nu coefficient [m^-1].</param>
        /// <returns>A validation issue when the Nu coefficient is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue StiffnessRelationNu(double stiffnessRelationNu)
        {
            return ValidateLargerThanZero(stiffnessRelationNu, "StiffnessRelationNu");
        }

        /// <summary>
        /// Validates the thickness.
        /// </summary>
        /// <param name="thickness">The thickness [m].</param>
        /// <returns>A validation issue when the thickness is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue Thickness(double thickness)
        {
            return ValidateLargerThanZero(thickness, "Thickness");
        }

        /// <summary>
        /// Validates the elastic modulus.
        /// </summary>
        /// <param name="elasticModulus">The elastic modulus [MPa].</param>
        /// <returns>A validation issue when the elastic modulus is not valid; <c>null</c>
        /// otherwise.</returns>
        public static ValidationIssue ElasticModulus(double elasticModulus)
        {
            return ValidateLargerThanZero(elasticModulus, "ElasticModulus");
        }

        private static ValidationIssue ValidateLargerThanZero(double propertyToValidate, string propertyName)
        {
            if (propertyToValidate <= 0d)
            {
                return new ValidationIssue(ValidationIssueType.Error, propertyName + " must be larger than 0.");
            }

            return null;
        }
    }
}