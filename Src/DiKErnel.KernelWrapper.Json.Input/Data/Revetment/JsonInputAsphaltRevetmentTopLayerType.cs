using System.Runtime.Serialization;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.Definitions;

namespace DiKErnel.KernelWrapper.Json.Input.Data.Revetment
{
    internal enum JsonInputAsphaltRevetmentTopLayerType
    {
        [EnumMember(Value = JsonInputAsphaltWaveImpactDefinitions.TOP_LAYER_TYPE_HYDRAULIC_ASPHALT_CONCRETE)]
        HydraulicAsphaltConcrete
    }
}