#include "stdafx.h"
#include "Line.h"
#include "Utils.h"

#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

Line::Line() : Shape()
{
}

Line::Line(char* attributes) : Shape()
{
  ParseAttributes(attributes);
}

Line::~Line()
{
  // cout << "Line::~Line()" << endl;
}

void Line::AddAttrib(char* name, char* value)
{
  if (strcmp(name, "x1") == 0)
    {
      x1 = (float) atof(value);
    }
  else if (strcmp(name, "y1") == 0)
    {
      y1 = (float) atof(value);
    }
  else if (strcmp(name, "x2") == 0)
    {
      x2 = (float) atof(value);
    }
  else if (strcmp(name, "y2") == 0)
    {
      y2 = (float) atof(value);
    }
}

void Line::Translate(float horizontal, float vertical)
{
  x1 += horizontal;
  x2 += horizontal;
  y1 += vertical;
  y2 += vertical;
}

void Line::Print()
{
  cout << "line "
       << x1 << " "
       << y1 << " "
       << x2 << " "
       << y2 << endl;
}

void Line::Save(ofstream *svgfile)
{
  *svgfile << "<line x1=\"" << x1
           << "\" y1=\"" << y1
           << "\" x2=\"" << x2
           << "\" y2=\"" << y2
           << "\" />\n";
}

bool Line::Create(char* args)
{
	args = SkipWhitespace(args);
	if (!args) return false;

	char* end;
	float num;

	x1 = strtof(args, &end);
	if (args == end) return false;
	args = end;

	y1 = strtof(args, &end);
	if (args == end) return false;
	args = end;

	x2 = strtof(args, &end);
	if (args == end) return false;
	args = end;

	y2 = strtof(args, &end);
	if (args == end) return false;

	args = SkipWhitespace(end);
	if (args) return false;

	return true;
}

bool Line::CheckWithinRect(float rx1, float ry1, float rw, float rh)
{
	float rx2 = rx1 + rw;
	float ry2 = ry1 + rh;
	if (x1 > rx1 && x1 < rx2 &&
		x2 > rx1 && x2 < rx2 &&
		y1 > ry1 && y1 < ry2 &&
		y2 > ry1 && y2 < ry2)
	{
		return true;
	}
	return false;
}

bool Line::CheckWithinCircle(float cx, float cy, float r)
{
	if ((x1 - cx)*(x1 - cx) + (y1 - cy)*(y2 - cy) < r*r)
	{
		return true;
	}
	return false;
}