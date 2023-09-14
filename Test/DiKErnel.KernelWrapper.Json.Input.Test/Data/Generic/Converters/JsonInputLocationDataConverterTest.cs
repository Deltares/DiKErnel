using System;
using DiKErnel.KernelWrapper.Json.Input.Data.Generic.Converters;
using NUnit.Framework;

namespace DiKErnel.KernelWrapper.Json.Input.Test.Data.Generic.Converters
{
    [TestFixture]
    public class JsonInputLocationDataConverterTest
    {
        [Test]
        public void CanWrite_Always_ReturnsFalse()
        {
            // Setup
            var converter = new JsonInputLocationDataConverter();

            // Call
            bool canWrite = converter.CanWrite;

            // Assert
            Assert.IsFalse(canWrite);
        }

        [Test]
        public void WriteJson_Always_ThrowsNotSupportedException()
        {
            // Setup
            var converter = new JsonInputLocationDataConverter();

            // Call
            void Call() => converter.WriteJson(null, null, null);

            // Assert
            Assert.Throws<NotSupportedException>(Call);
        }
    }
}