#ifndef HardwareSerial_h
#define HardwareSerial_h
extern "C"{
  #include "posix/arduino-serial-lib.h"
}

class HardwareSerial{
public:
	HardwareSerial(const char* serialport);
  ~HardwareSerial();
	void begin(int baud);
  void write(char);
  void write(char*, int);
  int peek();
  int read();
  void readBytes(char*, int);
private:
  const char* serialport;
  int fd;

};

HardwareSerial::HardwareSerial(const char* port){
  serialport=port;
  fd=-1;
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
  return serialport_peek(fd);
}

int HardwareSerial::read(){
  return serialport_readbyte(fd);
}

void HardwareSerial::readBytes(char* buf, int len){
  serialport_readbytes(fd, buf, len);
}


#endif //HardwareSerial.h
