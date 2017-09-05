package gp;

/**
 *
 * @author Abdelrahman
 */
public class Util {
    
    //Leg dimensions
    public static double L0 = 8;
    public static double L1 = 10.5;
    public static double L2 = 13.1;
    public static double L3 = 1.8;
    
    public static double Theta1(double X, double Z, double T0, double T2)
    {
        
        double Z_dash = -Z/Math.cos(toRad(T0)) - L0 - L3;
        double P = (Math.pow(X, 2)) + (Math.pow(Z_dash, 2)) + (Math.pow(L1, 2)) - (Math.pow(L2, 2));
        double R = 2*X*L1;
        double Q = 2*Z_dash*L1;
        
        double a = 2 * P * Q;
        double b = (Math.pow(P, 2)) - (Math.pow(R, 2));
        double c = 2 * ((Math.pow(R, 2)) + (Math.pow(Q, 2)));

        double C1_p = (a + Math.sqrt((Math.pow(a, 2)) - 2 * b * c)) / c;
        double C1_n = (a - Math.sqrt((Math.pow(a, 2)) - 2 * b * c)) / c;

        double S1_pp = Math.sqrt(1 - (Math.pow(C1_p, 2)));
        double S1_pn = -Math.sqrt(1 - (Math.pow(C1_p, 2)));
        double S1_np = Math.sqrt(1 - (Math.pow(C1_n, 2)));
        double S1_nn = -Math.sqrt(1 - (Math.pow(C1_n, 2)));

        double T1_pp = Math.atan2(S1_pp, C1_p) * 180 / Math.PI;     //return array or double?
        double T1_pn = Math.atan2(S1_pn, C1_p) * 180 / Math.PI;
        double T1_np = Math.atan2(S1_np, C1_n) * 180 / Math.PI;
        double T1_nn = Math.atan2(S1_nn, C1_n) * 180 / Math.PI;

//        double[] P_pp = new double[3];
//        double[] P_pn = new double[3];
//        double[] P_np = new double[3];
        
        double[] P_pp = EndEffector(T0, T1_pp, T2);
        P_pp[0] = Math.abs(P_pp[0] - X);
        P_pp[2] = Math.abs(P_pp[2] - Z);
        
        double[] P_pn = EndEffector(T0, T1_pn, T2);
        P_pn[0] = Math.abs(P_pn[0] - X);
        P_pn[2] = Math.abs(P_pn[2] - Z);
        
        double[] P_np = EndEffector(T0, T1_np, T2);
        P_np[0] = Math.abs(P_np[0] - X);
        P_np[2] = Math.abs(P_np[2] - Z);
        //% P_nn = EndEffector([T0, T1_nn, T2]);
        
        double T;
        if(P_pp[0] < (1 * Math.pow(10, -10)) && P_pp[2] < (1 * Math.pow(10, -10)))      //1e-10
            T = T1_pp;
        else if(P_pn[0] < (1 * Math.pow(10, -10)) && P_pn[2] < (1 * Math.pow(10, -10)))
            T = T1_pn;
        else if(P_np[0] < (1 * Math.pow(10, -10)) && P_np[2] < (1 * Math.pow(10, -10)))
            T = T1_np;
        else
            T = T1_nn;
        
        return T;
    }
    
    public static double Theta2(double X, double Z, double T0)
    {
        double Z_dash = -Z / Math.cos(toRad(T0)) - L0 - L3;
        
        double C2 = ((Math.pow(X, 2)) + (Math.pow(Z_dash, 2)) - (Math.pow(L1, 2)) - (Math.pow(L2, 2))) / (2 * L1 * L2);
        
        double S2 = Math.sqrt(1 - (Math.pow(C2, 2)));
        
        double T2 = Math.atan2(S2, C2) * 180 / Math.PI;
        double T2_2 = Math.atan2(-S2, C2) * 180 / Math.PI;
        
        double T;
        if (T2 >= 20 && T2 <= 140)
            T = T2;
        else
            T = T2_2;
        
        return T;
    }
    
    public static double[] EndEffector(double T0, double T1, double T2)
    {
        double[] p = new double[3];
         p[0] = L1 * Math.sin(toRad(T1)) + L2 * Math.sin(toRad(T1 - T2));
         p[1] = -Math.sin(toRad(T0)) * (L0 + L1 * Math.cos(toRad(T1)) + L2 * Math.cos(toRad(T1 - T2)) + L3);
         p[2] = -Math.cos(toRad(T0)) * (L0 + L1 * Math.cos(toRad(T1)) + L2 * Math.cos(toRad(T1 - T2)) + L3);

         return p;
    }
    
    
    
    public static double toRad(double d)
    {
        return d * Math.PI / 180;
    }
}
