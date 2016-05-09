#include "SimpleSerial.h"

/*Initializes HardwareSerial
 *and transmits the "READY" byte to sychronize*/
void Channel::init(int baudrate){
    Serial.begin(baudrate);

    while (Serial.read()!=READY) ;
    
    Serial.write(READY);
    
    while (Serial.read()!=READY) ;
    
    Serial.write(READY);



}

/*Waits for at least one byte to be available, then runs an event*/
void Channel::await(){
    while (Serial.available()==0) {}
    event();
}

/*runs an event if there are bytes available*/
void Channel::check(){
    if (Serial.available()>0) event();
}

/*reads first byte of data then passes execution on to specific
 *methods*/
void Channel::event(){
    char type=buffer(1)[0]; //first byte is type ID

    switch (type){
        case INT:
            handleInt();
            break;
        case FLOAT:
            handleFloat();
            break;
        case STRING:
            handleString();
            break;
        default:
            char size=buffer(1)[0];
            char* data=buffer(size);
            for(int i=0; i<ntypes; i++){
                if (types[i]==type){
                    handles[i](data,size);
                    break;
                }
                    
            }
    }
}

/*handle data by type-casting*/
void Channel::handleInt(){
    long i=*(long*)buffer(sizeof(long));
    intCallback(i);
}
void Channel::handleFloat(){
    float f=*(float*)buffer(sizeof(float));
    floatCallback(f);
}

/*handle String using HardwareSerial functions*/
void Channel::handleString(){
    String s=Serial.readStringUntil('\0');
    stringCallback(s);
}

/*waits for the desired amount of bytes then puts
 *them out in to an array*/
char* Channel::buffer(char size){
    while (Serial.available()<size){}
    
    char buffer[size];
    Serial.readBytes(buffer, size);
    return buffer;
}

/*sends a fixed amount of bytes preceeded by the type ID to interprete them*/
void Channel::tx(char type, char data[], char size) {
    Serial.write(type);
    if(type!=FLOAT && type!=INT && type!=STRING)
        Serial.write(size);
    Serial.write(data, size);
    Serial.flush();
}

/*send primary data types using above function*/
void Channel::tx(float f){
    tx(FLOAT, (char*)&f, sizeof(float));
}
void Channel::tx(double d){
    tx((float)d);
}
void Channel::tx(int i){
    tx((long)i);
}
void Channel::tx(long i){
    tx(INT, (char*)&i, sizeof(long));
}

/*send a String after conferting it to a char* */
void Channel::tx(String s){
    tx(STRING, (char *)s.c_str(), s.length()+1);
}

void Channel::setCallback(char type, callback f){
    handles[ntypes]=f;
    types[ntypes]=type;
    ntypes++;
}

void Channel::setCallback(void(*f)(int)){
    intCallback=f;
}
void Channel::setCallback(void(*f)(float)){
    floatCallback=f;
}
void Channel::setCallback(void(*f)(String)){
    stringCallback=f;
}











