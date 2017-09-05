function [ T ] = Theta1( X, Z, T0, fmove, fore, T_Old )

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

if(fmove == -1)
    %Moving backward
    if(fore == 1)
        %Forward Leg
        if(T1_pp >= -50 && T1_pp <= 90 && T1_pp >= T_Old)
            T = T1_pp;
        elseif(T1_np >= -50 && T1_np <= 90 && T1_np >= T_Old)
            T = T1_np;
        elseif(T1_pn >= -50 && T1_pn <= 90 && T1_pn >= T_Old)
            %Forward Leg
            T = T1_pn;
        else
            T = T1_nn;
        end
    else
        %Backward Leg %nn, pn, pp, np
        if(T1_nn >= -50 && T1_nn <= 90 && T1_nn <= T_Old)
            T = T1_nn;
        elseif(T1_pn >= -50 && T1_pn <= 90 && T1_pn <= T_Old)
            T = T1_pn;
        elseif(T1_pp >= -50 && T1_pp <= 90 && T1_pp <= T_Old)
            T = T1_pp;
        else
            T = T1_np;
        end
    end
else
    %Moving forward
    if(fore == 1)
        %Forward Leg %pp, np, pn, nn
        if(T1_pp >= -50 && T1_pp <= 90 && T1_pp <= T_Old)
            T = T1_pp;
        elseif(T1_np >= -50 && T1_np <= 90 && T1_np <= T_Old)
            T = T1_np;
        elseif(T1_pn >= -50 && T1_pn <= 90 && T1_pn <= T_Old)
            T = T1_pn;
        else
            T = T1_nn;
        end
    else
        %Backward Leg %pp, np, pn, nn
        if(T1_pp >= -50 && T1_pp <= 90 && T1_pp >= T_Old)
            T = T1_pp;
        elseif(T1_np >= -50 && T1_np <= 90 && T1_np >= T_Old)
            T = T1_np;
        elseif(T1_pn >= -50 && T1_pn <= 90 && T1_pn >= T_Old)
            T = T1_pn;
        else
            T = T1_nn;
        end
    end
end

end
