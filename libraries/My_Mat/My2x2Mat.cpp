#include "My2x2Mat.hpp"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

char pinCS = 9;
char nH = 2;
char nV = 2;

Max72xxPanel my_matrix = Max72xxPanel(pinCS, nH, nV);

Max72xxPanel getMatrix()
{
  return my_matrix;
}

void clear()
{
  for (short i = 0; i < 16; i++)
  {
    for (short j = 0; j < 16; j++)
    {
      my_matrix.drawPixel(i, j, 0);
    }
  }
  my_matrix.write();
}

void draw(char y, char x, bool c)
{
  if (x < 8 && y < 8)
  {
    y +=8;
  }
  else if (x >= 8 && y >= 8)
  {
    y -= 8;
  }
  else if (x >= 8 && y < 8)
  {
    x -= 8;
  }
  else if (x < 8  && y >= 8)
  {
    x += 8;
  }
  my_matrix.drawPixel(x, y, c);
}

void drawField(const Field& f)
{
  for (short i = 0; i < 16; i++)
  {
    for (short j = 0; j < 16; j++)
    {
      if (f.checkLight(i, j))
      {
        draw(j, i, 1);
      }
      else
      {
        draw(j, i, 0);
      }
    }
  }
  my_matrix.write();
}