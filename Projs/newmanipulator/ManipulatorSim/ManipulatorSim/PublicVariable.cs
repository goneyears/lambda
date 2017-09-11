using S7PROSIMLib;


namespace ManipulatorSim
{
   public  class Position
   {
       public Position(int ileft,int itop)
       {
           left=ileft;
           top=itop;

       }
       public Position(int ileft, int iright, int itop, int ibottom)
       {
           left = ileft;
           top = itop;
           right = iright;
           bottom = ibottom;

       }
       private int _left;
       private int _top;
       private int _right;
       private int _bottom;
       public int left
       {
           get {return _left;}
           set {_left = value;}
       }
       public int right
       {
           get { return _right; }
           set { _right = value; }
       }
       public int top
       {
           get { return _top; }
           set { _top = value; }
       }
       public int bottom
       {
           get { return _bottom; }
           set { _bottom = value; }
       }


   }

   public class Move
   {
      public  object forward;
      public  object backward;
      public  object upward;
      public  object downward;
      public object grip;
      
   }
   public class Limits
   {
       public bool forward;
       public bool back;
       public bool up;
       public bool down;
       public bool griped;

   }

   public class UserAction
   {
       public bool forward;
       public bool back;
       public bool up;
       public bool down;

       public bool grip;
       public bool release;

       public bool manual;
       public bool home;
       public bool step;
       public bool single;
       public bool continuous;

       public bool start;
       public bool stop;

       public bool emg;

   }


}