using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using System.Diagnostics;

namespace SQLAGV
{
    class USBCopyer
    {
        public USBCopyer()
        {
            Messages.WriteLine("建立USB复制-PLC通信连接");
            copyTcp = new TCP_Client("192.168.10.40", "50001");
            
            copyTcp.MessageReceived += AnalyzePLCMessage;
        }
        private TCP_Client copyTcp; 
        public enum CopyResult
        {
            UNKNOWN=0,
            GOOD=1,
            NOUDISK=2,
            MISSTORAGE=3,
            COPYFAILED=4
        }
        public static CopyResult CopyFilesToUDisk(string srcDir,List<string> filelist)
        {
            CopyResult result = 0;
            bool uexist = false;
            bool ustorageok = false;

            List<string> Udisks = new List<string>();
            //find all removable disks
            DriveInfo[] drvInfos = DriveInfo.GetDrives();
            foreach (DriveInfo drv in drvInfos) {
                Debug.WriteLine(drv.ToString());
                if (drv.DriveType == DriveType.Removable) {
                    uexist = true;
                    Messages.WriteLine("U盘容量:" + drv.TotalSize);
                    if (7000000000 < drv.TotalSize && drv.TotalSize < 9000000000) {
                        Udisks.Add(drv.ToString());
                        ustorageok = true;
                        break;
                        // Debug.WriteLine(i.ToString());
                    }
                }
            }

            //copy file
           
            bool copyComplete = false;
            foreach (string u in Udisks) {
                if (FileSys.CopyFiles(srcDir, u, filelist)) {
                    copyComplete = true;
                    Messages.WriteLine("文件复制成功");
                }
                Messages.WriteLine("弹出U盘");
                Udisk.Reject(u);
                break;//copy file to the first udisk then break;

            }

            if (uexist && ustorageok && copyComplete) {
                
                result = CopyResult.GOOD;
            }
            else if (!uexist || !ustorageok) {
                result = CopyResult.MISSTORAGE;
            }
            else if (!copyComplete) {
                result = CopyResult.COPYFAILED;
            }
            else {
                result = CopyResult.UNKNOWN;
            }

            Messages.WriteLine("文件复制结果:" + result.ToString());

            return result;
        }
       
        public void UdiskCopyTest()
        { 
            CopyResult copyResult = 0;

            //string srcDir = @"C:\Users\BM021671\Documents\ProjectFiles\Cell4\SourceFiles\";
            string srcDir = @"C:\a";
            copyResult = CopyFilesToUDisk(srcDir,Common.copyfilelist); 
            Debug.WriteLine("udisktest copyresult " + copyResult.ToString());
            if (copyResult == CopyResult.GOOD) {
                copyTcp.Send("Copy Test Complete");
            }
            else if (copyResult == CopyResult.COPYFAILED) {
                copyTcp.Send("Copy Test Failed");
            }
            else if (copyResult == CopyResult.MISSTORAGE) {
                copyTcp.Send("Storage Error");
            }
            else {
                copyTcp.Send("Unknown Result");
            } 
        }

        public void AnalyzePLCMessage(Object sender, TCPEventArgs e)
        {
            string str = e.receivedmessage;
            if (str == "copy") {
                UdiskCopyTest();
            }
            Debug.WriteLine(str);
        }
    }
}
