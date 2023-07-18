using System.Runtime.Serialization;
using DiKErnel.KernelWrapper.Json.Input.Data.Generic.Definitions;

namespace DiKErnel.KernelWrapper.Json.Input.Data.Generic
{
    // [JsonConverter(typeof(JsonStringEnumConverter))]
    internal enum JsonInputCalculationType
    {
        [EnumMember(Value = "onbekend")]
        Unknown,
        
        [EnumMember(Value = JsonInputDefinitions.CALCULATION_METHOD_TYPE_ASPHALT_WAVE_IMPACT)]
        AsphaltWaveImpact,
        
        [EnumMember(Value = JsonInputDefinitions.CALCULATION_METHOD_TYPE_GRASS_OVERTOPPING)]
        GrassOvertopping,
        
        [EnumMember(Value = JsonInputDefinitions.CALCULATION_METHOD_TYPE_GRASS_WAVE_IMPACT)]
        GrassWaveImpact,
        
        [EnumMember(Value = JsonInputDefinitions.CALCULATION_METHOD_TYPE_GRASS_WAVE_RUNUP)]
        GrassWaveRunup,
        
        [EnumMember(Value = JsonInputDefinitions.CALCULATION_METHOD_TYPE_NATURAL_STONE)]
        NaturalStone
    }
    //todo find out what the nlohmann json serialize enum does
}