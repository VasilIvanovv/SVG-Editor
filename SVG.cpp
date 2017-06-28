#include "stdafx.h"
#include "SVG.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <assert.h>

using namespace std;

SVG::SVG()
  : filename(NULL),
    shapes(NULL),
    shapes_count(0),
    shapes_size(8)
{
	shapes = new Shape*[shapes_size];
}

char* SVG::GetFilename()
{
  return filename;
}


SVG::SVG(const SVG & other)
{
	Copy(other);
}

SVG::~SVG()
{
	DeleteShapes();
}

SVG & SVG::operator=(const SVG & other)
{
	if (this != &other)
	{
		DeleteShapes();
		Copy(other);
	}
	return *this;
}


void SVG::DeleteShapes()
{
	for (int i = 0; i < shapes_count; i++)
	{
		delete shapes[i];
	}
	delete[] shapes;
}


void SVG::Copy(const SVG & other)
{
	shapes_count = other.shapes_count;
	shapes_size = other.shapes_size;
	for (int i = 0; i < other.shapes_count; i++)
	{
		Insert(other.shapes[i]);
	}
}

bool SVG::Open(const char* n_filename)
{
  delete[] filename;
  int filename_len = strlen(n_filename);
  filename = new char[filename_len + 1];
  strcpy_s (filename,filename_len + 1, n_filename);

  ifstream file(filename, ios::binary | ios::ate);

  if (!file)
    {
      return false;
    }

  unsigned int filesize = (unsigned int) file.tellg();
  file.seekg(0, ios::beg);
  char* file_buffer = new char[filesize + 1];
  file.read(file_buffer, filesize);
  file.close();
  file_buffer[filesize] = 0;

  if (!shapes)
  {
	  shapes_size = 8;
	  shapes = new Shape*[shapes_size];
  }

  char* iter = file_buffer;

  while ((iter = GetToken(iter, "<")))
    {
      char* tag_name = ++iter;
      if (tag_name[0] == '/') continue; // It's a closing tag

      char* attributes = NULL;
      iter = GetToken(tag_name, ">"WHITESPACE_CHARS);

      if (*iter == '>')
        {
          if (iter[-1] == '/') iter[-1] = 0;
          ++iter;
        }
      else
        {
          *(iter++) = 0;
          iter = SkipWhitespace(iter);

          if (*iter == '/')
            {
              ++iter;
              assert(*iter = '>');
              ++iter;
            }
          else if (*iter == '>')
            {
              ++iter;
            }
          else
            {
              attributes = iter;
              iter = GetToken(iter, ">");

              if (iter[-1] == '/') iter[-1] = 0;
              else *iter = 0;

              ++iter;
            }
        }

      if (!strcmp(tag_name, "rect"))
        {
          Insert(new Rectangle(attributes));
        }
      else if (!strcmp(tag_name, "circle"))
        {
          Insert(new Circle(attributes));
        }
      else if (!strcmp(tag_name, "line"))
        {
          Insert(new Line(attributes));
        }
    }

  delete[] file_buffer;

  return true;
}

bool SVG::SaveAs(const char* save_filename)
{
  ofstream file(save_filename, ios::binary);

  if (!file)
    {
      return false;
    }

  file << ("<?xml version=\"1.0\" standalone=\"no\"?>\n"
           "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n"
           " \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n"
           "<svg>\n");

  for (int i = 0; i < shapes_count; i++)
    {
      file << "  ";
      shapes[i]->Save(&file);
    }

  file << "</svg>\n";

  file.close();

  return true;
}

bool SVG::Save()
{
  if (!filename)
    {
      return false;
    }

  return SaveAs(filename);
}

bool SVG::Close()
{
  if (!filename)
    {
      return false;
    }

  cout << "Successfully closed \"" << filename << '"' << endl;

  delete[] filename;
  filename = NULL;
  delete[] shapes;
  shapes = NULL;
  shapes_count = 0;

  return true;
}

void SVG::Print()
{
  for (int i = 0; i < shapes_count; ++i)
    {
      cout << i + 1 << ". ";
      shapes[i]->Print();
    }
}

