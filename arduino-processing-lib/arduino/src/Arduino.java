package arduino;

import processing.core.PApplet;
import processing.serial.*;
import java.lang.reflect.Method;
import java.util.HashMap;
import java.lang.Byte;


public class Arduino {
	
	HashMap<Byte,Method> callbacks=new HashMap<Byte,Method>();
	
	private Serial serial;
	
	private PApplet parent;
	
	public Arduino(String port, int baudrate, PApplet parent) {
		this.parent=parent;
		serial = new Serial(parent, port, baudrate);
		while (serial.read()!=READY){
			serial.write(READY);
			parent.print(".");
			delay(100);
		}
		delay(100);
		while (serial.read()!=READY){
			serial.write(READY);
			parent.print(".");
			delay(100);
		}
		parent.println("CONNECTED");

			
	}
	
	public void setCallback(byte type, String functionName){
		Method m;
		switch (type){
		  case INT:
			  try{
				  m=parent.getClass().getMethod(functionName, int.class);
			  }catch(Exception e){
				  return;
			  }
			  break;
		  case FLOAT:
			  try{
				  m=parent.getClass().getMethod(functionName, float.class);
			  }catch(Exception e){
				  return;
			  }
			  break;
		  case STRING:
			  try{
				  m=parent.getClass().getMethod(functionName, String.class);
			  }catch(Exception e){
				  return;
			  }			  
			  break;
		  default:
			  try{
				  m=parent.getClass().getMethod(functionName, byte[].class);
			  }catch(Exception e){
				  return;
			  }
		}
		callbacks.put(type, m);
	}
	
	/*program holds until data is received and handled*/
	public void await() {
	  while (serial.available ()==0) {
	    parent.delay(0);
	  }
	  arduinoEvent();
	}

	/*must be called inside loop function...multithreading in the future!*/
	public void check() {
	  if (serial.available()>0) arduinoEvent();
	}

	/*defines what happens when data is received*/
	private void arduinoEvent() {
	  byte type=(byte)serial.readChar(); //first byte is type ID
	  switch (type){
	  case INT:
		  handleInt();
		  break;
	  case FLOAT:
		  handleFloat();
		  break;
	  case STRING:
		  handleString();
		  break;
	  default:
		  byte size=buffer(1)[0];
		  byte[] data=buffer(size);
			try{
				callbacks.get(type).invoke(parent,data);
			}catch(Exception e){}
	  }
	}
	
	//gets the specified amount of bytes from serial port
	//waits for new data if necessary 
	public byte[] buffer(int size){
		while (serial.available()<size) {
			parent.delay(0); 
		}
		byte[] buffer=new byte[size];
		serial.readBytes(buffer);
		return buffer;
	}
	
	private void handleInt() {
		byte[] b = buffer(4);
		
		int i = ArduinoUtils.getInt(b);
		try{
			callbacks.get(INT).invoke(parent,i);
		}catch(Exception e){}
	}
	
	private void handleFloat() { 
		byte[] b = buffer(4);
		float f = ArduinoUtils.getFloat(b);
		try{
			callbacks.get(FLOAT).invoke(parent,f);
		}catch(Exception e){}
	}
	
	private void handleString(){
		String s="";
		char ch;
		while(true){
			while(serial.available()==0)
				parent.delay(0);
			ch=serial.readChar();
			if(ch=='\0') break;
			s+=ch;
		}

		try{
			callbacks.get(STRING).invoke(parent,s);
		}catch(Exception e){}
	}
	
	public void tx(byte[] data, byte type){
		serial.write(type);
		if(type!=INT && type!=FLOAT && type!=STRING){
			serial.write((byte)data.length);
		}
		serial.write(data);
	}
	
	public void tx(byte msg){
		serial.write(msg);
	}
	
	public void tx(int i){
		byte[] b = ArduinoUtils.bytes(i);
		tx(b,INT);
	}
	
	public void tx(float f){
		byte[] b = ArduinoUtils.bytes(f);
		tx(b,FLOAT);
	}
	
	public void tx(String s){
		serial.write(STRING);
		serial.write(s);
		serial.write('\0');
	}

	private void delay(int milliseconds){
		try {
		    Thread.sleep(milliseconds);                 //1000 milliseconds is one second.
		} catch(InterruptedException ex) {
		    Thread.currentThread().interrupt();
		}
	}
	
	/*single byte messages*/
	private static final byte READY = 20;

	/*self implemented types*/
	public static final byte INT = 40;
	
	public static final byte FLOAT = 41;
	
	public static final byte STRING = 42;
	

}
