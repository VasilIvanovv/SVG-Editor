#pragma once

#include "Shape.h"
using namespace std;

class Circle : public Shape
{
public:
  Circle();
  Circle(char* );
  ~Circle();
  void AddAttrib(char*, char*);
  void Print();
  void Translate(float, float);
  void Save(ofstream*);
  bool Create(char*);
  bool CheckWithinRect(float, float, float, float);
  bool CheckWithinCircle(float, float, float);
private:
  float cx;
  float cy;
  float r;
};
