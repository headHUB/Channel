#include "../Channel.h"
#include <iostream>
#include <string>
#include <limits.h>

using namespace std;

struct Ratio {
  int32_t num, den;
};

HardwareSerial Serial("/dev/cu.usbmodem14131");

Channel<Ratio> rch;
Channel<float> fch;

//bulletproof function to get user input
template <typename t> void get(t& var){
  while (! (cin >> var)) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "oops, retry:\t";
  }
}

void setup() {
  rch.init(Serial, 115200, 'R');
  fch.init(Serial, 115200, 'F');

}

void loop() {
  Ratio r;
  cout << "Numerator:\t";
  get(r.num);
  cout << "Denominator:\t";
  get(r.den);
  rch.send(r);
  float f = fch.next();
  cout << "Decimal:\t" << f << '\n';
  cout << "=====================================\n";
}

int main(){
  setup();
  while(1) loop();
}
