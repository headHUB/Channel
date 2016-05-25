#include "../Channel.h"
#include "../HardwareSerial.h"
#include <iostream>

using namespace std;

HardwareSerial Serial("/dev/cu.usbmodem1411");

struct Ratio {
    int16_t num, den;
} r;

Channel<Ratio> rch;
//Channel<float> fch;

void print(Ratio& r){
  cout << ((float)r.num/r.den) << endl;
}

void setup() {
  rch.init(Serial, 115200, 'R', print);
  //fch.init(Serial, 115200, 'F');

}

void loop() {
	cout << "Inserisci numeratore: ";
	cin >> r.num;
	cout << "Inserisci denominatore: ";
	cin >> r.den;
	rch.send(den);
  rch.wait();
}

int main(){
	setup();
	while(1) loop();
}
