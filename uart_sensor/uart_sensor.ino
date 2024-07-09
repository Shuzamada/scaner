#include <SoftwareSerial.h>



void setup() {
    Serial.begin(9600);
    sendCommand("s6-1#");
    sendCommand("s7-1#");
}
void sendCommand(String command) {
  Serial.print(command);
  Serial.flush();
  delay(100); // Задержка для выполнения команды
  // Чтение и вывод ответа датчика
  if (Serial.available()) {
    String response = Serial.readStringUntil('\n');
    Serial.println("Response: " + response);
  }
}
void loop() {
        Serial.println(Serial.parseInt());
} 
