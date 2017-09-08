using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using System.Diagnostics;
using System.Text.RegularExpressions;


using System.Reflection;

namespace fehlertranslater
{
    class Line
    {
        public Line(string str, Dictionary<string, string> dic)
        {
            Original = str;

            RemoveAdditionalComment();

            Dic = dic;

            if (OriginalWithoutComment != null && OriginalWithoutComment != "")
            {
                string spaceTrimed = System.Text.RegularExpressions.Regex.Replace(OriginalWithoutComment, @"\b\s+\b", " ");
                spaceTrimed = spaceTrimed.Replace("\t", "");
                spaceTrimed = spaceTrimed.Trim(' ');
                RegularLine = spaceTrimed;
            }
            else
            {
                RegularLine = "";
            }

            if (
                (RegularLine.Length > 0)
                &&
                    (
                         (RegularLine[0] == 'F' || RegularLine[0] == 'K') && (RegularLine[1] == '#')
                       || ((RegularLine[0] == 'S') && (RegularLine[1] == 'T') && (RegularLine[2] == '#'))
                     )
                )
            {
                Type = LineType.fehler;
            }
            else
            {
                Type = LineType.normal;
            }


            if (Type == LineType.fehler)
            {
                int spacePos = RegularLine.IndexOf(" ");
                if (spacePos > 0)
                {
                    FehlerNumber = RegularLine.Substring(0, spacePos);
                }
                else if (spacePos < 0)
                {
                    FehlerNumber = RegularLine;
                }
                else
                {
                    FehlerNumber = "TrimError";
                }
            }
            else
            {
                FehlerNumber = "";
            }


                if (Type == LineType.fehler)
                {
                    string endSym = RegularLine.Substring(RegularLine.Length - 1, 1);
                    if (endSym == "!" || endSym == "?" || endSym == ".")
                    {
                        EndSymbol= endSym;
                    }
                    else
                    {
                        EndSymbol= "";
                    }
                }
                else
                { EndSymbol= ""; }




            if (Type == LineType.fehler)
            {
                string tempBlock = System.Text.RegularExpressions.Regex.Replace(RegularLine, FehlerNumber, " ");
                if (EndSymbol != "")
                {
                    tempBlock = tempBlock.Trim(EndSymbol.ToCharArray());
                }
                tempBlock = tempBlock.Trim(' ');
                OriginalBlock = tempBlock;
            }
            else
            {
                OriginalBlock = OriginalWithoutComment;
            }

            if (Type == LineType.fehler)
            {
                Translation = TranslateDecrease();
            }
            else
            {
                Translation = Original;
            }

        }

        public enum LineType
        {
            fehler=1,
            normal=2
        }
        public enum TranslationResult
        {
            NotYet = 0,
            None = 1,
            Partial = 2,
            Full = 3,
            Well = 4
        }

        private Dictionary<string, string> Dic { get; set; }

        private void RemoveAdditionalComment()
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
        public string Original {get;set;}



        public string OriginalWithoutComment { get; set; }
        public string Translation { get; set; }

        public string OriginalBlock;//RegularLine's OriginalBlock(remove F# or K#
        public string TranslatedBlock;
        


        public string FehlerNumber;

        public string EndSymbol;

        //public string UnTransBlock { get; set; }
        private TranslationResult _result = TranslationResult.NotYet;
        public TranslationResult TransResult
        {
          
            get
            {
               return _result;
            }
            set
            {
                _result = value;
            }
        }
        public LineType Type;

        private string RegularLine;


