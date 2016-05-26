#ifndef HardwareSerial_h
#define HardwareSerial_h
extern "C"{
  #include "posix/arduino-serial-lib.h"
}

#include <unistd.h> //for delay
void delay(int n){
  usleep(n*1000);
}

class HardwareSerial{
public:
	HardwareSerial(const char* serialport);
  ~HardwareSerial();
	void begin(int baud);
  void write(char);
  void write(char*, int);
  void flush();
  int peek();
  int read();
  void readBytes(char*, int);
private:
  const char* serialport;
  int fd;
  int peeked;

};

HardwareSerial::HardwareSerial(const char* port){
  serialport=port;
  fd=-1;
  peeked=-1;
}

HardwareSerial::~HardwareSerial(){
  serialport_close(fd);
}

void HardwareSerial::begin(int baud){
  if (fd==-1)
    fd=serialport_init(serialport, baud);
}

void HardwareSerial::write(char c){
  serialport_writebyte(fd, c);
}

void HardwareSerial::write(char* c, int n){
  serialport_writebytes(fd, c, n);
}

int HardwareSerial::peek(){
  if(peeked==-1)
    peeked = serialport_readbyte(fd);
  return peeked;
}

int HardwareSerial::read(){
  int n;
  if (peeked!=-1) {
    n=peeked;
    peeked=-1;
  } else {
    n= serialport_readbyte(fd);
  }
  return n;
}

void HardwareSerial::readBytes(char* buf, int len){
  if (len<=0) return;
  if(peeked!=-1){
    buf[0]=peeked;
    serialport_readbytes(fd, buf+1, len-1);
  } else
    serialport_readbytes(fd, buf, len);
}

void HardwareSerial::flush(){
  serialport_flush(fd);
}

#endif //HardwareSerial.h
