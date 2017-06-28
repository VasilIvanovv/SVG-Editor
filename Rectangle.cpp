#include "stdafx.h"
#include "Utils.h"
#include "Rectangle.h"
#include "Shape.h"

#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

Rectangle::Rectangle() : Shape()
{
}

Rectangle::Rectangle(char *attributes) : Shape()
{
  ParseAttributes(attributes);
}

Rectangle::~Rectangle()
{
  // cout << "Rectangle::~Rectangle()" << endl;
}

void Rectangle::AddAttrib(char* name, char* value)
{
  if (!strcmp(name, "x"))
    {
      x = (float) atof(value);
    }
  else if (!strcmp(name, "y"))
    {
      y = (float) atof(value);
    }
  else if (!strcmp(name, "width"))
    {
      width = (float) atof(value);
    }
  else if (!strcmp(name, "height"))
    {
      height = (float) atof(value);
    }
  else if (!strcmp(name, "fill"))
    {
      SetFill(value);
    }
}

void Rectangle::Translate(float horizontal, float vertical)
{
  x += horizontal;
  y += vertical;
}

void Rectangle::Print()
{
  cout << "rectangle "
       << x << ' '
       << y << ' '
       << width << ' '
       << height << ' '
       << fill << endl;
}

void Rectangle::Save(ofstream *svgfile)
{
  *svgfile << "<rect x=\"" << x
           << "\" y=\"" << y
           << "\" width=\"" << width
           << "\" height=\"" << height
           << "\" fill=\"" << fill
           << "\" />\n";
}

bool Rectangle::Create(char* args)
{
	args = SkipWhitespace(args);
	if (!args) return false;

	char* end;
	float num;

	num = strtof(args, &end);
	if (args == end) return false;
	x = num;
	args = SkipWhitespace(end);
	if (!args) return false;
	
	num = strtof(args, &end);
	if (args == end) return false;
	y = num;
	args = SkipWhitespace(end);
	if (!args) return false;

	num = strtof(args, &end);
	if (args == end) return false;
	width = num;
	args = SkipWhitespace(end);
	if (!args) return false;

	num = strtof(args, &end);
	if (args == end) return false;
	height = num;
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

bool Rectangle::CheckWithinRect(float rx1, float ry1, float rw, float rh)
{
	float x1 = x;
	float y1 = y;
	float x2 = x + width;
	float y2 = y + height;

	float rx2 = rx1 + rw;
	float ry2 = ry1 + rh;

	if (x1 >= rx1 &&
		x2 <= rx2 &&
		y1 >= ry1 &&
		y2 <= ry2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Rectangle::CheckWithinCircle(float cx, float cy, float r)
{
	float x1 = x;
	float y1 = y;
	float x2 = x1 + width;
	float y2 = y1 + height;
	if ((x1 - cx)*(x1 - cx) + (y1 - cy)*(y1 - cy) < r*r &&
		(x2 - cx)*(x2 - cx) + (y1 - cy)*(y1 - cy) < r*r &&
		(x2 - cx)*(x2 - cx) + (y2 - cy)*(y2 - cy) < r*r &&
		(x1 - cx)*(x1 - cx) + (y2 - cy)*(y2 - cy) < r*r)
	{
		return true;
	}
	return false;
}