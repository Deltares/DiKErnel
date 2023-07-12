using DiKErnel.Util.Validation;
using NUnit.Framework;

namespace DiKErnel.Util.TestUtil
{
    public class ValidatorAssertHelper<T>
    {
        private delegate ValidationIssue ValidateAction(T data);

        static void AssertValue(ValidateAction validateAction, T value)
        {
            // Call
            ValidationIssue validationIssue = validateAction(value);

            // Assert
            Assert.IsNull(validationIssue);
        }

        static void AssertValue(ValidateAction validateAction,
                                T value,
                                ValidationIssueType validationIssueType,
                                string message)
        {
            // Call
            ValidationIssue validationIssue = validateAction(value);

            // Assert
            Assert.NotNull(validationIssue);
            Assert.AreEqual(validationIssueType, validationIssue.GetValidationIssueType());
            Assert.AreEqual(message, validationIssue.GetMessage());
        }
    }
}