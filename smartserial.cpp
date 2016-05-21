#include "SmartSerial.h"

//DONE
template <class P>
Channel<P>::Channel(HardwareSerial& s, const int& baud, const char& id, void(*cb)(P&))
  : id(id), Serial(&s), callback(cb) {
    Serial->begin(baud);
}

//DONE
template <class P>
void Channel<P>::check(){
  if (Serial->peek()==id){
    Serial->read(); //discard id byte
    rx();          //deal with the data
  }
}

template <class P>
void Channel<P>::rx(){
  Serial->read();
  P p();
  int s=p.length;
  if (s<0) {
    buffer((char*)&s, -s);
    p.length=s;
  }
  p.parse(buffer(s));

  callback(p);
}

template <class P>
void Channel<P>::send(const P &p){
  Serial->w
}

/*waits for the desired amount of bytes then puts
 *them out in to an array*/
template <class P>
void Channel<P>::buffer(char* buff, unsigned int size){
  for (unsigned int i=0; i<size; i++){
    while (Serial->available()<1){/*do nothing*/}
    buff[i]=Serial->read();
  }
}
