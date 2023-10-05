using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.Util;

namespace DiKErnel.KernelWrapper.Json.Input
{
    /// <summary>
    /// Container for a calculation input data result and the meta-data that goes with it.
    /// </summary>
    public class ComposedInputData
    {
        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="calculationInputDataResult">The calculation input data result.</param>
        /// <param name="locationIds">The ids of the locations in the calculation input data result.</param>
        internal ComposedInputData(DataResult<ICalculationInput> calculationInputDataResult, IReadOnlyList<int?> locationIds)
        {
            CalculationInputDataResult = calculationInputDataResult;
            LocationIds = locationIds;
        }

        /// <summary>
        /// Gets the calculation input data result.
        /// </summary>
        public DataResult<ICalculationInput> CalculationInputDataResult { get; }

        /// <summary>
        /// Gets the ids of the locations in the calculation input data result.
        /// </summary>
        public IReadOnlyList<int?> LocationIds { get; }
    }
}