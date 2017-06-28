#include "stdafx.h"
#include "Shape.h"
#include "Utils.h"
#include <assert.h>
#include <iostream>
using namespace std;

Shape::Shape() : fill(0)
{
  SetFill("");
}

Shape::~Shape()
{
  // cout << "Shape::~Shape()" << endl;
  delete[] fill;
}

void Shape::ParseAttributes(char* attributes)
{
  if (attributes)
    {
      char* iter = attributes;

      while ((iter = SkipWhitespace(iter)))
        {
          char* name = iter;
          iter = GetToken(name, "="WHITESPACE_CHARS);

          if (*iter != '=')
            {
              *(iter++) = 0;
              iter = SkipWhitespace(iter);
              assert(*iter == '=');
            }

          *(iter++) = 0;
          iter = SkipWhitespace(iter);
          assert(*iter == '"');
          ++iter;

          char *value = iter;
          iter = GetToken(iter, "\"");
          *(iter++) = 0;

          AddAttrib(name, value);
        }
    }
}

void Shape::SetFill(const char* new_fill)
{
  delete[] fill;
  int fill_size = strlen(new_fill);
  fill = new char[fill_size + 1];
  strcpy_s(fill,fill_size + 1, new_fill);
}


void Shape::AddAttrib(char* name, char* value)
{
  cout << "Shape::AddAttrib" << endl;
}
