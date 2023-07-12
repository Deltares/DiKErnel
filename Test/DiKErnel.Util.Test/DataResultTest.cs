using System.Collections.Generic;
using System.Linq;
using DiKErnel.Util.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Util.Test
{
    [TestFixture]
    public class DataResultTest
    {
        [Test]
        public void Constructor_WithData_ExpectedValues()
        {
            // Setup
            var data = 45;
            var message = "Test message";
            var eventType = EventType.Error;
            
            var events = new List<Event>();
            events.Add(new Event(message, eventType));
            
            // Call
            DataResult<int> result = new DataResult<int>(data, events);
            
            // Assert
            Assert.True(result.GetSuccessful());
            
            Assert.AreEqual(1, result.GetEvents().Count());
            EventAssertHelper.AssertEvent(eventType, message, result.GetEvents().ElementAt(0));
            
            Assert.AreEqual(data, result.GetData());
        }
    }
}