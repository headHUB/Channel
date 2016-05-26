#include "../Channel.h"
#include "../HardwareSerial.h"
#include <iostream>

using namespace std;

HardwareSerial Serial("/dev/cu.usbmodem1411");

struct Ratio {
    int16_t num, den;
} r;

Channel<Ratio> rch;
Channel<float> fch;

void print(float& f){
  cout << f << endl;
}

void setup() {
  rch.init(Serial, 115200, 'R');
  fch.init(Serial, 115200, 'F', print);

}

void loop() {
	cout << "Inserisci numerator: ";
	cin >> r.num;
	cout << "Inserisci denominator: ";
	cin >> r.den;
	rch.send(r);
  fch.wait();
}

int main(){
	setup();
	while(1) loop();
}
