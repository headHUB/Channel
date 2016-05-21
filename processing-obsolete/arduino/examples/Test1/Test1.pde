import arduino.*;
import processing.serial.*;

MyArduino ar;

void setup() {
  ar=new MyArduino();
  ar.init(this, "/dev/tty.usbmodem1411", 9600);
  println("ready");
  //PIDTunings pidt=new PIDTunings(1.2, 3.4, 5.6);
  //pidt.tx(ar);
  ar.await();
}
