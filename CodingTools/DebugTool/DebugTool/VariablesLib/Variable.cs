using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using OPCLib;
using System.Text.RegularExpressions;
using System.Diagnostics;

namespace VariablesLib
{
    public class Variable
    {
        public Variable(string name, OPCClient oc)
        {
            _OPCClient = oc;
            Name = name;
        }

        protected OPCClient _OPCClient;
        public string Name { get; set; }
        public void SetValue(string val)
        {
            _OPCClient.WriteItem(Name, val);
        }

        public static string Recognize(string varname){

            Match outYN_N = Regex.Match(varname, @"^.*\.OUT_x\+\d\-Y(?<num>\d)/(?<fb>[24]).*");
            if(outYN_N.Success){
                Debug.WriteLine(outYN_N.Groups["num"]);
                Debug.WriteLine(outYN_N.Groups["fb"]);
                return "cylinder";
            }
            Match outAN = Regex.Match(varname, @"^.*\.OUT_x\+\d\-A.*");
            if(outAN.Success){
                return "feeder";
            }
            Match inBN_N = Regex.Match(varname, @"^.*\.IN_x\+\d\-B.*");
            if(inBN_N.Success){
                return "cylinder sensor";
            }
            Match inBN = Regex.Match(varname, @"^.*\.IN_x\+\d\-B.*");
            if (inBN.Success) {
                return "normal sensor";
            }

            return "unknown";
            

        }

    }
}
