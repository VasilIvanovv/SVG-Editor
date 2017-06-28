#pragma once

#include "Shape.h"
using namespace std;

class Line : public Shape
{
public:
  Line();
  Line(char* );
  ~Line();
  void AddAttrib(char*, char*);
  void Print();
  void Translate(float, float);
  void Save(ofstream*);
  bool Create(char*);
  bool CheckWithinRect(float, float, float, float);
  bool CheckWithinCircle(float, float, float);
private:
  float x1;
  float y1;
  float x2;
  float y2;
};
