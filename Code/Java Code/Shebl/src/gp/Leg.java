package gp;

/**
 *
 * @author Abdelrahman
 */
public class Leg {

       public double ID = -1;             //Leg Number, -1 not initialized
       public double Xb = 0;              //The Distance from Origin on the X axis
       public double Yb = 0;              //The Distance form Origin on the Y axis
       public double  Inv = -1;            //Is the Leg flipped (Is it Forward Leg)
       public double  Right = 1;           //Is the Leg on the right side of the robot
       public double[] Theta = {0, 45, 90}; //The Joint's Angles
       public double[] Len = {8, 10.5, 13.1, 1.8}; //Leg Dimentions
       public double[] Swing_Theta;         //The Theta's in the Swing Phase
       public double[] foot;                //The Foot Point
       public double Tup = 0.25;          //Time of rising the leg
       public double Tdown = 0.25;        //Time of downing the leg
       public double Tdisp = 0.5;         //Time of moving the leg
       public double disp = 4;            //The displacement distance
       public double h = 4;
       
       //Constructor
       public Leg(double id, double xb, double yb, double inv, double r)
       {
           ID = id;
           if(inv == 1)
               Xb = xb;
           else
               Xb = -xb;
           
           if(r == 1)
               Yb = -yb;
           else
               Yb = yb;

           Inv = inv;
           Right = r;
           Swing_Theta = new double[6];
           foot = Link3();
       }
       
       //Update Leg
       public void Update(double T0, double T1, double T2)
       {
           if(Theta.length < 3)
           {
               System.out.println("Logical Error in Leg.Update");
               return;
           }
           Theta[0] = T0;
           Theta[1] = T1;
           Theta[2] = T2;
           foot = Link3();
       }
       
       //Move Leg
       public void Move()
       {
           //Get the Velocity of rising the Leg in Z axis
           //Vup = L.h/L.Tup;
           double X = foot[0] - Xb;
           double Z = foot[2] + h;
           if(Inv == 1)
               X = -X;
           
           double T2 = Util.Theta2(X, Z, Theta[0]);
           double T1 = Util.Theta1(X, Z, Theta[0], T2);
           Swing_Theta[0] = T1;
           Swing_Theta[1] = T2;
           //L.Theta = [L.Theta(1), T1, T2];
           Theta[1] = T1;
           Theta[2] = T2;
           foot = Link3();
           
           //Get the Velocity of moving the Leg forward in x axis
           //Vdisp = L.disp/L.Tdisp;
           X = foot[0] - Xb;
           Z = foot[2];
           X = X + disp;
           if(Inv == 1)
               X = -X;
           
           T2 = Util.Theta2(X, Z, Theta[0]);
           T1 = Util.Theta1(X, Z, Theta[0], T2);
           Swing_Theta[2] = T1;
           Swing_Theta[3] = T2;
           //L.Theta = [L.Theta(1), T1, T2];
           Theta[1] = T1;
           Theta[2] = T2;
           foot = Link3();
           
           //Get the Velocity of downing the Leg in z axis
           //Vdown = -L.h/L.Tdown;
           X = foot[0] - Xb;
           Z = foot[2] - h;
           if(Inv == 1)
               X = -X;
           
           T2 = Util.Theta2(X, Z, Theta[0]);
           T1 = Util.Theta1(X, Z, Theta[0], T2);
           Swing_Theta[4] = T1;
           Swing_Theta[5] = T2;
           //L.Theta = [L.Theta(1), T1, T2];
           Theta[1] = T1;
           Theta[2] = T2;
           foot = Link3();
       }
       
       public void Move_Disp(double X, double Y)
       {
           double X_abs = Math.abs(X);
           double Y_abs = Math.abs(Y);
           if((X_abs < Math.pow(10, -10)) && (Y_abs < Math.pow(10, -10)))
               return;
           
           //Get the Req angles to set the foot at (X, Y) from COM
           double X_Old = foot[0] - Xb;
           X = X_Old + X;
           Y = foot[1] - Yb + Y;
           if(Inv == 1)
               X = -X;
           
           if(Right == 1)
               Y = -Y;
           
           double Z = foot[2];
           double T0 = Math.atan(Y/Z);
           double T2 = Util.Theta2(X, Z, T0);
           double T1 = Util.Theta1(X, Z, T0, T2);
           Theta[0] = T0;
           Theta[1] = T1;
           Theta[2] = T2;
           foot = Link3();
       }
       //Third Link
       private double[] Link3()
       {
           double L0 = Len[0];
           double L1 = Len[1];
           double L2 = Len[2];
           double L3 = Len[3];
           double T0,T1,T2;
           if(Right == 1)
               T0 = Theta[0];  //The Leg on the right side
           else
               T0 = Theta[0]; //the Leg on the left side
           
           if(Inv == -1)       //If the robot isn't flipped
           {
               T1 = Theta[1];
               T2 = Theta[2];
           }
           else
           {
               T1 = -Theta[1];
               T2 = -Theta[2];
           }
           
           //Leg Kinematics
           double X = L1*Math.sin(Util.toRad(T1)) + L2*Math.sin(Util.toRad(T1-T2)) + Xb;
           double Temp = L0 + L1*Math.cos(Util.toRad(T1)) + L2*Math.cos(Util.toRad(T1-T2)) + L3;
           double Y = -Math.sin(Util.toRad(T0))*(Temp) + Yb;
           double Z = -Math.cos(Util.toRad(T0))*(Temp);

           double[] p = new double[3];
           p[0] = X;
           p[1] = Y;
           p[2] = Z;
           
           return p;
       }
}
