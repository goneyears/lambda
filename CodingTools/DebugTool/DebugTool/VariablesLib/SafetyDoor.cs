﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VariablesLib
{
    public class SafetyDoor : Element
    {      
        public SafetyDoor(string varname,Output O1, Input I1)
            : base(varname,O1, I1)
        {

        }
    }
}