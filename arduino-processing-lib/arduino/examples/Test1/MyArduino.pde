class MyArduino extends Arduino{
  
  void handle(float f){
    println(f);
  }
  void handle(int i){
    println(i);
  }
  void handle(String s){
    println(s);
  }
  
  void handle(PIDTunings pidt){
    println("kp "+pidt.kp);
    println("ki "+pidt.ki);
    println("kd "+pidt.kd);
  }
  
  void handleOther(byte type){
   
    if (type==PID_TUNINGS){
      PIDTunings pidt = new PIDTunings();
      pidt.rx(this);
      handle(pidt);
    }
  }
  
  byte PID_TUNINGS = 20;
  
}
