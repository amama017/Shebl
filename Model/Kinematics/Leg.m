classdef Leg
%Class 

   properties
       ID = -1;             %Leg Number, -1 not initialized
       Xb = 0;              %The Distance from Origin on the X axis
       Yb = 0;              %The Distance form Origin on the Y axis
       Inv = -1;            %Is the Leg flipped (Is it Forward Leg)
       Right = 1;           %Is the Leg on the right side of the robot
       Theta = [0, 45, 90]; %The Joint's Angles
       Len = [8, 10.5, 13.1, 1.8];%Leg Dimentions
       foot;                %The Foot Point
       Tup = 0.25;          %Time of rising the leg
       Tdown = 0.25;        %Time of downing the leg
       Tdisp = 0.5;         %Time of moving the leg
       disp = 4;            %The displacement distance
       h = 4;               %The displacement distance
   end

   methods
       %Constructor
       function L = Leg(id, xb, yb, inv, r)
           L.ID = id;
           if(inv == 1)
               L.Xb = xb;
           else
               L.Xb = -xb;
           end
           if(r == 1)
               L.Yb = -yb;
           else
               L.Yb = yb;
           end
           L.Inv = inv;
           L.Right = r;
           L.foot = L.Link3();
       end
       
       %Update Leg
       function L = Update(L, T0, T1, T2)
           L.Theta = [T0, T1, T2];
           L.foot = L.Link3();
       end
       
       %Move Leg
       function L = Move(L)
           %Get the Velocity of rising the Leg in Z axis
           %Vup = L.h/L.Tup;
           X = L.foot(1) - L.Xb;
           Z = L.foot(3) + L.h;
           if(L.Inv == 1)
               X = -X;
           end
           T2 = Theta2(X, Z, L.Theta(1));
           T1 = Theta1(X, Z, L.Theta(1), T2);
           L.Theta = [L.Theta(1), T1, T2];
           L.foot = L.Link3();
           
           %Get the Velocity of moving the Leg forward in x axis
           %Vdisp = L.disp/L.Tdisp;
           X = L.foot(1) - L.Xb;
           Z = L.foot(3);
           X = X + L.disp;
           if(L.Inv == 1)
               X = -X;
           end
           T2 = Theta2(X, Z, L.Theta(1));
           T1 = Theta1(X, Z, L.Theta(1), T2);
           L.Theta = [L.Theta(1), T1, T2];
           L.foot = L.Link3();
           
           %Get the Velocity of downing the Leg in z axis
           %Vdown = -L.h/L.Tdown;
           X = L.foot(1) - L.Xb;
           Z = L.foot(3) - L.h;
           if(L.Inv == 1)
               X = -X;
           end
           T2 = Theta2(X, Z, L.Theta(1));
           T1 = Theta1(X, Z, L.Theta(1), T2);
           L.Theta = [L.Theta(1), T1, T2];
           L.foot = L.Link3();
       end
       
       function L = Move_Disp(L, X, Y)
           if(X == 0 && Y == 0)
               return;
           end
           %Get the Req angles to set the foot at (X, Y) from COM
           X_Old = L.foot(1) - L.Xb;
           X = X_Old + X;
           Y = L.foot(2) - L.Yb + Y;
           if(L.Inv == 1)
               X = -X;
           end
           if(L.Right == 1)
               Y = -Y;
           end
           Z = L.foot(3);
           T0 = atan(Y/Z);
           T2 = Theta2(X, Z, T0);
           T1 = Theta1(X, Z, T0, T2);
           L.Theta = [T0, T1, T2];
           L.foot = L.Link3();
       end
       
       %First Link
       function p = Link0(L)
           p(1) = L.Xb;         %X
           p(2) = L.Yb;         %Y
           p(3) = -L.Len(1);    %Z
       end
       
       %First Link
       function p = Link1(L)
           %Temp Variables
           L0 = L.Len(1);
           L1 = L.Len(2);
           if(L.Right == 1)
               T0 = L.Theta(1);  %The Leg on the right side
           else
               T0 = -L.Theta(1); %the Leg on the left side
           end
           if(L.Inv == -1)       %If the robot isn't flipped
               T1 = L.Theta(2);
           else
               T1 = -L.Theta(2);
           end
           
           %Leg Kinematics
           X = L1*sind(T1) + L.Xb;
           Temp = L0 + L1*cosd(T1);
           Y = -sind(T0)*(Temp) + L.Yb;
           Z = -cosd(T0)*(Temp);
           p = [X, Y, Z];
       end
       
       %Second Link
       function p = Link2(L)
           %Temp Variables
           L0 = L.Len(1);
           L1 = L.Len(2);
           L2 = L.Len(3);
           if(L.Right == 1)
               T0 = L.Theta(1);  %The Leg on the right side
           else
               T0 = -L.Theta(1); %the Leg on the left side
           end
           if(L.Inv == -1)       %If the robot isn't flipped
               T1 = L.Theta(2);
               T2 = L.Theta(3);
           else
               T1 = -L.Theta(2);
               T2 = -L.Theta(3);
           end
           
           %Leg Kinematics
           X = L1*sind(T1) + L2*sind(T1-T2) + L.Xb;
           Temp = L0 + L1*cosd(T1) + L2*cosd(T1-T2);
           Y = -sind(T0)*(Temp) + L.Yb;
           Z = -cosd(T0)*(Temp);
           p = [X, Y, Z];
       end
       
       %Third Link
       function p = Link3(L)
           %Temp Variables
           L0 = L.Len(1);
           L1 = L.Len(2);
           L2 = L.Len(3);
           L3 = L.Len(4);
           if(L.Right == 1)
               T0 = L.Theta(1);  %The Leg on the right side
           else
               T0 = -L.Theta(1); %the Leg on the left side
           end
           if(L.Inv == -1)       %If the robot isn't flipped
               T1 = L.Theta(2);
               T2 = L.Theta(3);
           else
               T1 = -L.Theta(2);
               T2 = -L.Theta(3);
           end
           
           %Leg Kinematics
           X = L1*sind(T1) + L2*sind(T1-T2) + L.Xb;
           Temp = L0 + L1*cosd(T1) + L2*cosd(T1-T2) + L3;
           Y = -sind(T0)*(Temp) + L.Yb;
           Z = -cosd(T0)*(Temp);
           p = [X, Y, Z];
       end
       
       %Draw The Leg
       function Draw(L)
           P0 = L.Link0();
           P1 = L.Link1();
           P2 = L.Link2();
           P3 = L.Link3();
           hold all;
           line('XData',[L.Xb,P0(1)], 'YData',[L.Yb,P0(2)], 'ZData',[0,P0(3)]);
           line('XData',[P0(1),P1(1)], 'YData',[P0(2),P1(2)], 'ZData',[P0(3),P1(3)]);
           line('XData',[P1(1),P2(1)], 'YData',[P1(2),P2(2)], 'ZData',[P1(3),P2(3)]);
           line('XData',[P2(1),P3(1)], 'YData',[P2(2),P3(2)], 'ZData',[P2(3),P3(3)]);
       end
   end
end 
