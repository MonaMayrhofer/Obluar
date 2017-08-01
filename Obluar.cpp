#include "Obluar.h"
#include <Arduino.h>


Obluar::Obluar(int rxp, int txp){
  _rxp = rxp;
  _txp = txp;
  _error = 0;
  _serial = new SoftwareSerial(_rxp,_txp);
}

Obluar::~Obluar(){
  //delete _serial;
}

void Obluar::begin(){
  _serial->begin(9600);
}

void Obluar::sendCmd(String s){
  _serial->print(s);
  _serial->print("\r\n");
}

String Obluar::receiveString(){
  checkListen();
  return _serial->readStringUntil('\n');
}

String Obluar::help(){
  sendCmd("AT+HELP");
  String ret;
  ret = receiveString();
  while(_serial->available()){
    ret.append(receiveString());
  }
  return ret;
}

void Obluar::setData(char c){
  checkListen();
  _data = c;
}

char Obluar::getData(){
  checkListen();
  if(!_serial->available()){
    return 0;
  }
  return _serial->read();
}

bool Obluar::hasNewData(){
  checkListen();
  return _serial->available();
}

void Obluar::flush(){
  checkListen();
  _serial->flush();
}

char Obluar::getLastData(){
  checkListen();
  char rd = 0;
  while(_serial->available())
    rd = _serial->read();
  return rd;
}

String Obluar::conn(){
  sendCmd("AT+CONN");
  return receiveString();
}

String Obluar::getdcn(){
  sendCmd("AT+GETDCN");
  return receiveString();
}

String Obluar::version(){
  sendCmd("AT+VERSION");
  return receiveString();
}

String Obluar::laddr(){
  sendCmd("AT+LADDR");
  return receiveString();
}

String Obluar::disc(){
  sendCmd("AT+DISC");
  return receiveString();
}

String Obluar::pin(){
  sendCmd("AT+PIN");
  return receiveString();
}

void Obluar::checkListen(){
  if(!_serial->isListening())
    _error = 1;
}

bool Obluar::hasError(){
  return _error != 0;
}

String Obluar::getError(){
  switch (_error) {
    case 1:
      return "Obluar blocks SoftwareSerial. No other Software is allowed to listen.";
    default:
      return "Unknown Error Code";
  }
}
