#include "SensorGrid3.hpp"

SensorGrid3 sensor_grid(5, 13,
                        6, 13,
                        7, 13);

void setup()
{
  Serial.begin(9600);
  sensor_grid.begin(9600);
}
void loop()
{
  Serial.print("first:");
  Serial.print(sensor_grid.readFirst());
  Serial.print("  second:");
  Serial.print(sensor_grid.readSecond());
  Serial.print("  third:");
  Serial.println(sensor_grid.readThird());
}
