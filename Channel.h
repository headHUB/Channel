#ifndef Channel_h
#define Channel_h

#include "Arduino.h"

template <class P> class Channel {
public:
  Channel<P>(HardwareSerial &s, long baud, char id, void(*)(P&));
  void send(const P&);
  void check();
private:
  const char id;
  void (*callback)(P&);
  HardwareSerial* Serial;
  void rx();
  void get(char* , int);
};

/*================IMPLEMENTATION=================*/

template <class P>
Channel<P>::Channel(HardwareSerial& s, long baud, char id, void(*cb)(P&)):
  id(id), Serial(&s), callback(cb) {
  Serial->begin(baud);
}

template <class P>
void Channel<P>::check(){
  if (Serial->peek()==id){
    Serial->read(); //discard id byte
    P p;
    int s=p.size();
    if (s<0) get((char*)&s, -s);
    char buff[s];
    get(buff, s);
    p.parse(buff);

    callback(p);
  }
}

template <class P>
void Channel<P>::rx(){

}

template <class P>
void Channel<P>::send(const P &p){
  Serial->write(p.size());
  Serial->write(id);
  //Serial->write
}

template <class P>
void Channel<P>::get(char* buff, int size){
  for (int i=0; i<size; i++){
    while (Serial->available()<1){/*do nothing*/}
    buff[i]=Serial->read();
  }
}

#endif
