using System.Collections.Generic;
using TechTalk.SpecFlow;
using TechTalk.SpecFlow.Assist;

namespace SpecFlow.SystemTest.Support
{
    [Binding]
    public class StepArgumentTransformer
    {

            [StepArgumentTransformation]

        public IEnumerable<(double, double)> TestTransform(Table table)
        {
             return  table.CreateSet<(double, double)>();
        }

    }
}
