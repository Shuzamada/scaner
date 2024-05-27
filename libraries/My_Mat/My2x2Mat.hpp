#ifndef MY2X2MAT_HPP
#define MY2X2MAT_HPP

#include "Field.hpp"
#include "Arduino.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

Max72xxPanel getMatrix();
void clear();
void draw(char y, char x, bool c);
void drawField(const Field& f);

#endif