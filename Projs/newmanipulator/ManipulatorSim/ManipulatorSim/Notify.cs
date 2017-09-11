using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ManipulatorSim
{
    class Notify
    {
        public Action<Axis> grip { get; set; }
        public Axis EnGrip
        {
            get{return _EnGrip;}
            set
            {
                _EnGrip=value;
                grip(value);
            }
        }

        private Axis _EnGrip;
    }
}
