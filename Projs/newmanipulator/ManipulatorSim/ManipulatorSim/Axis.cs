using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Windows.Forms;
using System.Drawing;


namespace ManipulatorSim
{
    class Axis
    {
        private PictureBox _picbox ;

        public class iLocation
        {
            public int X;
            public int Y;
        }

        public iLocation OriginLocation = new iLocation();

        public int OriginHeight;
        public Axis( int x,int y)
        {
            OriginLocation.X = x;
            OriginLocation.Y = y;
        }
        public Axis(int x,int y,int height)
        {
            OriginLocation.X = x;
            OriginLocation.Y = y;
            OriginHeight = height;
        }

        
        public PictureBox represent
        { 
           get{return _picbox;}
           set{_picbox=value;}
        }

        public void moveX(int i)
        {
            _picbox.Location = new Point(_picbox.Location.X + i, _picbox.Location.Y);

        }

        public void moveY(int i)
        {
            _picbox.Location = new Point(_picbox.Location.X, _picbox.Location.Y+i);

        }

        private bool _isAttached;
        public bool isAttached
        {
            get { return _isAttached; }
            set { _isAttached = value; }
        }

        public  bool nearby(Axis ax)
        {
            if (Math.Abs(this.represent.Location.X - ax.represent.Location.X) < 10
                &&
                Math.Abs(this.represent.Location.Y+this.represent.Size.Height  - ax.represent.Location.Y) < 10)
            {
                return true;
            }

            return false;
        }
        public void test(int a)
        {
            //return true;
        }
        public void attached(Axis ax)
        {
            this.represent.Location = new Point(ax.represent.Location.X, ax.represent.Location.Y + ax.represent.Size.Height);
            this.isAttached = true;
        }

        public void released(Axis ax)
        {
            this.represent.Location = new Point(this.represent.Location.X, this.OriginLocation.Y);
            this.isAttached = false;
        }

        public void followX(Axis ax)
        {
            int bias;
            bias = this.OriginLocation.X - ax.OriginLocation.X;
           this.represent.Location = new Point(ax.represent.Location.X+bias, this.OriginLocation.Y);
        }

        public void extend(Axis ax)
        {
            int exlength;
            exlength=ax.represent.Location.Y - ax.OriginLocation.Y;
            this.represent.Size = new Size(this.represent.Size.Width, this.OriginHeight + exlength-1);
        }

        public void BackOrigin()
        {
            this.represent.Location = new Point(this.OriginLocation.X-4, this.OriginLocation.Y);
            this.isAttached = false;
        }
    }
}
