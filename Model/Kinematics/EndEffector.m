function [ Point ] = EndEffector( Theta )
%Compute the place of the Leg's foot from the Joint Angles (in degrees)
%and plot the resulted orientation of the leg

%Leg dimentions
L0 = 8;
L1 = 10.5;
L2 = 13.1;
L3 = 1.8;

%Current Joint Angles
T0 = Theta(1);
T1 = Theta(2);
T2 = Theta(3);

% %The Point of Link0
% X0 = 0; Y0 = 0; Z0 = -L0;
% 
% %Plot Link0
% hold all;
% line('XData',[0,X0], 'YData',[0,Y0], 'ZData',[0,Z0]);
% 
% %Precompute S0 &C0
% S0 = sind(T0);
% C0 = cosd(T0);
% 
% %The Point of Link1
% X1 = L1*sind(T1);
% Temp1 = L0 + L1*cosd(T1);
% Y1 = -S0*(Temp1);
% Z1 = -C0*(Temp1);
% 
% %Plot Link1
% line('XData',[X0,X1], 'YData',[Y0,Y1], 'ZData',[Z0,Z1]);
% 
% %The Point of Link2
% X2 = L2*sind(T1-T2) + X1;
% Temp2 = L2*cosd(T1-T2);
% Y2 = -S0*(Temp2) + Y1;
% Z2 = -C0*(Temp2) + Z1;
% 
% %Plot Link2
% line('XData',[X1,X2], 'YData',[Y1,Y2], 'ZData',[Z1,Z2]);

%End-Effector (foot) Link3
X = L1*sind(T1) + L2*sind(T1-T2);
Y = -sind(T0)*(L0 + L1*cosd(T1) + L2*cosd(T1-T2) + L3);
Z = -cosd(T0)*(L0 + L1*cosd(T1) + L2*cosd(T1-T2) + L3);

% %Plot Link3
% line('XData',[X2,X], 'YData',[Y2,Y], 'ZData',[Z2,Z]);

%Result
Point = [X, Y, Z];
end
