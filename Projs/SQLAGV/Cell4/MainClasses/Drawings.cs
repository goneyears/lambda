using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace SQLAGV
{
    public class Cell
    {
        public Cell(Graphics g, Point p)
        {
            int height = 20;
            int width = 30;

            pen = new Pen(Color.Black);
            Rectangle rec = new Rectangle(p, new Size(height, width));

            this.g= g;
            this.g.DrawRectangle(pen, rec);

            Center.X = p.X + (height / 2);
            Center.Y = p.Y + (width / 2);
        }
        Graphics g;
        private Pen pen;

        public Point Center;

        public void Connect(Cell desCell)
        {
            g.DrawLine(pen, this.Center, desCell.Center);
        }

        public void Release(Cell desCell)
        {
            g.DrawLine(new Pen(Color.White),this.Center,desCell.Center);
        }
    }
}
