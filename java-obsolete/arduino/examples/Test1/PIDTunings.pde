class PIDTunings extends ArduinoPacket{
    
  float kp, ki, kd;
  
  PIDTunings(){};
  
  PIDTunings(float kp, float ki, float kd){
    this.kp=kp;
    this.ki=ki;
    this.kd=kd;
  }
  
  byte type=22;
    
  void init(byte[] b){
    byte[][] split = new byte[3][4];
    
    for(int i=0; i<12; i++)
      split[i/3][i%4]=b[i];
      
    kp = ArduinoUtils.getFloat(split[0]);
    ki = ArduinoUtils.getFloat(split[1]);
    kd = ArduinoUtils.getFloat(split[2]);
  }
  
  byte[] bytes(){
    byte[][] b=new byte[3][4];
    b[0]=ArduinoUtils.bytes(kp);
    b[1]=ArduinoUtils.bytes(ki);
    b[2]=ArduinoUtils.bytes(kd);
    return ArduinoUtils.join(b);
  }
  
}
