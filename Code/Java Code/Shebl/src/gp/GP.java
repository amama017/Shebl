package gp;

/**
 *
 * @author Ayman
 */
public class GP {

	private static SheblSerial SS;
	private static boolean pause;
	private static boolean reset;
    private static void Send_Angles(int leg, double[] Angles) {
        //Convert the Angles to Int
        int[] Angles_int = new int[12];
        for(int i=0; i<12; i++){
            Angles_int[i] = (int) Math.round((Angles[i]/2)+25);
        }
        //Send the Array of angles to the Controller
        //Send the Leg to Swing
        //Send the Angles of the Leg to Swing
        //Send the Support Legs Angles
        System.out.println("Send Data");
        SS.send(leg,Angles_int);
        if(getreset())
		{
			return;
		}
        System.out.println("Data Sent");
    }

    public enum FSM { Selection, Shift_Quad, Swing };
    
	public static void reset()
	{
		reset = true;
	}
	
	public static void pause()
	{
		pause = true;
	}
	
	public static void resume()
	{
		pause = false;
	}
	
	public static boolean getpause()
	{
		return pause;
	}
	
	public static boolean getreset()
	{
		return reset;
	}
	
	
    public static void run() {
        //FSM Parameters
        FSM CS, NS;
        //Initial State
        CS = FSM.Selection;
        NS = FSM.Swing;
        
        //Robot State
        Robot rob = new Robot(30, 30);
        
        //Angles to be sent to the controller
        double[] Angles = new double[12];
        //First 6 Angles for the Swing Leg
        //Rest 6 for the Support Leg
        
        //Which Leg to be swing
        int Leg_no = 0;
        //Leg Sequence
        //L1 => Back Right
        //L2 => Front Right
        //L3 => Back Left
        //L4 => Front Left
        
        SS = new SheblSerial();
        SS.Init();
        pause = false;
		
        while(true){
			if(pause)
				continue;
            if (CS == FSM.Selection) {
                //Selection Operation
                switch(Leg_no){
                    case 1:
                        Leg_no = 2;
                        break;
                    case 2:
                        Leg_no = 0;
                    	//Leg_no = 4;
                        break;
                    case 3:
                        Leg_no = 1;
                        break;
                    case 4:
                        Leg_no = 3;
                        break;
                    default:
                        Leg_no = 4;
                }
                
                //Go to the Next State
                if(Leg_no == 0){
                    CS = FSM.Shift_Quad;
                    NS = FSM.Selection;
                } else {
                    CS = NS;
                    NS = FSM.Selection;
                }
            } else if (CS == FSM.Swing) {
                //Swing Operation
                switch(Leg_no){
                    case 1:
                        //Move Leg1
                        rob.L1.Move();
                        //Shift COM
                        rob.Move_COM(Leg_no);
                        //Send Angles
                            //Swing Angles (L1)
                        System.arraycopy(rob.L1.Swing_Theta, 0, Angles, 0, 6);
                            //Support Angles (L2,L3,L4)
                        Angles[6] = rob.L2.Theta[1];
                        Angles[7] = rob.L2.Theta[2];
                        Angles[8] = rob.L3.Theta[1];
                        Angles[9] = rob.L3.Theta[2];
                        Angles[10] = rob.L4.Theta[1];
                        Angles[11] = rob.L4.Theta[2];
                        Send_Angles(Leg_no, Angles);
                        break;
                    case 2:
                        //Move Leg2
                        rob.L2.Move();
                        //Shift COM
                        rob.Move_COM(Leg_no);
                        //Send Angles
                            //Swing Angles (L2)
                        System.arraycopy(rob.L2.Swing_Theta, 0, Angles, 0, 6);
                            //Support Angles (L1,L3,L4)
                        Angles[6] = rob.L1.Theta[1];
                        Angles[7] = rob.L1.Theta[2];
                        Angles[8] = rob.L3.Theta[1];
                        Angles[9] = rob.L3.Theta[2];
                        Angles[10] = rob.L4.Theta[1];
                        Angles[11] = rob.L4.Theta[2];
                        Send_Angles(Leg_no, Angles);
                        break;
                    case 3:
                        //Move Leg3
                        rob.L3.Move();
                        //Shift COM
                        rob.Move_COM(Leg_no);
                        //Send Angles
                            //Swing Angles (L3)
                        System.arraycopy(rob.L3.Swing_Theta, 0, Angles, 0, 6);
                            //Support Angles (L1,L2,L4)
                        Angles[6] = rob.L1.Theta[1];
                        Angles[7] = rob.L1.Theta[2];
                        Angles[8] = rob.L2.Theta[1];
                        Angles[9] = rob.L2.Theta[2];
                        Angles[10] = rob.L4.Theta[1];
                        Angles[11] = rob.L4.Theta[2];
                        Send_Angles(Leg_no, Angles);
                        break;
                    case 4:
                        //Move Leg4
                        rob.L4.Move();
                        //Shift COM
                        rob.Move_COM(Leg_no);
                        //Send Angles
                            //Swing Angles (L4)
                        System.arraycopy(rob.L4.Swing_Theta, 0, Angles, 0, 6);
                            //Support Angles (L1,L2,L3)
                        Angles[6] = rob.L1.Theta[1];
                        Angles[7] = rob.L1.Theta[2];
                        Angles[8] = rob.L2.Theta[1];
                        Angles[9] = rob.L2.Theta[2];
                        Angles[10] = rob.L3.Theta[1];
                        Angles[11] = rob.L3.Theta[2];
                        Send_Angles(Leg_no, Angles);
                        break;
                    default:
                        //Error
                        return;
                }
                //Go to the Next State
                CS = NS;
                NS = FSM.Swing;
            } else {
                //Shift_Quad State is Optional State.
                rob.L1.Update(0, 45, 90);
                rob.L2.Update(0, 45, 90);
                rob.L3.Update(0, 45, 90);
                rob.L4.Update(0, 45, 90);
                //Send Angles
                for(int i=0; i<12;){
                    Angles[i] = 45;
                    Angles[i+1] = 90;
                    i=i+2;
                }
                Send_Angles(1, Angles);
                CS = NS;
                NS = FSM.Swing;
            }
            if(reset)
        	{
            	 rob.L1.Update(0, 45, 90);
                 rob.L2.Update(0, 45, 90);
                 rob.L3.Update(0, 45, 90);
                 rob.L4.Update(0, 45, 90);
                 //Send Angles
                 for(int i=0; i<12;){
                     Angles[i] = 45;
                     Angles[i+1] = 90;
                     i=i+2;
                 }
                 Send_Angles(1, Angles);
                 CS = NS;
                 NS = FSM.Swing;
        		reset = false;
        	}
        }
    }
}
