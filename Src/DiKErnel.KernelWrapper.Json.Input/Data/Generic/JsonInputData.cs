using System.Collections.Generic;

namespace DiKErnel.KernelWrapper.Json.Input.Data.Generic
{
    internal class JsonInputData
    {
        public JsonInputData(JsonInputHydraulicData hydraulicData,
                             JsonInputDikeProfileData dikeProfileData,
                             IEnumerable<JsonInputLocationData> locationData,
                             IEnumerable<(JsonInputCalculationType, JsonInputCalculationDefinitionData)> calculationDefinitionData)
        {
            HydraulicData = hydraulicData;
            DikeProfileData = dikeProfileData;
            LocationData = locationData;
            CalculationDefinitionData = calculationDefinitionData;
        }

        public JsonInputHydraulicData HydraulicData { get; }
        public JsonInputDikeProfileData DikeProfileData { get; }
        public IEnumerable<JsonInputLocationData> LocationData { get; }
        public IEnumerable<(JsonInputCalculationType, JsonInputCalculationDefinitionData)> CalculationDefinitionData { get; }
    }
}