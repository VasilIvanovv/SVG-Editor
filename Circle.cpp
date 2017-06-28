#include "stdafx.h"
#include "Circle.h"
#include "Utils.h"

#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;


Circle::Circle() : Shape()
{
}

Circle::Circle(char* attributes) : Shape()
{
  ParseAttributes(attributes);
}

Circle::~Circle()
{
  // cout << "Circle::~Circle()" << endl;
}

void Circle::AddAttrib(char* name, char* value)
{
  if (strcmp(name, "cx") == 0)
    {
      cx = (float) atof(value);
    }
  else if (strcmp(name, "cy") == 0)
    {
      cy = (float) atof(value);
    }
  else if (strcmp(name, "r") == 0)
    {
      r = (float) atof(value);
    }
  else if (strcmp(name, "fill") == 0)
    {
      SetFill(value);
    }
}

void Circle::Translate(float horizontal, float vertical)
{
  cx += horizontal;
  cy += vertical;
}

void Circle::Print()
{
  cout << "circle "
       << cx << " "
       << cy << " "
       << r << " "
       << fill << endl;
}

void Circle::Save(ofstream *svgfile)
{
  *svgfile << "<circle cx=\"" << cx
           << "\" cy=\"" << cy
           << "\" r=\"" << r
           << "\" fill=\"" << fill
           << "\" />\n";
}

bool Circle::Create(char* args)
{
	args = SkipWhitespace(args);
	if (!args) return false;

	char* end;
	float num;

	num = strtof(args, &end);
	if (args == end) return false;
	cx = num;
	args = SkipWhitespace(end);
	if (!args) return false;

	num = strtof(args, &end);
	if (args == end) return false;
	cy = num;
	args = SkipWhitespace(end);
	if (!args) return false;

	num = strtof(args, &end);
	if (args == end) return false;
	r = num;
	args = SkipWhitespace(end);
	if (!args) return false;

	char* n_fill = args;
	end = GetToken(n_fill, WHITESPACE_CHARS);
	if (end)
	{
		*(end++) = 0;
		if (SkipWhitespace(end)) return false;
	}

	SetFill(n_fill);
	return true;
}

bool Circle::CheckWithinRect(float rx1, float ry1, float rw, float rh)
{
	float rx2 = rx1 + rw;
	float ry2 = ry1 + rh;
	if (cx > rx1 && cx < rx2 &&
		cy > ry1 && cy < ry2)
	{
		if (r < (cy - ry1) &&
			r < (ry2 - cy) &&
			r < (cx - rx1) &&
			r < (rx2 - cx))
		{
			return true;
		}
	}
	return false;
}

bool Circle::CheckWithinCircle(float cx1, float cy1, float r1)
{
	float distance = ((cx1 - cx) + (cy1 - cy));
		if (distance < 0)
		{
		distance = distance - (2 * distance);
		}
		distance = sqrt(distance);
		if ((distance + r) < r1)
		{
			return true;
		}
		return false;
}