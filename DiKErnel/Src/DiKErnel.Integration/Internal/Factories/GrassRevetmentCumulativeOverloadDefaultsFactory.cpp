// Copyright (C) Stichting Deltares 2022. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#include "GrassRevetmentCumulativeOverloadDefaultsFactory.h"

#include "DefaultsFactoryException.h"
#include "GrassRevetmentCumulativeOverloadClosedSodTopLayerDefaults.h"
#include "GrassRevetmentCumulativeOverloadOpenSodTopLayerDefaults.h"

namespace DiKErnel::Integration
{
    using namespace DomainLibrary;
    using namespace std;

    unique_ptr<IGrassRevetmentCumulativeOverloadTopLayerDefaults> GrassRevetmentCumulativeOverloadDefaultsFactory::CreateTopLayerDefaults(
        const GrassRevetmentTopLayerType topLayerType)
    {
        switch (topLayerType)
        {
            case GrassRevetmentTopLayerType::ClosedSod:
                return make_unique<GrassRevetmentCumulativeOverloadClosedSodTopLayerDefaults>();
            case GrassRevetmentTopLayerType::OpenSod:
                return make_unique<GrassRevetmentCumulativeOverloadOpenSodTopLayerDefaults>();
            default:
                throw DefaultsFactoryException("Couldn't create defaults for the given top layer type.");
        }
    }
}
