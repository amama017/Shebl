function [ T ] = Theta1( X, Z, T0, T2 )

%Leg dimentions
L0 = 8;
L1 = 10.5;
L2 = 13.1;
L3 = 1.8;

Z_dash = -Z/cosd(T0) - L0 - L3;

P = (X^2) + (Z_dash^2) + (L1^2) - (L2^2);
R = 2*X*L1;
Q = 2*Z_dash*L1;

a = 2*P*Q;
b = (P^2) - (R^2);
c = 2*((R^2) + (Q^2));

C1_p = (a + sqrt((a^2) - 2*b*c))/c;
C1_n = (a - sqrt((a^2) - 2*b*c))/c;

S1_pp = sqrt(1 - (C1_p^2));
S1_pn = -sqrt(1 - (C1_p^2));
S1_np = sqrt(1 - (C1_n^2));
S1_nn = -sqrt(1 - (C1_n^2));

T1_pp = atan2(S1_pp, C1_p)*180/pi;
T1_pn = atan2(S1_pn, C1_p)*180/pi;
T1_np = atan2(S1_np, C1_n)*180/pi;
T1_nn = atan2(S1_nn, C1_n)*180/pi;

P_pp = EndEffector([T0, T1_pp, T2]);
P_pp = abs([P_pp(1), P_pp(3)] - [X, Z]);

P_pn = EndEffector([T0, T1_pn, T2]);
P_pn = abs([P_pn(1), P_pn(3)] - [X, Z]);

P_np = EndEffector([T0, T1_np, T2]);
P_np = abs([P_np(1), P_np(3)] - [X, Z]);
%P_nn = EndEffector([T0, T1_nn, T2]);

if(P_pp(1) < 1e-10 && P_pp(2) < 1e-10)
    T = T1_pp;
elseif(P_pn(1) < 1e-10 && P_pn(2) < 1e-10)
    T = T1_pn;
elseif(P_np(1) < 1e-10 && P_np(2) < 1e-10)
    T = T1_np;
else
    T = T1_nn;
end

end
