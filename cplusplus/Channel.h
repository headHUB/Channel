#ifndef CHANNEL_H
#define CHANNEL_H

extern "C"{
  #include "HardwareSerial.h"
}
#define ESTABLISH '~'

template <typename P> class Channel {
public:
  void init(const char* serialport, int baud, char id, void(*)(P&)=0);
  void send(const P&);
  void check();
  void wait();
  P next();
  ~Channel();

private:
  char id;
  void (*callback)(P&);
  int fd;
};

#include "Channel.cpp"

#endif
