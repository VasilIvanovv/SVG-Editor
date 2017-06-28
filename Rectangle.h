#pragma once

#include "Shape.h"
using namespace std;

class Rectangle : public Shape
{
public:
  Rectangle();
  Rectangle(char *);
  ~Rectangle();
  void AddAttrib(char*, char*);
  void Print();
  void Translate(float, float);
  void Save(ofstream*);
  bool Create(char*);
  bool CheckWithinRect(float, float, float, float);
  bool CheckWithinCircle(float, float, float);
private:
  float x;
  float y;
  float width;
  float height;
};
