package arduino;

public abstract class ArduinoPacket {
		
	public byte type;
	
	//(Override required for tx)
	protected abstract byte[] bytes();
	
	//Override required in variably sized structures
	public void rx(Arduino a){
		byte size=a.buffer(1)[0];
		byte[] b=a.buffer(size);
		init(b);
	}
	
	//Assemble data structure from byte array
	//(Override required for rx in fix sized structures)
	protected abstract void init(byte[] b);
	
}
