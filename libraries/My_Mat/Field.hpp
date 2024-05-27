#ifndef FIELD_HPP
#define FIELD_HPP

#include "Arduino.h"

class Field
{
  public:
    void draw(char x, char y, bool c);
    bool checkLight(char x, char y);
    bool checkMoveable(char x, char y);
    void move(String str);
    void fall(float angle);
  private:
    static const char length = 16;
    static const char height = 16;
    bool field[length][height][2] = {};
};
#endif
