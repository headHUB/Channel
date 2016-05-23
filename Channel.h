#ifndef CHANNEL_H
#define CHANNEL_H

#include "HardwareSerial.h"
#define ESTABLISH '~'

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

#include "Channel.cpp"

#endif