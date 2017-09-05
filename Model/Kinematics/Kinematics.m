function [ Velocity ] = Kinematics( Theta, Angular_V )
%Compute the Jacobian Matrix for the Leg Then computes the Kinematics of the leg
%the velocity of the foot according to the current Angle and Angular Velocity (in degree)

%Leg dimentions
L0 = 8;
L1 = 10.5;
L2 = 13.1;
L3 = 1.8;

%Current Joints Angles
T0 = Theta(1);
T1 = Theta(2);
T2 = Theta(3);

%Convert Current Angular Velocities to Radian
T0_dot = Angular_V(1)*pi/180;
T1_dot = Angular_V(2)*pi/180;
T2_dot = Angular_V(3)*pi/180;

%Precomputed variables
S0 = sind(T0);
C0 = cosd(T0);

S1 = L1*sind(T1);
C1 = L1*cosd(T1);

S2 = L2*sind(T1-T2);
C2 = L2*cosd(T1-T2);

%Jacobian Matrix
J = [0,              C1+C2,      -C2;
    -C0*(L0+C1+C2+L3),  S0*(S1+S2), -S0*S2;
    S0*(L0+C1+C2+L3),   C0*(S1+S2), -C0*S2];

%Result the Kinematics X_dot = J x Theta_dot
Velocity = J * [T0_dot; T1_dot; T2_dot];
end
