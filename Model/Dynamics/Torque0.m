function [ Torque ] = Torque0( Theta, Angular_V, Angular_A )

%Mass of the Links
m0 = 1;
m1 = 1;
m2 = 1;

%Inertia
I0xx = 1;
I1xz = 1;
I2xz = 1;

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
T0_doubledot = Angular_A(1)*pi/180;

%Precomputed Variables
C1 = cosd(T1);
S1 = sind(T1);
S0 = sind(T0);
d_C0 = cosd(2*T0);
d_S0 = sind(2*T0);
C12 = cosd(T1-T2);
S12 = sind(T1-T2);

%the Term of T1 double dot
Torque = T0_doubledot*(2*m0*((L0/2)^2) + m1*(L0^2) + m1*L0*L1*C1 + m1*((L1/2)^2)*(C1^2) ...
                + m2*(L0^2)*d_C0 + 2*m2*L0*L1*C1*d_C0 - m2*(L1^2)*(C1^2)*d_C0 ...
                - m2*L1*L2*C1*C12*d_C0 - m2*((L2/2)^2)*C12*d_C0 + I0xx + I1xz + I2xz);

%the Term of T0_dot * T1_dot
Torque = Torque + T0_dot*T1_dot*(-m1*L0*L1*S1 - 0.5*m1*(L1^2)*C1*S1 - 2*m2*L0*L1*S1*d_C0 ...
                + 2*m2*(L1^2)*C1*S1*d_C0 + m2*L0*L2*d_C0*S12 + m2*L1*L2*S1*C12*d_C0 ...
                + m2*L1*L2*C1*S12*d_C0 + m2*((L2/2)^2)*S12*d_C0);

%the Term of T0_dot * T2_dot
Torque = Torque + T0_dot*T2_dot*(-m2*L0*L2*d_C0*S12 - m2*L1*L2*C1*S12*d_C0 ...
                - m2*((L2/2)^2)*S12*d_C0);

%the Term of T0_dot^2
Torque = Torque + (T0_dot^2)*(m2*(L0^2)*d_S0 - 2*m2*L0*L1*C1*d_S0 + m2*(L1^2)*(C1^2)*d_S0 ...
                + m2*L0*L2*d_S0*C12 + m2*L1*L2*C1*C12*d_S0 + m2*((L2/2)^2)*C12*d_S0);

%the Term of g
Torque = Torque + g*(m0*S0*(L0/2) + m1*S0*(L0 + (L1/2)*C1) + m2*S0(L0 + L1*C1 + L2*C12/2));

end
