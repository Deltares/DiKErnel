#pragma once
#include <vector>

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * Class responsible for serving as data model for calculation data.
     */
    class CalculationData
    {
        public:
            std::vector<int> time;
        };
}
