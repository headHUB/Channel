#include <BetterSerial.h>
#include "PIDTunings.h"

Processing pr;

void setup() {
  pr.init(9600);
  pr.setHandle(handleInt);
  
  PIDTunings pidt(1.2, 2.3, 3.4);
  pr.tx(pidt, PID_TUNINGS);
}

void loop() {
  pr.check();
}

void handleInt(int i){
}
