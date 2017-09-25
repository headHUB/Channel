#if defined(ARDUINO)
#else
#include "../Channel.h"
#include <iostream>
#include <string>
#include <limits.h>

using namespace std;

HardwareSerial Serial("/dev/cu.SLAB_USBtoUART");

Channel<float> ch;

void setup() {
  ch.init(Serial, 115200, 'R');
}

void loop() {
  float f;
  cin >> f;
  ch.send(f);
}

int main(){
  setup();
  while(1) loop();
}
#endif
