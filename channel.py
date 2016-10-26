import struct
'''
class UARTSerial: 
    import serial

    def __init__(self, filename, baudrate): 
        #TODO
    def write(self, data):
        #TODO
    def peek(self):
        #TODO
    def readBytes(self, n):
        #TODO
    def read(self):
        #TODO
'''
class IPSerial:
    socket = __import__('socket')
    
    def __init__(self, address, port, baudrate):
        self.sock = self.socket.socket()
        self.sock.connect((address,port))

    def write(self, data): 
        self.sock.send(data)
    def peek(self):
        return self.sock.recv(1, self.socket.MSG_PEEK)
    def readBytes(self, n):
        return self.sock.recv(n, self.socket.MSG_WAITALL)
    def read(self):
        return self.sock.recv(1)


class Channel:
    def __init__(self, serial, type, id):
        self.ser = serial
        self.id = id
        #define type and sizes for the parser
        self.n = 4 #for float experiment

    def setCallback(self, callbackFunction):
        self.cb = callbackFunction
        
    def parse(self, raw):
        return struct.unpack('<f',raw)[0]

    def check(self):
        if self.ser.peek() == self.id:
            self.ser.read()
            data = self.ser.readBytes(self.n)
            packet = self.parse(data)
            self.cb(packet)

    def wait(self):
        byte = self.ser.read()
        while byte != self.id:
            byte = self.ser.read()
        data = self.ser.readBytes(self.n)
        packet = self.parse(data)
        self.cb(packet)

    def next(self):
        byte = self.ser.read()
        while byte != self.id:
            byte = self.ser.read()
        data = self.ser.readBytes(self.n)
        packet = self.parse(data)
        return packet

    def send(self, packet):
        raw = struct.pack('<f',packet)
        self.ser.write(self.id)
        self.ser.write(raw)
        
def serial(address, baudrate):
    splitPort = address.split(':')
    if len(splitPort) == 2:
        return IPSerial(splitPort[0],int(splitPort[1]),baudrate)
    if len(splitPort)== 1:
        return UARTSerial(address, baudrate)
