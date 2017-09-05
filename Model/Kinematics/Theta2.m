function [ T ] = Theta2( X, Z, T0 )

%Leg dimentions
L0 = 8;
L1 = 10.5;
L2 = 13.1;
L3 = 1.8;

Z_dash = -Z/cosd(T0) - L0 - L3;

C2 = ((X^2) + (Z_dash^2) - (L1^2) - (L2^2)) / (2*L1*L2);

S2 = sqrt(1 - (C2^2));

T2 = atan2(S2,C2)*180/pi;
T2_2 = atan2(-S2,C2)*180/pi;

if(T2 >= 20 && T2 <= 140)
    T = T2;
else
    T = T2_2;
end

end
