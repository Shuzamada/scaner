#include <NeoSWSerial.h>

// Определение программных UART портов
NeoSWSerial mySerial1(6, 7); // RX, TX для первого устройства
NeoSWSerial mySerial2(13, 5); // RX, TX для второго устройства

void setup() {
  // Инициализация аппаратного UART (Serial) и программных UART портов
  Serial.begin(9600);
  mySerial1.begin(9600);
  mySerial2.begin(9600);
}
bool first = false;
bool second = false;
void loop() {

  if (mySerial1.available())
  {
    char c = mySerial1.read();
    Serial.write(c);
    if (c == '\n')
    first = true;
  }
  if (first)
  {
    Serial.println("first");
    mySerial2.begin(9600);
    first = false;
  }

  if (mySerial2.available())
  { 
    char c = mySerial2.read();
    Serial.write(c);
    if (c == '\n')
    second = true;
  }
  if (second)
  {
    Serial.println("second");
    mySerial1.begin(9600);
    second = false;
  }
}
