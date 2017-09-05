function [ Angular_V ] = InvKinematics( Theta, Velocity )
%Compute the Jacobian Matrix for the Leg Then computes the Inverse Kinematics of the leg
%the Angular Velocity of the foot according to the current Angle and the Velocity of the foot (in degree)

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
V0 = Velocity(1);
V1 = Velocity(2);
V2 = Velocity(3);

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

%Result the Inverse Kinematics Theta_dot = J x X_dot
Angular_V = inv(J) * [V0; V1; V2];

%Convert Current Angular Velocities to Radian
Angular_V(1) = Angular_V(1)*180/pi;
Angular_V(2) = Angular_V(2)*180/pi;
Angular_V(3) = Angular_V(3)*180/pi;

end
