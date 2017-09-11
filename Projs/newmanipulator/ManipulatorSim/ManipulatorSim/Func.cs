using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ManipulatorSim
{
     class r_trig

    {
        
         private bool _Q;
         private bool bfirst=true;

         public void IN(bool signal)
         {
             if (this.Q) this.Q = false;
             if (signal && bfirst)
             {
                 this.Q = true;
                 bfirst = false;
             }
             if (!signal) bfirst = true;


         }

         public bool Q
         {
             get { return _Q; }
             set { _Q = value; }
         }

    }
}
