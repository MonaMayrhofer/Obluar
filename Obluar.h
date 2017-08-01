#include <SoftwareSerial.h>

class Obluar{
public:
  Obluar(int rxp, int txp);
  ~Obluar();

  void begin();

  char getData();
  void setData(char c);
  bool hasNewData();
  void flush();
  char getLastData();

  String help();
  String conn();
  String getdcn();
  String version();
  String laddr();
  String disc();
  String pin();

  String getError();
  bool hasError();

private:
  void sendCmd(String s);
  void checkListen();
  String receiveString();

  int _rxp;
  int _txp;
  char _data;
  int _error;

  SoftwareSerial* _serial;
};
