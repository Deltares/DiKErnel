#pragma once

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * Class responsible for serving as data model for a revetment.
     */
    class Revetment
    {
        public:
            std::string typeTopLayer;
            double relativeDensity;
            double thicknessTopLayer;
            double initialDamage;
            double similarityParameterThreshold;
            double coefficientPlungingAp;
            double coefficientPlungingBp;
            double coefficientPlungingCp;
            double coefficientPlungingNp;
            double coefficientSurgingAs;
            double coefficientSurgingBs;
            double coefficientSurgingCs;
            double coefficientSurgingNs;
        };
}
