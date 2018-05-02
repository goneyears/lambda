using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VariablesLib
{
    public class Element
    {
        public Element(string varname,List<IOPair> pairs)
        {
            VarName = varname;
            IOPairs = pairs;

        }
        public Element(string varname,Output O1, Input I1)
        {
            VarName = varname;
            IOPairs.Add(new IOPair(O1, I1));
        }

        public Element(string varname, Output O1, Input I1, Output O2, Input I2)
        {
            VarName = varname;
            IOPairs.Add(new IOPair(O1, I1));
            IOPairs.Add(new IOPair(O2, I2));
        }
        
    
        public string Name{get;set;}

        public string VarName{get;set;}

        public int TestResult{get;set;}

        public List<IOPair> IOPairs{get;set;}

        public void Test()
        {
            TestResult = 1;
            foreach (IOPair p in IOPairs) {
                p.Output.SetValue(true);
                if (p.Input.GetValue() == false) {
                    TestResult = 0;
                    break;
                }
            }
        }
    }
}
