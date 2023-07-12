using System.Collections.Generic;
using System.Threading;

namespace DiKErnel.Util.TestUtil
{
    public class EventRegistryTestHelper
    {
        private readonly Thread thread;
        private readonly List<Event> registeredEvents;

        public EventRegistryTestHelper(int numberOfEventsToRegister)
        {
            registeredEvents = new List<Event>();
            thread = new Thread(() => PerformTest(numberOfEventsToRegister));
            thread.Start();
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