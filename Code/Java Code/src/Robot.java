package gp;

/**
 *
 * @author Abdelrahman
 */
public class Robot {
    
       double L = 30;          //Length of Robot
       double W = 30;          //Width of Robot
       Leg L1, L2, L3, L4;  //Robot's Legs
       double Ts = 1;          //Total Swing Time
       
       //Constructor
       public Robot(double l,double w)
       {
           L = l;
           W = w;
           
           L1 = new Leg(1,L,W,-1,1);  //Backward Right Leg
           L2 = new Leg(2,L,W,1,1);  //Forward Right Leg
           L3 = new Leg(3,L,W,-1,-1); //Backward Left Leg
           L4 = new Leg(4,L,W,1,-1);  //Forward Left Leg
       }
       
       //Update the Leg Orientation
       public void Update(double ID, double T0, double T1, double T2)
       {
           if(ID == 1)
               L1.Update(T0, T1, T2);
           else if(ID == 2)
               L2.Update(T0, T1, T2);
           else if(ID == 3)
               L3.Update(T0, T1, T2);
           else
               L4.Update(T0, T1, T2);
        }
       
       public void Move_COM(double ID)
       {
           if(ID == 1)
           {
               //Backward Right Leg
               //Move COM to the Median of (FL, FR, BL)
               double X1 = L4.foot[0];
               double Y1 = L4.foot[1];
               
               double X2 = L2.foot[0];
               double Y2 = L2.foot[1];
               
               double X3 = L3.foot[0];
               double Y3 = L3.foot[1];
               
               double a = (X2 + X1 - 2*X3)/(Y2 + Y1 - 2*Y3);
               double b = (X3 + X1 - 2*X2)/(Y3 + Y1 - 2*Y2);
               
               //Get the New COM
               double Y = (Y2*b - Y3*a + X3 - X2)/(b - a);
               double X = X2 + (Y - Y2)*b;
               
               //Get the Transformation of the legs
               Update_Legs(ID, X, Y);
           }   
           else if(ID == 2)
           {
               //Forward Right Leg
               //Move COM to the Edge of BR & FL
               double X1 = L1.foot[0];
               double Y1 = L1.foot[1];
               
               double X2 = L4.foot[0];
               double Y2 = L4.foot[1];
               
               //Get the New COM [Old COM is (0,0)]
               double Y = 0;
               double X = X1 + (Y - Y1)*((X1-X2)/(Y1-Y2));
               
               //Get the Transformation of the legs
               Update_Legs(ID, X, Y);
           }
           else if(ID == 3)
           {
               //Backward Left Leg
               //Move COM to the Median of (FL, FR, BR)
               double X1 = L4.foot[0];
               double Y1 = L4.foot[1];
               
               double X2 = L2.foot[0];
               double Y2 = L2.foot[1];
               
               double X3 = L1.foot[0];
               double Y3 = L1.foot[1];
               
               double a = (X2 + X1 - 2*X3)/(Y2 + Y1 - 2*Y3);
               double b = (X3 + X1 - 2*X2)/(Y3 + Y1 - 2*Y2);
               
               //Get the New COM
               double Y = (Y2*b - Y3*a + X3 - X2)/(b - a);
               double X = X2 + (Y - Y2)*b;
               
               //Get the Transformation of the legs
               Update_Legs(ID, X, Y);
           }   
           else
           {
               //Forward Left Leg
               //Move COM to the Edge of BL & FR
               double X1 = L3.foot[0];
               double Y1 = L3.foot[1];
               
               double X2 = L2.foot[0];
               double Y2 = L2.foot[1];
               
               //Get the New COM [Old COM is (0,0)]
               double Y = 0;
               double X = X1 + (Y - Y1)*((X1-X2)/(Y1-Y2));
               
               //Get the Transformation of the legs
               Update_Legs(ID, X, Y);
           }
        }
       
    public void Update_Legs(double ID, double X, double Y)
    {
        if(ID == 1)
        {
            L2.Move_Disp(-X, -Y);
            L3.Move_Disp(-X, -Y);
            L4.Move_Disp(-X, -Y);
        }
        else if(ID == 2)
        {
            L1.Move_Disp(-X, -Y);
            L3.Move_Disp(-X, -Y);
            L4.Move_Disp(-X, -Y);
        }
        else if(ID == 3)
        {
            L1.Move_Disp(-X, -Y);
            L2.Move_Disp(-X, -Y);
            L4.Move_Disp(-X, -Y);
        }
        else
        {
            L1.Move_Disp(-X, -Y);
            L2.Move_Disp(-X, -Y);
            L3.Move_Disp(-X, -Y);
        }
    }
}
