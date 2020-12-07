#pragma once

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * Class responsible for serving as data model for input data.
     */
    class BoundaryConditionsPerTimeStep
    {
        public:
            double waveHeightHm0;
            double wavePeriodTm10;
            double waveAngle;
        };
}