void SVG::Resize(int n_shapes_size)
{
  shapes_size = n_shapes_size;

  Shape **new_shapes = new Shape*[shapes_size];

  for (int i = 0; i < shapes_count; i++)
    {
      new_shapes[i] = shapes[i];
    }

  delete[] shapes;
  shapes = new_shapes;
}

void SVG::Insert(Shape *new_shape)
{
  if (shapes_count >= shapes_size)
    {
      Resize(shapes_size * 2);
    }

  shapes[shapes_count++] = new_shape;
}

void SVG::Erase(int index)
{
  if (index >= 0 && index < shapes_count)
    {
      --shapes_count;
      delete shapes[index];

      for (int i = index; i < shapes_count; ++i)
        {
          shapes[i] = shapes[i + 1];
        }

      if (shapes_count <= shapes_size / 4)
        {
          Resize(shapes_size / 2);
        }
    }
  else
    {
      cerr << "Error: Invalid erase index" << endl;
    }
}

void SVG::Translate(float horizontal, float vertical)
{
  for (int i = 0; i < shapes_count; i++)
    {
      shapes[i]->Translate(horizontal, vertical);
    }
}

void SVG::CheckWithin(char* args)
{
	if (!strncmp(args, "rectangle", 9))
	{
		args = GetToken(args, " ");
		if (!args)
		{
			cerr << "Error: Invalid rectangle arguments" << endl;
			return;
		}

		char* end;
		float x = strtof(args, &end);
		if (args == end)
		{
			cerr << "Error: Invalid rectangle x argument" << endl;
			return;
		}

		args = SkipWhitespace(end);
		if (!args)
		{
			cerr << "Error: Invalid rectangle arguments" << endl;
			return;
		}
		float y = strtof(args, &end);
		if (args == end)
		{
			cerr << "Error: Invalid rectangle y argument" << endl;
			return;
		}

		args = SkipWhitespace(end);
		if (!args)
		{
			cerr << "Error: Invalid rectangle arguments" << endl;
			return;
		}
		float width = strtof(args, &end);
		if (args == end)
		{
			cerr << "Error: Invalid rectangle width argument" << endl;
			return;
		}

		args = SkipWhitespace(end);
		if (!args)
		{
			cerr << "Error: Invalid rectangle arguments" << endl;
			return;
		}
		float height = strtof(args, &end);
		if (args == end)
		{
			cerr << "Error: Invalid rectangle height argument" << endl;
			return;
		}

		if (SkipWhitespace(end))
		{
			cerr << "Error: Invalid rectangle arguments" << endl;
			return;
		}

		for (int i = 0; i < shapes_count; i++)
		{
			if (shapes[i]->CheckWithinRect(x, y, width, height))
			{
				cout << i + 1 << ". ";
				shapes[i]->Print();
			}
		}
	}
	else if (!strncmp(args, "circle", 6))
	{
		args = GetToken(args, " ");
		if (!args)
		{
			cerr << "Error: Invalid circle arguments" << endl;
			return;
		}

		char* end;
		float cx = strtof(args, &end);
		if (args == end)
		{
			cerr << "Error: Invalid circle cx argument" << endl;
			return;
		}

		args = SkipWhitespace(end);
		if (!args)
		{
			cerr << "Error: Invalid circle arguments" << endl;
			return;
		}
		float cy = strtof(args, &end);
		if (args == end)
		{
			cerr << "Error: Invalid circle cy argument" << endl;
			return;
		}

		args = SkipWhitespace(end);
		if (!args)
		{
			cerr << "Error: Invalid circle arguments" << endl;
			return;
		}
		float r = strtof(args, &end);
		if (args == end)
		{
			cerr << "Error: Invalid circle radius argument" << endl;
			return;
		}

		if (SkipWhitespace(end))
		{
			cerr << "Error: Invalid circle arguments" << endl;
			return;
		}

		for (int i = 0; i < shapes_count; i++)
		{
			if (shapes[i]->CheckWithinCircle(cx, cy, r))
			{
				cout << i + 1 << ". ";
				shapes[i]->Print();
			}
		}
	}
	else
	{
		cerr << "Error: Invalid within shape" << endl;
	}
}