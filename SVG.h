#pragma once

#include "Shape.h"
#include <fstream>

using namespace std;

class SVG
{
public:
  SVG();
  SVG(const SVG &);
  ~SVG();
  SVG & operator=(const SVG &);
  void DeleteShapes();
  void Copy(const SVG &);
  char* GetFilename();
  bool Open(const char*);
  bool Save();
  bool SaveAs(const char*);
  bool Close();
  void Print();
  void Resize(int);
  void Insert(Shape *);
  void Erase(int);
  void Translate(float, float);
  void CheckWithin(char*);
private:
  char* filename;
  Shape** shapes;
  int shapes_count;
  int shapes_size;
};
