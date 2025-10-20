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

namespace DiKErnel.External.Overtopping.Data
{
    /// <summary>
    /// The model factors for the overtopping kernel.
    /// </summary>
    internal struct ModelFactors
    {
        /// <summary>
        /// Model factor for non-breaking waves [-].
        /// </summary>
        public double FactorDeterminationQnFn;

        /// <summary>
        /// Model factor for breaking waves [-].
        /// </summary>
        public double FactorDeterminationQbFb;

        /// <summary>
        /// Model factor describing the uncertainty of 2% run-up height [-].
        /// </summary>
        public double Mz2;

        /// <summary>
        /// Model factor for shallow waves [-].
        /// </summary>
        public double FShallow;

        /// <summary>
        /// Model factor computed overtopping [-].
        /// </summary>
        public double ComputedOvertopping;

        /// <summary>
        /// Model factor critical overtopping [-].
        /// </summary>
        public double CriticalOvertopping;

        /// <summary>
        /// Relaxation factor iteration procedure wave run-up [-].
        /// </summary>
        public double RelaxationFactor;

        /// <summary>
        /// Reduction factor foreshore [-].
        /// </summary>
        public double ReductionFactorForeshore;
    }
}