#include "stdafx.h"
#include "Utils.h"

#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

char* GetToken(char* str, const char *search)
{
  int search_len = strlen (search);
  while (*str)
    {
      for (int i = 0; i < search_len; ++i)
        {
          if (*str == search[i])
            {
              return str;
            }
        }
      ++str;
    }

  return 0;
}

char* SkipWhitespace(char* str)
{
  while (*str)
    {
      if (!isspace(*str))
        {
          return str;
        }
      ++str;
    }

  return 0;
}


bool ParseFloatArg(char** command_args, bool* error,
                   const char* name, float* value, bool* set)
{
  bool matches = false;
  int name_len = strlen(name);

  if (!strncmp (*command_args, name, name_len))
    {
      matches = true;

      if (*set)
        {
          cerr << "Error: Duplicated " <<  name << " argument" << endl;
          *error = true;
        }
      else
        {
          *set = true;

          *command_args += name_len;
          char* end;
          *value = strtof (*command_args, &end);

          if (*command_args == end)
            {
              cerr << "Error: Invalid " << name << " value" << endl;
              *error = true;
            }
          else
            {
              *command_args = end;
            }
        }
    }

  return matches;
}
 

bool ParseMultiwordArg (char** command_args)
{
  bool success = true;

  if (**command_args == '"')
    {
      ++(*command_args);
      char* end = GetToken (*command_args, "\"");

      if (!end)
        {
          cerr << "Error: No closing quotations" << endl;
          success = false;
        }
      else if (SkipWhitespace (end + 1))
        {
          cerr << "Error: Excessive arguments" << endl;
          success = false;
        }
      else
        {
          *end = 0;
        }
    }
  else
    {
      char *end = GetToken (*command_args, WHITESPACE_CHARS);

      if (end && SkipWhitespace(end))
        {
          cerr << "Error: Excessive arguments" << endl;
          success = false;
        }
    }

  return success;
}
