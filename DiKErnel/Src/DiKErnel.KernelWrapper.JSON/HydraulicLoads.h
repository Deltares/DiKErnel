#pragma once
#include <vector>

#include "BoundaryConditionsPerTimeStep.h"

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * Class responsible for serving as data model for hydraulic loads.
     */
    class HydraulicLoads
    {
        public:
            int waveAngleMaximum;
            std::vector<BoundaryConditionsPerTimeStep> boundaryConditionsPerTimeStep;
    };
}
