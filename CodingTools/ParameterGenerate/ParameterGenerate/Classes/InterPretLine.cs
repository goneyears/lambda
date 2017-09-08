using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ParameterGenerate.Classes
{
    class InterPretLine:Line
    {
 
        
 
 
        public InterPretLine(string str)
        {
            Original = str;
            RemoveAdditionalComment();
            GetRegularLine();
            length = RegularLine.Length;
            currentPosition = 0;

        }

        private int currentPosition;
        public string CurrentLexeme { get; set; }
  
 #region Lexeme process
        public Dictionary<string, string> LexemeToDic()
        {
            Dictionary<string,string> varDic = new Dictionary<string,string>();
            TokenType _tokenType;
            string lastVariable = "";
            while (true)
            {
                _tokenType = GetNextToken();

                if (_tokenType == TokenType.END) break;

                if(_tokenType==TokenType.VARIABLE)
                {
                    varDic.Add(CurrentLexeme,"");
                    lastVariable = CurrentLexeme;
                }
                if (_tokenType == TokenType.STRING)
                {
                    varDic[lastVariable] = CurrentLexeme;
                }
            }
            return varDic;
        }
        private char GetNextChar()
        {
            if(currentPosition<length) return RegularLine[currentPosition++];
            currentPosition++;
            return '\0';
        }
        public TokenType GetNextToken()
        {
            const int LEX_STATE_START=1;
            const int LEX_STATE_VARIABLE = 2;
            const int LEX_STATE_EQUAL = 3;
            const int LEX_STATE_STRING = 4;
            const int LEX_STATE_STRING_CLOSE_QUOTE = 5;


            if (currentPosition >= length) return TokenType.END;
            string currLexeme = "";
            int iCurrLexState=LEX_STATE_START;
            while (true)
            {
                bool addChar = false ;
                bool lexDone = false ;
                char cChar = GetNextChar();
                if (cChar == '\0') break;
                
                switch(iCurrLexState)
                {
                    case LEX_STATE_START:
                        if (IsCharWhiteSpace(cChar))
                        {
                            addChar = false;
                        }

                        if (IsCharAlpha(cChar) || IsCharNum(cChar))
                        {
                            addChar = true;
                            iCurrLexState = LEX_STATE_VARIABLE;
                        }
                        if(cChar=='=')
                        {
                            addChar = true;
                            iCurrLexState = LEX_STATE_EQUAL;
                        }
                        if(cChar=='\"')
                        {
                            addChar = false;
                            iCurrLexState = LEX_STATE_STRING;
                        }
                       break;
                    case LEX_STATE_VARIABLE:
                        if (IsCharWhiteSpace(cChar))
                        {
                            addChar = false;
                            lexDone = true;
                        }

                        if (IsCharAlpha(cChar) || IsCharNum(cChar))
                        {
                            addChar = true;
                            iCurrLexState = LEX_STATE_VARIABLE;
                        }
                       break;
                    case LEX_STATE_EQUAL:
                      
                        addChar = false;
                        lexDone = true;

                        break;

                      
                    case LEX_STATE_STRING:

                       addChar = true;

                       if (cChar == '\"')
                       {

                           addChar = false;
                           iCurrLexState = LEX_STATE_STRING_CLOSE_QUOTE;
                       }
                       break;
                    case LEX_STATE_STRING_CLOSE_QUOTE:
                        addChar = false;
                        lexDone = true;
                        break;
                }

                if (addChar) currLexeme = currLexeme + cChar;
                if (lexDone)
                {
                    break;
                }
            }
            --currentPosition;

            TokenType _tokenType;
            switch(iCurrLexState)
            {
                case LEX_STATE_VARIABLE:
                    _tokenType = TokenType.VARIABLE;
                    break;
                case LEX_STATE_EQUAL:
                    _tokenType = TokenType.EQUAL;
                    break;
                case LEX_STATE_STRING_CLOSE_QUOTE:
                    _tokenType = TokenType.STRING;
                    break;

                default:
                    _tokenType = TokenType.END;
                    break;

            }

            CurrentLexeme = currLexeme;
            return _tokenType;

        }
#endregion


    }
}