        public string Translate()
        {
            TransResult = TranslationResult.Full;
            string[] fehlerWords = OriginalBlock.Split(' ');
            string tempTranslatedBlock = "";//with untranswords
            //UnTransBlock = string.Join(" ", fehlerWords, 1, 2);
            
            int startTransPos = 0;
            int lastTransPos = 0;
            while (startTransPos < fehlerWords.Length)
            {
                bool beTranslated = false;
                string increasedWord = "";

                string wordsBlock = "";

                for (int iScan = startTransPos; iScan <= fehlerWords.Length - 1; iScan++)
                {
                    string tempResult = "";
                    increasedWord = ConnectStr(increasedWord, fehlerWords[iScan]);
                    Debug.WriteLine("increasedword : " + increasedWord);
                    if (TranslateWord(increasedWord, ref tempResult))
                    {
                        wordsBlock = tempResult;
                        lastTransPos = iScan;
                        beTranslated = true;
                        if(startTransPos==0 && iScan==fehlerWords.Length-1)
                        {
                            TransResult = TranslationResult.Well;
                            TranslatedBlock = wordsBlock;
                            return FehlerNumber + " " + TranslatedBlock + EndSymbol;
                            
                        }
                        Debug.WriteLine("resultBlock: " + wordsBlock);
                    }

                }

                    if (beTranslated)
                    {
                        startTransPos = lastTransPos + 1;
                        tempTranslatedBlock = tempTranslatedBlock + wordsBlock;
                    }
                    else
                    {
                        tempTranslatedBlock = tempTranslatedBlock + " " + fehlerWords[startTransPos];
                        startTransPos++;
                        TransResult = TranslationResult.Partial;
                    }
                
            }

            TranslatedBlock = tempTranslatedBlock;
            return FehlerNumber +" "+ TranslatedBlock + EndSymbol;

        }
        public string TranslateDecrease()
        {
            TransResult = Line.TranslationResult.Full; //set full before translate
            TranslateLine(OriginalBlock);
            return FehlerNumber + " " + TranslatedBlock + EndSymbol;

        }
        private string SubString(string[] str,int iStart,int iEnd)
        {
            string tempStr = str[iStart];
            for (int i = iStart+1; i <= iEnd; i++)
            {
                tempStr = tempStr +" "+ str[i];
            }
            return tempStr;

        }
        private void TranslateLine(string inputWords)
        {
            //TransResult = TranslationResult.Full;
            string[] fehlerWords = inputWords.Split(' ');
            
            int fehlerWordsEndPos=fehlerWords.Length - 1;
            int lastTransPos = fehlerWordsEndPos;
            string decreasedWords = SubString(fehlerWords,0,fehlerWordsEndPos);

            string transWordsBlock = "";
            
            int iStart;
            for (iStart = 0; iStart <= fehlerWordsEndPos;iStart++ )
            {

                decreasedWords = SubString(fehlerWords, iStart, fehlerWordsEndPos);
                transWordsBlock = decreasedWords;
                if (TranslateWord(decreasedWords, ref transWordsBlock))
                {
                    lastTransPos = iStart;
                    break;
                }

            }

            if(iStart==0)//full translated exit translate loop
            {
                TranslatedBlock = transWordsBlock + TranslatedBlock;
               // return TranslatedBlock;

            }
            else if(lastTransPos==0 && iStart>0)// non translation of the last wordblock
            {
                TransResult = TranslationResult.Partial;
                TranslatedBlock = transWordsBlock +" "+ TranslatedBlock; ;
                //return OriginalBlock;

            }
            else
            {
                if (iStart > lastTransPos)
                {
                    transWordsBlock = transWordsBlock + " "; //no word be translated then add space to the last word
                    TransResult = TranslationResult.Partial;
                }
                TranslatedBlock = transWordsBlock + TranslatedBlock;
 
                string subWords= SubString(fehlerWords,0,lastTransPos-1);
                TranslateLine(subWords);
            }

            //return "error occured!!!!!";
        }

        private bool TranslateWord(string inputWord, ref string outputWord)
        {
            //add case

            if (Dic.Keys.Contains(inputWord.ToUpper()))
            {
                outputWord = Dic[inputWord.ToUpper()];
                return true;
            }
            else if(IsNumeric(inputWord))
            {
                outputWord = inputWord;
                return true;
            }
            else
            {
                outputWord = inputWord;
                return false;
            }

        }
        private bool IsNumeric(string str)
        {
            for(int i=0;i<str.Length;i++)
            {
                if (!char.IsNumber(str[i])) return false;
            }
            return true;
        }
        private string ConnectStr(string str, string addStr)
        {
            if (str != "")
            {
                return str + " " + addStr;
            }
            else
            {
                return addStr;
            }
        }

        //private bool Match(string str)
        //{

        //}
    }
}
