using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ParameterGenerate.Classes
{

    class DefinitionLine:Line
    {
        public List<string> lineLexeme = new List<string>();
        public string _housingType;
        public bool _isFlange;
        public string _teilmass;
        public string _color;
        public int _poleNumber;
        public string _serialNumber;
        public int _numberOfHousings;


        string HousingName, Teilmass, PoleNumber, Speed, NumberOfHousings, SPSFlange, SPSScrewType, SPSFlangeScrewType
             , CameraColor, CameraFlange, CameraHousingType, CameraScrewType, CameraFlangeScrewType, SerialNumber
             , MG1, MG2, Axis1, Axis2
             , MG1Axis1Offset0, MG1Axis1Offset1, MG1Axis1Offset2, MG1Axis1Offset3, MG1Axis1Offset4, MG1Axis1Offset5, MG1Axis1Offset6, MG1Axis1Offset7, MG1Axis1Offset8, MG1Axis1Offset9, MG1Axis1Offset10
             , MG1Axis2Offset0, MG1Axis2Offset1, MG1Axis2Offset2, MG1Axis2Offset3, MG1Axis2Offset4, MG1Axis2Offset5, MG1Axis2Offset6, MG1Axis2Offset7, MG1Axis2Offset8, MG1Axis2Offset9, MG1Axis2Offset10
             , MG2Axis1Offset0, MG2Axis1Offset1, MG2Axis1Offset2, MG2Axis1Offset3, MG2Axis1Offset4, MG2Axis1Offset5, MG2Axis1Offset6, MG2Axis1Offset7, MG2Axis1Offset8, MG2Axis1Offset9, MG2Axis1Offset10;

        public string OutputLine { get; set; }
        public DefinitionLine(string str)
        {
            Original = str;
            RemoveAdditionalComment();
            GetRegularLine();
            length = RegularLine.Length;
            CurrentPosition = 0;
            if (Type == LineType.SNR)
            {
                GetAllLexeme();
                DecodeSNRInformation(lineLexeme);
                InformationToFormatList();
                FormatListToLine();
            }

        }


        public List<string> interLineList=new List<string>();

        private int CurrentPosition { get; set; }

        public void DecodeSNRInformation(List<string> lst)
        {
            //SNR 5452586 00 010 BCP 508F 20 BK
            //SNR 1757019 00 010 MSTB 2.5 2 ST 5.08

            _housingType = lst[4];
            string lstStr=string.Join(" ",lst.ToArray());
            if (lstStr.Contains("F"))
            {
                _isFlange = true;
            }
            else
            {
                _isFlange = false;
            }

            if(lstStr.Contains("5.08")||lstStr.Contains(" 508"))
            {
                _teilmass = "508";
            }
            else if(lstStr.Contains("5.00")||lstStr.Contains(" 500"))
            {
                _teilmass = "500";
            }
            else
            {
                throw new Exception("Error teilmass, not 500 or 508");
            }

            if(lstStr.Contains("GN"))
            {
                _color = "GN";
            }
            else if(lstStr.Contains("GY"))
            {
                _color = "GY";
            }
            else if(lstStr.Contains("BK"))
            {
                _color="BK";
            }
            else
            {
                _color = "GN";
            }

            _poleNumber = int.Parse(lst[6]);
            _serialNumber = lst[1];

            _numberOfHousings = CalcNumberOfHousings();

            ExtendInfoAnalysis();

            //return FormatStr(serialNumber) + FormatStr(housingType) + FormatStr(isFlange) + FormatStr(teilmass) + FormatStr(color) + FormatStr(poleNumber);

        }
        public void ExtendInfoAnalysis()
        {
              //  HousingName
            HousingName = GenType();
            Teilmass = _teilmass[0] + "." + _teilmass[1] + _teilmass[2];
            PoleNumber = _poleNumber.ToString();
            Speed = "120";
            NumberOfHousings = _numberOfHousings.ToString();
            SPSFlange = _isFlange?"1":"0";
            SPSScrewType = GenSPSScrewType();
            SPSFlangeScrewType = GenSPSFlangeScrewType();
            CameraColor = GenCamColor();
            CameraFlange = _isFlange ? "1" : "0";
            CameraHousingType = GenCamHousingType();
            CameraScrewType = CameraHousingType;
            CameraFlangeScrewType = CameraHousingType;
            SerialNumber = _serialNumber;
            MG1 = "1";
            MG2 = "2";
            Axis1 = "1";
            Axis2 = "2";

            switch (_numberOfHousings)
            {
                case 1:
                    {
                        MG1Axis1Offset1 = "0.00";
                        MG1Axis1Offset2 = "0.00";
                        MG1Axis1Offset3 = "0.00";


                        break;
                    }

                case 2:
                    {
                        MG1Axis1Offset1 = "0.00";
                        MG1Axis1Offset2 = "123.00";
                        MG1Axis1Offset3 = "0.00";
 
                        break;
                    }
                case 3:
                    {
                        MG1Axis1Offset1 = "0.00";
                        MG1Axis1Offset2 = "47.20";
                        MG1Axis1Offset3 = "123.00";
 
                        break;
                    }
                default:
                    {
                        throw new Exception("error number of housings");
                      
                    }
            } 
            MG1Axis1Offset6 = "1.90";
            MG1Axis1Offset7 = "20.354";
            MG1Axis1Offset8 = "83.000";
            MG1Axis1Offset9 = "97.50";
            MG2Axis1Offset1 = MG1Axis1Offset1;
            MG2Axis1Offset2 = MG1Axis1Offset2;
            MG2Axis1Offset3 = MG1Axis1Offset3;
            MG2Axis1Offset4 = "10.00";
            //SPSFlangeScrewType=
        }
        private string GenSPSScrewType()
        {
            if (_housingType == "MSTB")
            {
                return "1";
            }
            else if (_housingType == "BCP")
            {
                return "10";
            }
            throw new Exception("Error HousingType, not MSTB or BCP");
            //return "error";
        }
        private string GenSPSFlangeScrewType()
        {
            if(_isFlange)
            {
                if (_housingType == "MSTB")
                {
                    return "1";
                }
                else if (_housingType == "BCP")
                {
                    return "10";
                }
                else
                {
                    throw new Exception("Error HousingType, not MSTB or BCP");
                }
            }
            else
            {
                return "0";
            }

        }
        private string GenCamColor()
        {
            if (_color == "GY")
            {
                return "8";
            }
            else if (_color == "BK")
            {
                return "1";
            }

            if (_housingType == "MSTB" && _color == "GN")
            {
                return "0";
            }
            else if (_housingType == "BCP" && _color == "GN")
            {
                return "23";
            }
            throw new Exception("Error Camera Color");
        }

        private string GenCamHousingType()
        {
            if (_housingType == "MSTB")
            {
                return "0";
            }
            else if (_housingType == "BCP")
            {
                return "1";
            }
            throw new Exception("Error HousingType, not MSTB or BCP");
        }
        public void InformationToFormatList()
        {
            interLineList.Add("HousingName =\"" +FormatStr( HousingName,22    )      +"\"");
            interLineList.Add("Teilmass =\"" + Teilmass             +"\"");
            interLineList.Add("PoleNumber =\"" + FormatStr(PoleNumber ,2)          +"\"");
            interLineList.Add("Speed =\"" + Speed                +"\"");
            interLineList.Add("NumberOfHousings =\"" + NumberOfHousings     +"\"");
            interLineList.Add("SPSFlange =\"" + SPSFlange            +"\"");
            interLineList.Add("SPSScrewType =\"" +  FormatStr(SPSScrewType ,2)        +"\"");
            interLineList.Add("SPSFlangeScrewType =\"" + FormatStr( SPSFlangeScrewType,2)   +"\"");
            interLineList.Add("CameraColor =\"" + FormatStr( CameraColor ,2)         +"\"");
            interLineList.Add("CameraFlange =\"" + CameraFlange         +"\"");
            interLineList.Add("CameraHousingType =\"" + CameraHousingType    +"\"");
            interLineList.Add("CameraScrewType =\"" + CameraScrewType      +"\"");
            interLineList.Add("CameraFlangeScrewType =\"" + CameraFlangeScrewType+"\"");
            interLineList.Add("SerialNumber =\"" + SerialNumber         +"\"");
            interLineList.Add("MG1 =\"" + MG1                  +"\"");
            interLineList.Add("MG2 =\"" + MG2                  +"\"");
            interLineList.Add("Axis1 =\"" + Axis1                +"\"");
            interLineList.Add("Axis2 =\"" + Axis2                +"\"");
            interLineList.Add("MG1Axis1Offset1 =\"" + FormatStr( MG1Axis1Offset1 ,6) + "\"");
            interLineList.Add("MG1Axis1Offset2 =\"" + FormatStr( MG1Axis1Offset2 ,6) + "\"");
            interLineList.Add("MG1Axis1Offset3 =\"" + FormatStr(MG1Axis1Offset3, 6) + "\"");


            interLineList.Add("MG1Axis1Offset6 =\"" +FormatStr( MG1Axis1Offset6 ,6)     +"\"");
            interLineList.Add("MG1Axis1Offset7 =\"" + MG1Axis1Offset7      +"\"");
            interLineList.Add("MG1Axis1Offset8 =\"" + MG1Axis1Offset8      +"\"");
            interLineList.Add("MG1Axis1Offset9 =\"" + MG1Axis1Offset9      +"\"");

            interLineList.Add("MG2Axis1Offset1 =\"" + FormatStr(MG2Axis1Offset1, 6) + "\"");
            interLineList.Add("MG2Axis1Offset2 =\"" + FormatStr(MG2Axis1Offset2, 6) + "\"");
            interLineList.Add("MG2Axis1Offset3 =\"" + FormatStr(MG2Axis1Offset3, 6) + "\"");
            interLineList.Add("MG2Axis1Offset4 =\"" + FormatStr(MG2Axis1Offset4, 6) + "\"");
        }
        public void FormatListToLine()
        {
            OutputLine = string.Join("      ", interLineList.ToArray());
        }


        public int CalcNumberOfHousings()
        {
            int[,] poleHousingArr;
            poleHousingArr = new int[2,25]{//    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24
                                            { 0, 0, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                            { 0, 0, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

                                        };
            int isF = _isFlange ? 1 : 0;
            return poleHousingArr[isF, _poleNumber];
            //if (_poleNumber <= 7)
            //{
            //    return 3;
            //}
            //else if (8 <= _poleNumber && _poleNumber <= 12)
            //{
            //    return 2;
            //}
            //else if (13 <= _poleNumber && _poleNumber <= 24)
            //{
            //    return 1;
            //}
            //return 0;
        }

        private string GenType()
        {
            if (_housingType == "MSTB")      //BS# MSTB 2.5/3-ST-5.08
            {
                string st = _isFlange ? "STF" : "ST";
                string teilStr = _teilmass[0] + "." + _teilmass[1] + _teilmass[2];

                return "MSTB 2.5/" + _poleNumber.ToString() + "-" + st + "-" + teilStr;
            }
            else if (_housingType == "BCP")    //BS# BCP-508F-3 BK
            {
                string st = _isFlange ? "F" : ""; 

                return "BCP-" + _teilmass + st + "-" + _poleNumber.ToString() + " " + _color;
            }
            else
            {
                return "error of type";
            }


        }
        public void GetAllLexeme()
        {
            LexType _lexType;
            _lexType=GetNextLex();
            while (_lexType != LexType.END)
            {
                _lexType = GetNextLex();
            }


        }
        public char GetNextChar()
        {
            if(CurrentPosition<length) return RegularLine[CurrentPosition++];
            CurrentPosition++;
            return '\0';
        }
        public LexType GetNextLex()
        {
            const int LEX_STATE_START=1;
            const int LEX_STATE_LEX = 2;

            if(CurrentPosition>=length) return LexType.END;
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
                        if (IsCharWhiteSpace(cChar)|| IsCharDelim(cChar))
                        {
                            addChar = false;
                        }

                        if (IsCharAlpha(cChar) || IsCharNum(cChar))
                        {
                            addChar = true;
                            iCurrLexState = LEX_STATE_LEX;
                        }
                       break;
                    case LEX_STATE_LEX:
                        if (IsCharWhiteSpace(cChar)|| IsCharDelim(cChar))
                        {
                            addChar = false;
                            lexDone = true;
                        }

                        if (IsCharAlpha(cChar) || IsCharNum(cChar))
                        {
                            addChar = true;
                            iCurrLexState = LEX_STATE_LEX;
                        }
                       break;

                }

                if (addChar) currLexeme = currLexeme + cChar;
                if (lexDone) break;
            }
            --CurrentPosition;
            LexType _lexType;
            switch(iCurrLexState)
            {
                case LEX_STATE_LEX:
                    _lexType=LexType.LEX;
                    break;
                default:
                    _lexType=LexType.END;
                    break;

            }
            lineLexeme.Add(currLexeme);
            return _lexType;

        }


        public LineType Type
        {
            get
            {

                if (
                    (RegularLine.Length > 4)
                    &&
                        (
                             (RegularLine[0] == 'S' && RegularLine[1] == 'N' && RegularLine[2] == 'R' && RegularLine[3] == '#')
                         )
                    )
                {
                    return LineType.SNR;
                }
                else
                {
                    return LineType.normal;
                }
            }
        }
        

    }
}
