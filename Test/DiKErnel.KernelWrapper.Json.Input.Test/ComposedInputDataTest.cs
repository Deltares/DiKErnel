using System;
using DiKErnel.Core.Data;
using DiKErnel.Util;
using NUnit.Framework;

namespace DiKErnel.KernelWrapper.Json.Input.Test
{
    [TestFixture]
    public class ComposedInputDataTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            var calculationInputDataResult = new DataResult<ICalculationInput>(Array.Empty<Event>());
            int?[] locationIds = Array.Empty<int?>();

            // Call
            var composedInputData = new ComposedInputData(calculationInputDataResult, locationIds);

            // Assert
            Assert.AreSame(calculationInputDataResult, composedInputData.CalculationInputDataResult);
            Assert.AreSame(locationIds, composedInputData.LocationIds);
        }
    }
}