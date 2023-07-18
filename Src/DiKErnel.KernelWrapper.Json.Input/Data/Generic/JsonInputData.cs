using System.Collections.Generic;
using DiKErnel.KernelWrapper.Json.Input.Data.Generic.Definitions;
using Newtonsoft.Json;

namespace DiKErnel.KernelWrapper.Json.Input.Data.Generic
{
    public class JsonInputData
    {
        public JsonInputData(IEnumerable<int> times,
                             JsonInputHydraulicData hydraulicData,
                             JsonInputDikeProfileData dikeProfileData,
                             IEnumerable<JsonInputLocationData> locationData,
                             IEnumerable<JsonInputCalculationDefinitionData> calculationDefinitionData)
        {
            Times = times;
            HydraulicData = hydraulicData;
            DikeProfileData = dikeProfileData;
            LocationData = locationData;
            CalculationDefinitionData = calculationDefinitionData;
        }

        [JsonProperty(JsonInputDefinitions.TIME)]
        public IEnumerable<int> Times { get; }

        [JsonProperty(JsonInputDefinitions.HYDRAULIC_LOADS)]
        public JsonInputHydraulicData HydraulicData { get; }
        
        [JsonProperty(JsonInputDefinitions.DIKE_PROFILE)]
        public JsonInputDikeProfileData DikeProfileData { get; }
        
        [JsonProperty(JsonInputDefinitions.LOCATIONS)]
        public IEnumerable<JsonInputLocationData> LocationData { get; }

        [JsonProperty(JsonInputDefinitions.CALCULATION_METHODS)]
        public IEnumerable<JsonInputCalculationDefinitionData> CalculationDefinitionData { get; }
    }
}