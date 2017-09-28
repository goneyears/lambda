using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
namespace SQLAGV
{
    public static class Messages
    {

        public static string Text; 

        public static void WriteLine(string newMessage)
        {
            newMessage = System.DateTime.Now.ToString() + "  " + newMessage;
            Text = Text + newMessage + "\r\n";
             
            
            
        }


    }
}
