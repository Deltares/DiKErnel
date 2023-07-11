﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

namespace DiKErnel.DomainLibrary.Defaults.GrassRevetmentWaveImpact
{
    /// <summary>
    /// Class that contains default values for grass revetment wave impact with an open sod
    /// top layer.
    /// </summary>
    public class GrassRevetmentWaveImpactOpenSodTopLayerDefaults : IGrassRevetmentWaveImpactTopLayerDefaults
    {
        public double TimeLineAgwi => 0.8;
        
        public double TimeLineBgwi => -0.00001944;
        
        public double TimeLineCgwi => 0.25;
    }
}