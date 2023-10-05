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
            var calculationInput = new DataResult<ICalculationInput>(Array.Empty<Event>());
            int[] locationIds = Array.Empty<int>();

            // Call
            var composedInputData = new ComposedInputData(calculationInput, locationIds);

            // Assert
            Assert.AreSame(calculationInput, composedInputData.CalculationInput);
            Assert.AreSame(locationIds, composedInputData.LocationIds);
        }
    }
}