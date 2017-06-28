#pragma once
#include <fstream>
using namespace std;
class Shape
{
public:
  Shape();
  virtual ~Shape();
  void ParseAttributes(char*);
  void SetFill(const char*);
  virtual void AddAttrib(char*, char*) = 0;
  virtual void Print() = 0;
  virtual void Translate(float, float) = 0;
  virtual void Save(ofstream*) = 0;
  virtual bool Create(char* ) = 0;
  virtual bool CheckWithinRect(float, float, float, float) = 0;
  virtual bool CheckWithinCircle(float, float, float) = 0;
protected:
  char* fill;
};
