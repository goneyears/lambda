using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Cell4
{
    class CameraColorTestTransfer
    {
        public CameraColorTestTransfer()
        {
            Messages.WriteLine("建立CameraColor-PLC通信连接");
            PCCameraTcp = new TCP_Client("192.168.10.49", "9001");
            PLCTcp = new TCP_Client("192.168.10.40", "29001");

            PCCameraTcp.MessageReceived += AnalyzePCCameraMessage;
            PLCTcp.MessageReceived += AnalyzePLCMessage;
            
        }

        private TCP_Client PCCameraTcp;
        private TCP_Client PLCTcp;


        private void AnalyzePCCameraMessage(object sender, TCPEventArgs e)
        {
            PLCTcp.Send(e.receivedmessage);

            Messages.WriteLine("PC Camera to PLC" + e.receivedmessage);
        }




        public void AnalyzePLCMessage(Object sender, TCPEventArgs e)
        {

            PCCameraTcp.Send(e.receivedmessage);
            Messages.WriteLine("PLC To PC Camera"+e.receivedmessage);
        }
    }
}
