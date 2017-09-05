classdef Robot
%ROBOT Summary of this class goes here
%   Detailed explanation goes here

   properties
       L = 37;          %Length of Robot
       W = 37;          %Width of Robot
       L1, L2, L3, L4;  %Robot's Legs
       Ts = 1;          %Total Swing Time
   end

   methods
       %Constructor
       function R = Robot(l,w)
           if nargin > 0
               R.L = l;
               R.W = w;
           end
           R.L1 = Leg(1,R.L,R.W,-1,1);  %Backward Right Leg
           R.L2 = Leg(2,R.L,R.W,1,1);   %Forward Right Leg
           R.L3 = Leg(3,R.L,R.W,-1,-1); %Backward Left Leg
           R.L4 = Leg(4,R.L,R.W,1,-1);  %Forward Left Leg
       end
       
       %Update the Leg Orientation
       function R = Update(R, ID, T0, T1, T2)
           if(ID == 1)
               R.L1 = R.L1.Update(T0, T1, T2);
           elseif(ID == 2)
               R.L1 = R.L2.Update(T0, T1, T2);
           elseif(ID == 3)
               R.L1 = R.L3.Update(T0, T1, T2);
           else
               R.L1 = R.L4.Update(T0, T1, T2);
           end
       end
       
       function R = Move(R, ID)
           if(ID == 1)
               R.L1 = R.L1.Move();
               R = R.Move_COM(ID);
           elseif(ID == 2)
               R.L2 = R.L2.Move();
               R = R.Move_COM(ID);
           elseif(ID == 3)
               R.L3 = R.L3.Move();
               R = R.Move_COM(ID);
           else
               R.L4 = R.L4.Move();
               R = R.Move_COM(ID);
           end
       end
       
       function R = Update_Legs(R, ID, X, Y)
           if(ID == 1)
               R.L2 = R.L2.Move_Disp(-X, -Y);
               R.L3 = R.L3.Move_Disp(-X, -Y);
               R.L4 = R.L4.Move_Disp(-X, -Y);
           elseif(ID == 2)
               R.L1 = R.L1.Move_Disp(-X, -Y);
               R.L3 = R.L3.Move_Disp(-X, -Y);
               R.L4 = R.L4.Move_Disp(-X, -Y);
           elseif(ID == 3)
               R.L1 = R.L1.Move_Disp(-X, -Y);
               R.L2 = R.L2.Move_Disp(-X, -Y);
               R.L4 = R.L4.Move_Disp(-X, -Y);
           else
               R.L1 = R.L1.Move_Disp(-X, -Y);
               R.L2 = R.L2.Move_Disp(-X, -Y);
               R.L3 = R.L3.Move_Disp(-X, -Y);
           end
       end
       
       function R = Move_COM(R, ID)
           if(ID == 1)
               %Backward Right Leg
               %Move COM to the Median of (FL, FR, BL)
               X1 = R.L4.foot(1);
               Y1 = R.L4.foot(2);
               
               X2 = R.L2.foot(1);
               Y2 = R.L2.foot(2);
               
               X3 = R.L3.foot(1);
               Y3 = R.L3.foot(2);
               
               a = (X2 + X1 - 2*X3)/(Y2 + Y1 - 2*Y3);
               b = (X3 + X1 - 2*X2)/(Y3 + Y1 - 2*Y2);
               
               %Get the New COM
               Y = (Y2*b - Y3*a + X3 - X2)/(b - a);
               X = X2 + (Y - Y2)*b;
               
               %Get the Transformation of the legs
               R = R.Update_Legs(ID, X, Y);
               
           elseif(ID == 2)
               %Forward Right Leg
               %Move COM to the Edge of BR & FL
               X1 = R.L1.foot(1);
               Y1 = R.L1.foot(2);
               
               X2 = R.L4.foot(1);
               Y2 = R.L4.foot(2);
               
               %Get the New COM [Old COM is (0,0)]
               Y = 0;
               X = X1 + (Y - Y1)*((X1-X2)/(Y1-Y2));
               
               %Get the Transformation of the legs
               R = R.Update_Legs(ID, X, Y);
               
           elseif(ID == 3)
               %Backward Left Leg
               %Move COM to the Median of (FL, FR, BR)
               X1 = R.L4.foot(1);
               Y1 = R.L4.foot(2);
               
               X2 = R.L2.foot(1);
               Y2 = R.L2.foot(2);
               
               X3 = R.L1.foot(1);
               Y3 = R.L1.foot(2);
               
               a = (X2 + X1 - 2*X3)/(Y2 + Y1 - 2*Y3);
               b = (X3 + X1 - 2*X2)/(Y3 + Y1 - 2*Y2);
               
               %Get the New COM
               Y = (Y2*b - Y3*a + X3 - X2)/(b - a);
               X = X2 + (Y - Y2)*b;
               
               %Get the Transformation of the legs
               R = R.Update_Legs(ID, X, Y);
               
           else
               %Forward Left Leg
               %Move COM to the Edge of BL & FR
               X1 = R.L3.foot(1);
               Y1 = R.L3.foot(2);
               
               X2 = R.L2.foot(1);
               Y2 = R.L2.foot(2);
               
               %Get the New COM [Old COM is (0,0)]
               Y = 0;
               X = X1 + (Y - Y1)*((X1-X2)/(Y1-Y2));
               
               %Get the Transformation of the legs
               R = R.Update_Legs(ID, X, Y);
           end
       end
       
       %Draw the Robot
       function Draw(R)
           line('XData',[R.L,R.L,-R.L,-R.L,R.L], 'YData',[R.W,-R.W,-R.W,R.W,R.W], 'ZData',[0,0,0,0,0]);
           R.L1.Draw();
           R.L2.Draw();
           R.L3.Draw();
           R.L4.Draw();
       end
   end
end 
