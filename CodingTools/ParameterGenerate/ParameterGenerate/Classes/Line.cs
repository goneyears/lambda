using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ParameterGenerate.Classes
{
    public enum LexType
    {
        LEX = 1,
        END = 0
    }
    public enum TokenType
    {
        END=0,
        VARIABLE=1,
        STRING=2,
        EQUAL=3
    }
    public enum LineType
    {
        SNR = 1,
        normal = 2
    }
    class Line
    {

        public Line() 
        {


        }
        public Line(string str)
        {
            Original = str;
            GetRegularLine();
            length = RegularLine.Length;
        }
       // private int _length;

        public int length;
  
        public void RemoveAdditionalComment()
        {
            if (Original != null)
            {
                int commentPos = Original.IndexOf("/*");
                if (commentPos == -1)
                {
                    OriginalWithoutComment = Original;

                }
                else
                {
                    OriginalWithoutComment = Original.Substring(0, commentPos);
                }
            }
        }
        public string Original { get; set; }
        public string OriginalWithoutComment { get; set; }
        public void GetRegularLine()
        {
            if (OriginalWithoutComment != null && OriginalWithoutComment != "")
            {
                string spaceTrimed = System.Text.RegularExpressions.Regex.Replace(OriginalWithoutComment, @"\b\s+\b", " ");
                spaceTrimed = spaceTrimed.Replace("\t", "");
                spaceTrimed = spaceTrimed.Trim(' ');
                RegularLine= spaceTrimed;
            }
            else
            {
                RegularLine= "";
            }
        }
        public string RegularLine;


        public string GenSpace(int num)
        {
            string spaceStr = "";
            for(int i=1;i<=num;i++)
            {
                spaceStr = spaceStr + " ";
            }
            return spaceStr;
        }

        
        public string FormatStr<T>(T tstr,int len=999)
        {
            if (len == 999)
            {
                if (typeof(T) == typeof(Int32))
                {
                    len = 3;
                }
                else if (typeof(T) == typeof(string))
                {
                    len = 10;
                }
                else
                {
                    len = 0;//other type of var need to be added
                }
            }

            string str = tstr.ToString();
            if (len > str.Length)
            {
                return str + GenSpace(len - str.Length);
            }
            else
            {
                return str;
            }
        }

        
        public bool IsCharNum(char chr)
        {
            if(Char.IsNumber(chr)|| chr=='.') return true;
            return false;
        }
        public bool IsCharAlpha(char chr)
        {
            if (Char.IsLetter(chr)) return true;
 
            return false;
        }
        public bool IsCharWhiteSpace(char chr)
        {
            if(chr==' ') return true;
            return false;
        }
        public bool IsCharDelim(char chr)
        {
            if(chr=='\\' || chr=='/' || chr=='-' ) return true;
            return false;
        }

        public void Fault()
        {
            MessageBox.Show("Error ");
        }
    }
}
