#include "stdafx.h"

#include "Utils.h"
#include "SVG.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

#include <iostream>
#include <stdlib.h>

using namespace std;


int main()
{
  SVG svg;

  while (1)
    {
      cout << "> ";
      char user_input[128];
      cin.getline(user_input, 127);

      char *command = SkipWhitespace(user_input);

      if (!command)
        {
          continue;
        }

      char *command_args = GetToken (command, WHITESPACE_CHARS);

      if (command_args)
        {
          *(command_args++) = 0;
          command_args = SkipWhitespace (command_args);
        }

      if (!strcmp(command, "open"))
        {
          if (command_args)
            {
              if (ParseMultiwordArg (&command_args))
                {
                  if (svg.Open(command_args))
                    {
                      cout << "Successfully opened \"" << svg.GetFilename() << '"' << endl;
                    }
                  else
                    {
                      cerr << "Error: Cannot open \"" << command_args << '"' << endl;
                    }
                }
            }
          else
            {
              cerr << "Error: Must specify a filename" << endl;
            }
        }
      else if (!strcmp(command, "save"))
        {
          if (svg.Save())
            {
              cout << "Successfully saved the changes to \"" << svg.GetFilename() << '"' << endl;
            }
          else
            {
              cerr << "Error: Cannot save file" << endl;
            }
        }
      else if (!strcmp(command, "saveas"))
        {
          if (command_args)
            {
              if (ParseMultiwordArg (&command_args))
                {
                  if (svg.SaveAs(command_args))
                    {
                      cout << "Successfully saved the changes to \"" << command_args << '"' << endl;
                    }
                  else
                    {
                      cerr << "Error: Cannot save to \"" << command_args << '"' << endl;
                    }
                }
            }
          else
            {
              cerr << "Error: Must specify a filename" << endl;
            }
        }
      else if (!strcmp(command, "close"))
        {
          if (!svg.Close())
            {
              cerr << "Error: Cannot close file" << endl;
            }
        }
      else if (!strcmp(command, "print"))
        {
          svg.Print();
        }
	  else if (!strcmp(command, "create"))
	  {
		  if (command_args)
		  {
			  char* shape_name = command_args;
			 command_args = GetToken(command_args, " ");
			 if (command_args)
			 {
				 *(command_args++) = 0;
				 command_args = SkipWhitespace(command_args);
				 if (command_args)
				 {
					 bool success;
					 if (!strcmp(shape_name, "rectangle"))
					 {
						 Shape* new_shape = new Rectangle;
						 success = new_shape->Create(command_args);
						 svg.Insert(new_shape);
					 }
					 else if (!strcmp(shape_name, "circle"))
					 {
						 Shape* new_shape = new Circle;
						 success = new_shape->Create(command_args);
						 svg.Insert(new_shape);
					 }
					 else if (!strcmp(shape_name, "line"))
					 {
						 Shape* new_shape = new Line;
						 success = new_shape->Create(command_args);
						 svg.Insert(new_shape);
					 }
					 else
					 {
						 cerr << "Error: Unknown shape specified" << endl;
					 }

					 if (!success)
					 {
						 cerr << "Error: Invalid shape args" << endl;
					 }
				 }
				 else
				 {
					 cerr << "Error: No shape arguments specified" << endl;
				 }
			 }
			 else
			 {
				 cerr << "Error: No shape specified" << endl;
			 }
		  }
		  else
		  {
			  cerr << "Error: Nothing entered" << endl;
		  }
	  }
      else if (!strcmp(command, "erase"))
        {
          if (command_args)
            {
              char *parse_end;
              int shape_index = (int) strtol(command_args, &parse_end, 10) - 1;

              if (parse_end == command_args)
                {
                  cerr << "Error: Invalid index number" << endl;
                }
              else if (!SkipWhitespace(command_args))
                {
                  cerr << "Error: Excessive arguments" << endl;
                }
              else
                {
                  svg.Erase(shape_index);
                }
            }
          else
            {
              cerr << "Error: You must specify an index number" << endl;
            }
        }
      else if (!strcmp(command, "translate"))
        {
          if (command_args)
            {
              bool error = false;

              float horizontal = 0;
              bool  horizontal_set = 0;
              float vertical = 0;
              bool  vertical_set = 0;

              while (!error && (command_args = SkipWhitespace(command_args)))
                {

                  if (!ParseFloatArg (&command_args, &error, "horizontal=",
                                      &horizontal, &horizontal_set) &&
                      !ParseFloatArg (&command_args, &error, "vertical=",
                                      &vertical, &vertical_set))
                    {
                      cerr << "Error: Unrecognized translate argument" << endl;
                      error = true;
                    }
                }

              if (!error && (horizontal_set || vertical_set))
                {
                  svg.Translate(horizontal, vertical);
                }
            }
          else
            {
              cerr << "Error: You must specify a horizontal and/or vertical translation" << endl;
            }
        }
	  else if (!strcmp(command, "within"))
	  {
		  if (command_args)
		  {
			  svg.CheckWithin(command_args);
		  }
		  else
		  {
			  cerr << "Error: Must specify rectangle or circle" << endl;
		  }
	  }
      else if (!strcmp(command, "exit"))
        {
          break;
        }
      else
        {
          cerr << "Error: Invalid command" << endl;
        }
    }

  return 0;
}
