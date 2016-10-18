#ifndef CHANNEL_H
#define CHANNEL_H
#if defined(ARDUINO)
#include <HardwareSerial.h>
#include "Arduino.h"
#else
#include "pc-serial/PCSerial.h"
#endif

template <typename P> class Channel {
public:
  void init(HardwareSerial &s, long baud, char id, void(*)(P&)=0);
  void send(const P&);
  void check();
  void wait();
  P next();

private:
  char id;
  void (*callback)(P&);
  HardwareSerial* Serial;
};

template <typename P>
void Channel<P>::init(HardwareSerial& s, long baud, char ID, void(*cb)(P&)){
  id=ID;
  Serial=&s;
  callback=cb;
  Serial->begin(baud);
  delay(100);
}

template <typename P>
void Channel<P>::check(){
  if (Serial->peek()==id){
    Serial->read(); //discard id byte
		P p;
		Serial->readBytes((char*)&p, sizeof(P));
		callback(p);
  }
}

template <typename P>
void Channel<P>::wait(){
  while (Serial->read()!=id) ; //potentially buggy
	P p;
	Serial->readBytes((char*)&p, sizeof(P));
	callback(p);
}

template <typename P>
P Channel<P>::next(){
  while (Serial->read()!=id) ;
	P p;
	Serial->readBytes((char*)&p, sizeof(P));
	return p;
}

template <typename P>
void Channel<P>::send(const P &p){
  Serial->write(id);
  Serial->write((char*)&p,sizeof(P));
}

#endif
