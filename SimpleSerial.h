#ifndef SIMPLESERIAL_H
#define SIMPLESERIAL_H

#include "Arduino.h"

#define N_TYPES 4

//Packet type byte IDs
#define INT 40
#define FLOAT 41
#define STRING 42
#define READY 20

typedef void (*callback)(char*,char);

class Channel {

public:

    /*call before anything else*/
    void init(int baudrate);

    /*program holds until any data is received and handled*/
    void await();

    /*must be called regularly to check the input buffer*/
    void check();

    /*trasmit default primary data types*/
    void tx(double d);
    void tx(float f);
    void tx(int i);
    void tx(long i);
    void tx(String s);

    /*tx anything else*/
    void tx(char type, char data[], char size);

    /*Assign functions for rx
     *TODO: make this happen in compile time?
     */
    void setCallback(char type, callback f);
    void setCallback(void(*f)(int));
    void setCallback(void(*f)(float));
    void setCallback(void(*f)(String));


private:

    char types[N_TYPES];
    callback handles[N_TYPES];
    int ntypes=0;

    void (*intCallback)(int);
    void (*stringCallback)(String);
    void (*floatCallback)(float);


    /*gets the exact amount of bytes, waits for them if necessary*/
    char* buffer(char size);

    /*defines what happens when data is received*/
    void event();

    /*turn bytes into the correct data types and call the "handle" methods*/
    void handleInt();
    void handleFloat();
    void handleString();

};




#endif
