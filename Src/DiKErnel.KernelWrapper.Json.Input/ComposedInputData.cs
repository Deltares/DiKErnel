using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.Util;

namespace DiKErnel.KernelWrapper.Json.Input
{
    /// <summary>
    /// Container for composed calculation input and the meta-data that goes with it.
    /// </summary>
    public class ComposedInputData
    {
        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="calculationInput">The composed calculation input.</param>
        /// <param name="locationIds">The ids of the locations in the composed calculation input.</param>
        internal ComposedInputData(DataResult<ICalculationInput> calculationInput, IReadOnlyList<int?> locationIds)
        {
            CalculationInput = calculationInput;
            LocationIds = locationIds;
        }

        /// <summary>
        /// Gets the composed calculation input.
        /// </summary>
        public DataResult<ICalculationInput> CalculationInput { get; }

        /// <summary>
        /// Gets the ids of the locations in the composed calculation input.
        /// </summary>
        public IReadOnlyList<int?> LocationIds { get; }
    }
}