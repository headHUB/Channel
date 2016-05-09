class PIDTunings : public Packet {
public:     
  float kp, ki, kd;
  
  PIDTunings(){};
  
  PIDTunings(float kp, float ki, float kd):
    kp(kp), ki(ki), kd(kd){}
  
  char size(){
    return 12;
  }

  struct data {
    float kp, ki, kd;
  };

  void init(char* bytes){
    data d=*(data*)bytes;
    kp=d.kp;
    ki=d.ki;
    kd=d.kd;
  }
  
  char* bytes(){
    data d{kp, ki, kd};
    return (char*)&d;
  }
  
};
