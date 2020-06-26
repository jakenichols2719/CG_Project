#include "CSCIx229.h"
#include <fstream>
#include <iostream>

//read file into cstring
char* ReadFile(char* file);
//create shader program of type
int MakeShader(GLenum type, char* file);
//create vertex and fragment shader from files
int MakeShaderProg(char* vFile, char* fFile);
