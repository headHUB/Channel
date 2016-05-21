#ifndef SMARTSERIAL_H
#define SMARTSERIAL_H

#include "HardwareSerial.h"

#define MAX_SOCKETS 4
#define READY 0xAA


template <class P> class Channel {
public:
  Channel(HardwareSerial&, const int&, const char& id, void(*)(P&)=nf);
  void send(const P&);
  void check();
private:
  const char id;
  const void (*callback)(P&);
  HardwareSerial* Serial;
  void rx();
  void buffer(char* , unsigned int);

  //placeholder for the callback function (null-function)
  void nf(P& p){}
};
#endif //SMARTSERIAL_H
