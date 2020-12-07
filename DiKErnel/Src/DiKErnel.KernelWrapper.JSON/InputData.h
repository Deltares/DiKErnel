#pragma once
#include <vector>

#include "CalculationData.h"
#include "CalculationLocation.h"
#include "HydraulicLoads.h"

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * Class responsible for serving as data model for input data.
     */
    class InputData
    {
        public:
            CalculationData calculationData;
            HydraulicLoads hydraulicLoads;
            std::vector<CalculationLocation> locations;
        };
}
