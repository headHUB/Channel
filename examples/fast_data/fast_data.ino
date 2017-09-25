#include <PID.h>
#include <Channel.h>
Channel<PIDData> ch;


void setup() {
  ch.init(Serial, 115200, 'P');
  leftServo.tuneAnglePID(0.004, 0, 0.002);

  leftServo.goTo(360);
}

void loop() {
  if(leftServo.update())
    ch.send(*leftServo.getData());
}
