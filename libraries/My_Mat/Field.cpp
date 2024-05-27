#include "Field.hpp"
#include "Arduino.h"

void Field::draw(char x, char y, bool c)
{
  field[x][y][0] = c;
  field[x][y][1] = c;
}

bool Field::checkLight(char x, char y)
{
  if (x >= length or y >= height or x < 0 or y < 0)
  {
    return true;
  }
  return field[x][y][0];
}

bool Field::checkMoveable(char x, char y)
{
  if (x >= length or y >= height or x < 0 or y < 0)
  {
    return false;
  }
  return field[x][y][1];
}

void Field::move(String str)
{
  if (str == "down")
  {
    for (char i = 0; i < length; i++)
    {
      for (char j = 0; j < height; j++)
      {
        if (checkMoveable(i, j) && !checkLight(i, j + 1))
        {
          draw(i, j, 0);
          draw(i, j + 1, 1);
          j++;
        }
      }
    }
  }
  else if (str == "down_left")
  {
    for (char j = height; j >= 0; j--)
    {
      for (char i = 0; i < length; i++)
      {
        if (checkMoveable(i, j) && checkLight(i , j + 1) && !checkLight(i - 1, j + 1))
        {
          draw(i, j, 0);
          draw(i - 1, j + 1, 1);
        }
      }
    }
  }
  else if (str == "down_right")
  {
    for (char j = 0; j < height; j++)
    {
      for (char i = length; i >= 0; i--)
      {
        if (checkMoveable(i, j) && checkLight(i , j + 1) && !checkLight(i + 1, j + 1))
        {
          draw(i, j, 0);
          draw(i + 1, j + 1, 1);
          j++;
        }
      }
    }
  }
  else if (str == "left")
  {
    for (char j = 0; j < height; j++)
    {
      for (char i = length - 1; i >= 0; i--)
      {
        if (checkMoveable(i, j) && !checkLight(i - 1, j))
        {
          draw(i, j, 0);
          draw(i - 1, j, 1);
          i--;
        }
      }
    }
  }
  else if (str == "left_down")
  {
    for (char i = 0; i < length; i++)
    {
      for (char j = 0; j < height; j++)
      {
        if (checkMoveable(i, j) && checkLight(i - 1, j) && !checkLight(i - 1, j + 1))
        {
          draw(i, j, 0);
          draw(i - 1, j + 1, 1);
        }
      }
    }
  }
  else if (str == "left_up")
  {
    for (char i = 0; i < length; i++)
    {
      for (char j = 0; j < height; j++)
      {
        if (checkMoveable(i, j) && checkLight(i - 1, j) && !checkLight(i - 1, j - 1))
        {
          draw(i, j, 0);
          draw(i - 1, j - 1, 1);
        }
      }
    }
  }
  else if (str == "right")
  {
    for (char j = 0; j < height; j++)
    {
      for (char i = 0 ; i < length - 1; i++)
      {
        if (checkMoveable(i, j) && !checkLight(i + 1, j))
        {
          draw(i, j, 0);
          draw(i + 1, j, 1);
          i++;
        }
      }
    }
  }
  else if (str == "right_down")
  {
    for (char i = length; i > 0; i--)
    {
      for (char j = 0; j < height; j++)
      {
        if (checkMoveable(i, j) && checkLight(i + 1, j) && !checkLight(i + 1, j + 1))
        {
          draw(i, j, 0);
          draw(i + 1, j + 1, 1);
        }
      }
    }
  }
  else if (str == "right_up")
  {
    for (char i = 0; i < length; i++)
    {
      for (char j = 0; j < height; j++)
      {
        if (checkMoveable(i, j) && checkLight(i + 1, j) && !checkLight(i + 1, j - 1))
        {
          draw(i, j, 0);
          draw(i + 1, j - 1, 1);
        }
      }
    }
  }
  else if (str == "up")
  {
    for (char i = 0; i < length; i++)
    {
      for (char j = height - 1; j >= 0 ; j--)
      {
        if (checkMoveable(i, j) && !checkLight(i, j - 1))
        {
          draw(i, j, 0);
          draw(i, j - 1, 1);
          j--;
        }
      }
    }
  }
  else if (str == "up_left")
  {
    for (char j = 0; j < height; j++)
    {
      for (char i = length; i > 0; i--)
      {
        if (checkMoveable(i, j) && checkLight(i, j - 1) && !checkLight(i - 1, j - 1))
        {
          draw(i, j, 0);
          draw(i - 1, j - 1, 1);
        }
      }
    }
  }
  else if (str == "up_right")
  {
    for (char j = 0; j < height; j++)
    {
      for (char i = 0; i < length; i++)
      {
        if (checkMoveable(i, j) && checkLight(i, j - 1) && !checkLight(i + 1, j - 1))
        {
          draw(i, j, 0);
          draw(i + 1, j - 1, 1);
        }
      }
    }
  }
}

void Field::fall(float angle)
{
  while (angle > 360)
  {
    angle -= 360;
  }
  while (angle < 0)
  {
    angle += 360;
  }
  if (angle > 360 - 22.5 || angle < 22.5)
  {
    move("up");
    move("up_left");
    move("up_right");
  }
  if (angle > 45 - 22.5 && angle < 45 + 22.5)
  {
    move("right_up");
    move("up_right");
    move("up");
    move("right");
  }
  if (angle > 90 - 22.5 && angle < 90 + 22.5)
  {
    move("right");
    move("right_up");
    move("right_down");
  }
  if (angle > 135 - 22.5 && angle < 135 + 22.5)
  {
    move("down_right");
    move("right_down");
    move("down");
    move("right");
  }
  if (angle > 180 - 22.5 && angle < 180 + 22.5)
  {
    move("down");
    move("down_left");
    move("down_right");
  }
  if (angle > 225 - 22.5 && angle < 225 + 22.5)
  {
    move("down_left");
    move("left_down");
    move("down");
    move("left");
  }
  if (angle > 270 - 22.5 && angle < 270 + 22.5)
  {
    move("left");
    move("left_up");
    move("left_down");
  }
  if (angle > 315 - 22.5 && angle < 315 + 22.5)
  {
    move("left_up");
    move("up_left");
    move("left");
    move("up");
  }
}
