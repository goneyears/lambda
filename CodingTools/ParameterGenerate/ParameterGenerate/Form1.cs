using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ParameterGenerate.Classes;
using System.Diagnostics;

//using System.Reflection;
//using System.Linq.Expressions;

namespace ParameterGenerate
{
    public partial class Form1 : Form
    {
        string SachnrInputPath = "";
        string SachnrOutPath = "";


        public Form1()
        {
            InitializeComponent();
        }
        List<List<string>> interList = new List<List<string>>();
        
        private void button1_Click(object sender, EventArgs e)
        {
            string inputPath = System.IO.Path.GetDirectoryName(SachnrInputPath);

            System.IO.StreamReader paraTxt = new System.IO.StreamReader(inputPath+"\\" + "Sachnr.txt");
            System.IO.StreamWriter interParaTxt = new System.IO.StreamWriter( "Sachnr_inter.txt");

           // List<string> interStrArr = new List<string>();
            //string str = "SNR# 1995570-00/10 MSTB 2.5/22-STF-5.08";

            string paraLine;
            while ((paraLine = paraTxt.ReadLine()) != null)
            {
                DefinitionLine pline = new DefinitionLine(paraLine);
                if (pline.Type == LineType.SNR)
                {
                    interParaTxt.WriteLine(pline.OutputLine);
                }

            }

            paraTxt.Close();
           interParaTxt.Close();
            MessageBox.Show("inter transform generate complete");

        }

        private void button2_Click(object sender, EventArgs e)
        {
            string outPath = System.IO.Path.GetDirectoryName(SachnrInputPath);
            System.IO.StreamReader headerTxt = new System.IO.StreamReader( "SachnrHeader.txt");
            System.IO.StreamReader interTxt = new System.IO.StreamReader( "Sachnr_inter.txt");

            System.IO.StreamWriter outParaTxt = new System.IO.StreamWriter(outPath+"\\" + "Sachnr_output.txt",false,Encoding.Default);

            string headerLine;
            while ((headerLine = headerTxt.ReadLine()) != null)
            {
                outParaTxt.WriteLine(headerLine);
            }
            headerTxt.Close();

            string interLine;
            while ((interLine = interTxt.ReadLine()) != null)
            {
                Dictionary<string, string> varDic = new Dictionary<string, string>();
                InterPretLine pline = new InterPretLine(interLine);
                varDic = pline.LexemeToDic();

                //Template transform to output

                if (varDic.Count != 0)
                {
                    string templateLine;
                    System.IO.StreamReader templateTxt = new System.IO.StreamReader( "SachnrTemplate.txt");
                    while ((templateLine = templateTxt.ReadLine()) != null)
                    {
                        TemplateLine tLine = new TemplateLine(templateLine);
                        string outputLine = "";
                        TokenType _tokenType;
                        while (true)
                        {
                            _tokenType = tLine.GetNextToken();

                            if (_tokenType == TokenType.END) break;

                            if (_tokenType == TokenType.VARIABLE)
                            {
                                if (varDic.ContainsKey(tLine.CurrentLexeme))
                                {
                                    outputLine = outputLine + varDic[tLine.CurrentLexeme];
                                }
                                else
                                {
                                    outputLine = outputLine + "0";
                                }
                            }
                            if (_tokenType == TokenType.STRING)
                            {
                                outputLine = outputLine + tLine.CurrentLexeme;
                            }
                        }
                        outParaTxt.WriteLine(outputLine);
                        //  Debug.WriteLine(outputLine);
                    }
                    templateTxt.Close();
                }
            }

            interTxt.Close();
            outParaTxt.Close();

            MessageBox.Show("inter transform generate complete");
        }

        private void FehlerSelectBtn_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileName = new OpenFileDialog();
            fileName.InitialDirectory = Application.StartupPath;
            fileName.Filter = "txt files (*.txt)|*.txt";
            fileName.RestoreDirectory = true;
            if (fileName.ShowDialog() == DialogResult.OK)
            {
                SachnrInputPath = fileName.FileName.ToString();
                FehlerPathBox.Text = SachnrInputPath;
            }
            System.IO.StreamWriter configIni = new System.IO.StreamWriter("config.ini");
            configIni.WriteLine(SachnrInputPath);
            configIni.WriteLine(SachnrOutPath);
            configIni.Close();
        }

        private void FehlerUnicodeBtn_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileName = new OpenFileDialog();
            fileName.InitialDirectory = Application.StartupPath;
            fileName.Filter = "txt files (*.txt)|*.txt";
            fileName.RestoreDirectory = true;
            if (fileName.ShowDialog() == DialogResult.OK)
            {
                SachnrOutPath = fileName.FileName.ToString();
                FehlerUnicodePathBox.Text = SachnrOutPath;
            }
            System.IO.StreamWriter configIni = new System.IO.StreamWriter("config.ini");
            configIni.WriteLine(SachnrInputPath);
            configIni.WriteLine(SachnrOutPath);
            configIni.Close();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            System.IO.StreamReader configIni = new System.IO.StreamReader("config.ini");
            SachnrInputPath = configIni.ReadLine();
            SachnrOutPath = configIni.ReadLine();
            FehlerPathBox.Text = SachnrInputPath;
            FehlerUnicodePathBox.Text = SachnrOutPath;

            configIni.Close();
        }
    }
}
