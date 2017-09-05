package gp;

import processing.core.*;
import processing.serial.*;


public class SheblSerial extends PApplet {
	private Serial port;
	
	//Initialize Serial port
	public void Init()
	{
		//println("Available serial ports:");
		//println(Serial.list());
		//PApplet.main(new String[] { "--present", "gp.SheblSerial" });
		port = new Serial(this, Serial.list()[2], 57600);
		delay(1000);
	}
	
	public void setup()
	{
		
		
	}
	
	//Send leg and angles data to serial port
	public void send(int leg, int[] angles)
	{
		while(true)
		{
			if(port.available() > 0)
			{
				System.out.println("Data Receive");
				int c = port.read();
				System.out.println(c);
				if(c == 250)
				{
					System.out.println("BREAK!");
					break;
				}
				delay(20);
			}
				System.out.println("send");
				int h = 251;
				port.write((char)h);
				delay(20);
		}
		System.out.println("Done HandShaking");
		System.out.print(leg + ": ");
		
		port.write((char)leg);
		for(int i = 0; i < 12; i++)
		{
			System.out.print(angles[i] + " ");
			port.write((char)angles[i]);
		}
		delay(200);
		while(true)
		{
			if(port.available() > 0)
			{
				System.out.println("ACK:Data Receive");
				int c = port.read();
				System.out.println(c);
				if(c == 251)
				{
					System.out.println("ACK:BREAK!");
					break;
				}
				delay(200);
			}
				System.out.println("ACK:send");
				int h = 250;
				port.write((char)h);
				delay(200);
		}
		System.out.println("ACK:Done HandShaking");
	}
	
}
