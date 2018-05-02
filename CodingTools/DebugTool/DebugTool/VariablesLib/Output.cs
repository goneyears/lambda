using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using OPCLib;
namespace VariablesLib
{
    public class Output:Variable
    {
        public Output(string name, OPCClient oc):base(name,oc)
        {
        }
        public void SetValue(bool val)
        {
            _OPCClient.WriteItem(Name, val.ToString());
        }
    }
}
