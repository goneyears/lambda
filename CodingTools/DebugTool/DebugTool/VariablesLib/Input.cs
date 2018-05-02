using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using OPCLib;
namespace VariablesLib
{
    public class Input:Variable
    {
        public Input(string name, OPCClient oc):base(name,oc)
        {
        }
        public bool GetValue()
        {
            object o = _OPCClient.ReadItem(Name);
            return (bool)o;
        }
    
}
}