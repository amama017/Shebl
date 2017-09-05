function [ Torque ] = Torque1( Theta, Angular_V, Angular_A )

%Mass of the Links
m1 = 1;
m2 = 1;

%Inertia
I1zz = 1;
I2zz = 1;

%Leg dimentions
L0 = 1;
L1 = 10;
L2 = 10;

%Current Joints Angles
T0 = Theta(1);
T1 = Theta(2);
T2 = Theta(3);

%Convert Current Angular Velocities to Radian
T0_dot = Angular_V(1)*pi/180;
T1_dot = Angular_V(2)*pi/180;
T2_dot = Angular_V(3)*pi/180;

%Convert Current Angular Acceleration to Radian
T1_doubledot = Angular_A(2)*pi/180;
T2_doubledot = Angular_A(3)*pi/180;

%Precomputed Variables
S1 = sind(T1);
C1 = cosd(T1);
S2 = sind(T2);
C2 = cosd(T2);
C0 = cosd(T0);
d_C0 = cosd(2*T0);
S12 = sind(T1-T2);
C12 = cosd(T1-T2);
L2_m = L2/2;
L1_m = L1/2;

%the Term of T1 double dot
Torque = T1_doubledot*(m1*(L1_m^2) + m2*(L1^2) + m2*(L2_m^2) + 2*m2*L1*L2_m*C2 + I1zz + I2zz);

%the Term of T2 double dot
Torque = Torque + T2_doubledot*(-m2*(L2_m^2) - m2*L1*L2_m*C2 - I2zz);

%the Term of T1_dot * T2_dot
Torque = Torque + T1_dot*T2_dot*(-2*m2*L1*L2_m*S2);

%the Term of T2_dot^2
Torque = Torque + (T2_dot^2)*(m2*L1*L2_m*S2);

%the Term of T0_dot^2
Torque = Torque + (T0_dot^2)*(m1*L0*L2_m*S1 + m1*(L1_m^2) ...
                + m2*L0*L1*S1*d_C0 - m2*(L1^2)*C1*S1*d_C0 ...
                - m2*L0*L2_m*d_C0*S12 - m2*L1*L2_m*S1*C12*d_C0 ...
                - m2*L1*L2_m*C1*S12*d_C0 - 0.5*m2*(L2_m^2)*S12*d_C0);

%the Term of g
Torque = Torque + g*(m1*L1_m*S1*C0 + m2*L1*S1*C0 * m2*L2_m*S12*C0);

end
