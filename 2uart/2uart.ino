#include <NeoSWSerial.h>

// Определение программных UART портов
NeoSWSerial mySerial1(5, 13); // RX, TX для первого устройства
NeoSWSerial mySerial2(6, 13); // RX, TX для второго устройства
NeoSWSerial mySerial3(7, 13);
void setup() {
  Serial.begin(9600);
  delay(100);
  mySerial3.begin(9600);
  delay(100);
  mySerial2.begin(9600);
  delay(100);
  mySerial1.begin(9600);
}
bool first = true;
bool second = true;
bool third = true;
String first_data = "";
String second_data = "";
String third_data = "";
void loop() {

  if (mySerial1.available() && third)
  {
    char c = mySerial1.read();
    first_data = first_data + String(c);
    if (c == '\n')
    {
    mySerial2.begin(9600);
    Serial.print("first " + first_data);
    first_data = "";
    first = true;
    third = false;
    }
  }
  if (mySerial2.available() && first)
  { 
    char c = mySerial2.read();
    //Serial.write(c);
    second_data = second_data + String(c);
    if (c == '\n')
    {
    mySerial3.begin(9600);
    Serial.print(second_data);
    second_data = "second ";
    second = true;
    first = false;
    }
  }
  if (mySerial3.available() && second)
  { 
    char c = mySerial3.read();
    //Serial.write(c);
    third_data = third_data + String(c);
    if (c == '\n')
    {
    mySerial1.begin(9600);
    Serial.print(third_data);
    third_data = "third ";
    third = true;
    second = false;
    }
  }
}
