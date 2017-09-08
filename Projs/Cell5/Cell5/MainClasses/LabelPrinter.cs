using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
using System.Drawing.Printing;
using System.Diagnostics;
using System.IO;
using System.Threading;
namespace Cell5
{
    class LabelPrinter
    {
        public LabelPrinter(PictureBox picbox)
        {
            printImage = picbox;
            picturePrintDocument.PrintPage += new PrintPageEventHandler(picturePrintDocument_PrintPage);
            PrinterTcp = new TCP_Client("192.168.10.50", "50003");

            Messages.WriteLine("PLC通信正常");
            Debug.WriteLine("plc ok");
            PrinterTcp.MessageReceived += AnalyzePLCMessage;
        }


        private TCP_Client PrinterTcp;
        private PictureBox printImage;
        public PrintDocument picturePrintDocument=new PrintDocument();


        private bool status = false;




        public void GetImage(string filename)
        {
            try
            {
                status = connectState(@"\\192.168.10.111\SharedPic\U5", "bm021671", "Phoenix@123");
                Debug.WriteLine("status:   " + status);
                if (status)
                {

                    Messages.WriteLine("已连接文件服务器");
                    //共享文件夹的目录
                    DirectoryInfo theFolder = new DirectoryInfo(@"\\192.168.10.111\SharedPic\U5\");
                    //相对共享文件夹的路径
                    //获取保存文件的路径
                    string fullfileName = theFolder.ToString() + filename;
                    Messages.WriteLine("图片文件:" + fullfileName);
                    printImage.Image = Image.FromFile(fullfileName);
                    printImage.Image.RotateFlip(RotateFlipType.Rotate180FlipNone);
                    Debug.WriteLine("filename:   " + fullfileName);


                }
                else
                {
                    Messages.WriteLine("不能连接文件服务器");
                }

            }
            catch (Exception e)
            {
                Messages.WriteLine("读取打印图片错误，请关闭在本机上打开的远程文件的文件夹并且确认图片存在");
                Messages.WriteLine(e.ToString());
                Debug.WriteLine(e.ToString());
            }

 

        }
        public void PrintImage()
        {
            picturePrintDocument.Print();
        }

        public void TestSendString(){
            PrinterTcp.Send("READY");
        }


        public void AnalyzePLCMessage(Object sender, TCPEventArgs e)
        {
            Debug.WriteLine("receivedMessage:   " + e.receivedmessage);
            string recStr = e.receivedmessage.Replace(" ", "");
            string[] recStrArr = recStr.Split(' ');
            Messages.WriteLine("接收到PLC传送的图片文件名:" + recStr);
            if (recStr.Contains("."))
            {
                Messages.WriteLine("准备从文件服务器读取文件");
                GetImage(recStr);
                Messages.WriteLine("图片读取完成，启动打印机");
                PrintImage();
                Messages.WriteLine("反馈信号给PLC");
                Thread.Sleep(2000);
                PrinterTcp.Send("READY");
                Messages.WriteLine("打印任务发送完成");
                Debug.WriteLine("Print Complete");
            }
            Debug.WriteLine(recStr);


        }

        public void picturePrintDocument_PrintPage(object sender, System.Drawing.Printing.PrintPageEventArgs e)
        {
            try {
                if (printImage.Image != null) {

                    e.Graphics.PageUnit = GraphicsUnit.Document;
                    e.Graphics.SetClip(new Rectangle(50, 40, 350, 150));

                    Debug.WriteLine(e.Graphics.VisibleClipBounds.ToString());
                    e.Graphics.DrawImage(printImage.Image, e.Graphics.VisibleClipBounds);
                    e.HasMorePages = false;
                }
            }
            catch (Exception exception) {
                Messages.WriteLine("打印错误，请检查打印机连接");
            }
        }


        public static bool connectState(string path)
        {
            return connectState(path, "", "");
        }
        /// <summary>
        /// 连接远程共享文件夹
        /// </summary>
        /// <param name="path">远程共享文件夹的路径</param>
        /// <param name="userName">用户名</param>
        /// <param name="passWord">密码</param>
        /// <returns></returns>
        public static bool connectState(string path, string userName, string passWord)
        {
            bool Flag = false;
            Process proc = new Process();
            try
            {
                proc.StartInfo.FileName = "cmd.exe";
                proc.StartInfo.UseShellExecute = false;
                proc.StartInfo.RedirectStandardInput = true;
                proc.StartInfo.RedirectStandardOutput = true;
                proc.StartInfo.RedirectStandardError = true;
                proc.StartInfo.CreateNoWindow = true;
                proc.Start();
                string dosLine = "net use " + path + " " + passWord + " /user:" + userName;
                proc.StandardInput.WriteLine(dosLine);
                proc.StandardInput.WriteLine("exit");
                while (!proc.HasExited)
                {
                    proc.WaitForExit(1000);
                }
                string errormsg = proc.StandardError.ReadToEnd();
                proc.StandardError.Close();
                if (string.IsNullOrEmpty(errormsg))
                {
                    Flag = true;
                }
                else
                {
                    throw new Exception(errormsg);
                }
            }
            catch (Exception ex)
            {
                Messages.WriteLine("文件服务器连接错误");
            }
            //finally
            //{
            //    proc.Close();
            //    proc.Dispose();
            //}
            return Flag;
        }

        /// <summary>
        /// 向远程文件夹保存本地内容，或者从远程文件夹下载文件到本地
        /// </summary>
        /// <param name="src">要保存的文件的路径，如果保存文件到共享文件夹，这个路径就是本地文件路径如：@"D:\1.avi"</param>
        /// <param name="dst">保存文件的路径，不含名称及扩展名</param>
        /// <param name="fileName">保存文件的名称以及扩展名</param>
        public static void Transport(string src, string dst, string fileName)
        {

            FileStream inFileStream = new FileStream(src, FileMode.Open);
            if (!Directory.Exists(dst))
            {
                Directory.CreateDirectory(dst);
            }
            dst = dst + fileName;
            FileStream outFileStream = new FileStream(dst, FileMode.OpenOrCreate);

            byte[] buf = new byte[inFileStream.Length];

            int byteCount;

            while ((byteCount = inFileStream.Read(buf, 0, buf.Length)) > 0)
            {

                outFileStream.Write(buf, 0, byteCount);

            }

            inFileStream.Flush();

            inFileStream.Close();

            outFileStream.Flush();

            outFileStream.Close();

        }
 
    }

    
}
