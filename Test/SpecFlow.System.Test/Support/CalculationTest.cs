using System.Linq;
using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Core.Extensions;
using DiKErnel.Util;
using NUnit.Framework;

namespace SpecFlow.SystemTest.Support
{
    public abstract class CalculationTest
    {
        public static void AssertOutput(Calculator calculator, double expectedDamage,
                                           int? expectedTimeOfFailure = null)
        {
            Assert.AreEqual(CalculationState.FinishedSuccessfully, calculator.CalculationState);

            DataResult<CalculationOutput> calculatorResult = calculator.Result;
            Assert.IsTrue(calculatorResult.Successful);
            CollectionAssert.IsEmpty(calculatorResult.Events);

            Assert.AreEqual(expectedDamage,
                            calculatorResult.Data.LocationDependentOutputItems[0].GetDamages().Last(),
                            1e-14);

            Assert.AreEqual(expectedTimeOfFailure,
                            calculatorResult.Data.LocationDependentOutputItems[0].GetTimeOfFailure());
        }
    }
}