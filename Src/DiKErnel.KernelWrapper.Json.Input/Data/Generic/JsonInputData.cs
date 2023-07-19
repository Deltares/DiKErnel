using System.Collections.Generic;
using DiKErnel.KernelWrapper.Json.Input.Data.Generic.Definitions;
using Newtonsoft.Json;

namespace DiKErnel.KernelWrapper.Json.Input.Data.Generic
{
    internal class JsonInputData
    {
        [JsonProperty(JsonInputDefinitions.TIME)]
        public IEnumerable<int> Times { get; private set; }

        [JsonProperty(JsonInputDefinitions.HYDRAULIC_LOADS)]
        public JsonInputHydraulicData HydraulicData { get; private set; }

        [JsonProperty(JsonInputDefinitions.DIKE_PROFILE)]
        public JsonInputDikeProfileData DikeProfileData { get; private set; }

        [JsonProperty(JsonInputDefinitions.LOCATIONS)]
        public IEnumerable<JsonInputLocationData> LocationData { get; private set; }

        [JsonProperty(JsonInputDefinitions.CALCULATION_METHODS)]
        public IEnumerable<JsonInputCalculationData> CalculationDefinitionData { get; private set; }
    }
}