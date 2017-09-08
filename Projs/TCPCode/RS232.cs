using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Threading;

namespace DCCK_Vision
{
    public class RS232 : IDisposable
    {
        private SerialPort _serialport;
        public RS232(string com, string bps, string databit, string stopbit, string check)
        {
            _serialport = new SerialPort();
            //串口端口号
            _serialport.PortName = com;
            //串口波特率
            _serialport.BaudRate = int.Parse(bps);
            //串口数据位
            _serialport.DataBits = int.Parse(databit);
            //串口停止位
            switch (stopbit)
            {
                case "0":
                    _serialport.StopBits = StopBits.None;
                    break;
                case "1":
                    _serialport.StopBits = StopBits.One;
                    break;
                case "1.5":
                    _serialport.StopBits = StopBits.OnePointFive;
                    break;
                case "2":
                    _serialport.StopBits = StopBits.Two;
                    break;
                default:
                    _serialport.StopBits = StopBits.None;
                    break;
            }
            //串口奇偶校验
            switch (check)
            {
                case "无":
                    _serialport.Parity = Parity.None;
                    break;
                case "奇校验":
                    _serialport.Parity = Parity.Odd;
                    break;
                case "偶校验":
                    _serialport.Parity = Parity.Even;
                    break;
                default:
                    _serialport.Parity = Parity.None;
                    break;
            }
        }
        public bool Open()
        {
            try
            {
                if (_serialport.IsOpen)
                    _serialport.Close();
                _serialport.Open();
                return true;
            }
            catch (Exception ex)
            {
                string error = "打开串口出现错误：" + ex.Message;
                Log.WriteLog(error);
                return false;
            }
        }

        public string Read()
        {
            lock (_serialport)
            {
                string data = string.Empty;
                try
                {
                    if (_serialport != null)
                    {
                        if (!_serialport.IsOpen)
                            _serialport.Open();
                        WaitSleep(5);
                        data = _serialport.ReadExisting();
                    }
                }
                catch (Exception ex)
                {
                    string error = "串口读取数据错误，信息为" + ex.Message;
                    Log.WriteLog(error);
                    data = string.Empty;
                }
                return data;
            }
        }

        public bool Write(string data)
        {
            lock (_serialport)
            {
                bool status = false;
                try
                {
                    if (_serialport != null)
                    {
                        if (!_serialport.IsOpen)
                            _serialport.Open();
                        _serialport.Write(data);
                        status = true;
                    }
                }
                catch (Exception ex)
                {
                    string error = "串口写入数据错误，信息为" + ex.Message;
                    Log.WriteLog(error);
                    status = false;
                }
                return status;
            }
        }
        private void WaitSleep(int cc)
        {
            for (int i = 0; i < cc; i++)
            {
                if (_serialport.BytesToRead > 0)
                {
                    Thread.Sleep(20);
                    break;
                }
            }
        }
        public void Dispose()
        {
            if (_serialport != null)
            {
                if (_serialport.IsOpen)
                    _serialport.Close();
                _serialport.Dispose();
            }
        }
    }
}
