#pragma once
#include <string>
#include <Revetment.h>

#include "ProfileSchematization.h"

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * \brief Class responsible for serving as data model for a calculation location.
     */
    class CalculationLocation
    {
        public:
            std::string name;
            Revetment revetment;
            ProfileSchematization profileSchematization;
    };
}
