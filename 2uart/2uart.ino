#include <NeoSWSerial.h>

// Определение программных UART портов
NeoSWSerial mySerial1(6, 7); // RX, TX для первого устройства
NeoSWSerial mySerial2(13, 5); // RX, TX для второго устройства

void setup() {
  // Инициализация аппаратного UART (Serial) и программных UART портов
  Serial.begin(9600);
  
  delay(100);
  mySerial2.begin(9600);
  delay(100);
  mySerial1.begin(9600);
}
bool first = true;
bool second = true;
String first_data = "";
String second_data = "";
void loop() {

  if (mySerial1.available() && second)
  {
    //Serial.print(mySerial1.parseInt());
    char c = mySerial1.read();
    Serial.write(c);
    //first_data = first_data + String(c);
    if (c == '\n')
    {
    mySerial2.begin(9600);
    Serial.print("first ");
    //first_data = "";
    first = true;
    second = false;
    }
  }
  if (mySerial2.available() && first)
  { 
    char c = mySerial2.read();
    Serial.write(c);
    second_data = second_data + String(c);
    if (c == '\n')
    {
    mySerial1.begin(9600);
    Serial.print("second ");
    //second_data = "second ";
    second = true;
    first = false;
    }
  }
}
