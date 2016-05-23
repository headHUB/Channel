package arduino;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class ArduinoUtils {
	
	//useful functions for implementer
	public static byte[] bytes(float f){
		return ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putFloat(f).array();
	}
	public static byte[] bytes(int i){
		return ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(i).array();
	}
	
	public static float getFloat(byte[] b){
		return ByteBuffer.wrap(b).order(ByteOrder.LITTLE_ENDIAN).getFloat();
	}
	
	public static int getInt(byte[] b){
		return ByteBuffer.wrap(b).order(ByteOrder.LITTLE_ENDIAN).getInt();
	}
	
	public static byte[] join(byte[][] a){
		byte[] output=a[0];
		for(int i=1; i<a.length; i++){
			output=join(output, a[i]);
		}
		return output;
	}
	
	public static byte[] join(byte[] a, byte[] b) {
		int aLen = a.length;
		int bLen = b.length;
		byte[] c= new byte[aLen+bLen];
		System.arraycopy(a, 0, c, 0, aLen);
		System.arraycopy(b, 0, c, aLen, bLen);
		return c;
	}

}
