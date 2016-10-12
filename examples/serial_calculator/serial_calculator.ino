#include <Channel.h>
#include <stdint.h>

struct Ratio {
    int32_t num, den;
};

Channel<Ratio> rch;
Channel<float> fch;

void reply(Ratio& r){
  fch.send((float)r.num/r.den);
}

void setup() {
  rch.init(Serial, 115200, 'R', reply);
  fch.init(Serial, 115200, 'F');
}

void loop() {
  rch.check();
}
