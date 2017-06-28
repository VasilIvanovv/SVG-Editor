#pragma once


#define WHITESPACE_CHARS " \n\r\t\v\f"

char* GetToken(char*, const char*);
char* SkipWhitespace(char *);
bool ParseFloatArg(char**, bool*, const char*, float*, bool*);
bool ParseMultiwordArg (char**);
