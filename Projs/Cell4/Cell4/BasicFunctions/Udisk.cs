using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.IO;
namespace Cell4
{
    static class Udisk
    {
        public static string drvName;
        public static bool DeviceIn = false;
        public static void DeviceChanged(ref Message m)
        {
            const int WM_DEVICECHANGE = 0x219;
            const int DBT_DEVICEARRIVAL = 0x8000;
            const int DBT_DEVICEREMOVECOMPLETE = 0x8004;

            if (m.Msg == WM_DEVICECHANGE) {
                switch (m.WParam.ToInt32()) {
                    case DBT_DEVICEARRIVAL://U盘插入  
                        DriveInfo[] uin = DriveInfo.GetDrives();
                        foreach (DriveInfo drive in uin) {
                            if (drive.DriveType == DriveType.Removable) {
                                Messages.WriteLine("U盘已插入，盘符为:" + drive.Name.ToString());
                                drvName = drive.Name.ToString().Remove(2);
                                DeviceIn = true;
                                break;
                            }
                        }
                        break;
                    case DBT_DEVICEREMOVECOMPLETE: //U盘卸载  
                        DeviceIn = false;
                        Messages.WriteLine("U盘被拔出！");
                        break;
                    default:
                        break;
                }
            }

        }

        public static void Reject(string drv)
        {
            const uint GENERIC_READ = 0x80000000;
            const int GENERIC_WRITE = 0x40000000;
            const int FILE_SHARE_READ = 0x1;
            const int FILE_SHARE_WRITE = 0x2;
            const int IOCTL_STORAGE_EJECT_MEDIA = 0x2d4808;
            //第一个参数filename与普通文件名有所不同，设备驱动的“文件名”(常称为“设备路径”)形式固定为“\\.\DeviceName”, 如 string filename = @"\\.\I:";
            string filename = @"\\.\" + drv.Remove(2);
            //打开设备，得到设备的句柄handle.
            IntPtr handle = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, IntPtr.Zero, 0x3, 0, IntPtr.Zero);

            // 向目标设备发送设备控制码，也就是发送命令。IOCTL_STORAGE_EJECT_MEDIA  弹出U盘。
            uint byteReturned;
            bool result = DeviceIoControl(handle, IOCTL_STORAGE_EJECT_MEDIA, IntPtr.Zero, 0, IntPtr.Zero, 0, out byteReturned, IntPtr.Zero);

            Debug.WriteLine(result ? "U盘已退出" : "U盘退出失败");


        }



        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern IntPtr CreateFile(
            string lpFileName,
            uint dwDesireAccess,
            uint dwShareMode,
            IntPtr SecurityAttributes,
            uint dwCreationDisposition,
            uint dwFlagsAndAttributes,
            IntPtr hTemplateFile
        );

        [DllImport("kernel32.dll", ExactSpelling = true, SetLastError = true, CharSet = CharSet.Auto)]
        private static extern bool DeviceIoControl(
            IntPtr hDevice,
            uint dwIoControlCode,
            IntPtr lpInBuffer,
            uint nInBufferSize,
            IntPtr lpOutBuffer,
            uint nOutBufferSize,
            out uint lpBytesReturned,
            IntPtr lpOverlapped
        );
    }
}
