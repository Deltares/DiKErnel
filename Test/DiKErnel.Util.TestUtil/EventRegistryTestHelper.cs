using System.Collections.Generic;
using System.Threading;

namespace DiKErnel.Util.TestUtil
{
    public class EventRegistryTestHelper
    {
        private List<Event> registeredEvents;
        private readonly Thread thread;

        public EventRegistryTestHelper(int numberOfEventsToRegister)
        {
            thread = new Thread(() => PerformTest(numberOfEventsToRegister));
        }

        public void WaitForCompletion()
        {
            bool joinable = Thread.CurrentThread != thread;
            if (joinable)
            {
                thread.Join();
            }
        }

        public IEnumerable<Event> GetRegisteredEvents()
        {
            return registeredEvents;
        }

        private void PerformTest(int numberOfEventsToRegister)
        {
            for (int i = 0; i < numberOfEventsToRegister; ++i)
            {
                EventRegistry.Register(new Event($"Event {i}", EventType.Error));
            }

            foreach (Event registeredEvent in EventRegistry.Flush())
            {
                registeredEvents.Add(registeredEvent);
            }
        }
    }
}