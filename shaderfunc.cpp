#include "shaderfunc.h"

/*
 * Reads a file into a cstring.
 * Remember to delete once you're done using the result!
*/
char* ReadFile(char* file)
{
  int fileSize;
  char* buf;
  //open file
  std::fstream f (file, std::fstream::in | std::fstream::app | std::fstream::ate);
  //check to make sure it actually opened
  if (!f) Fatal("Failed to open file.");
  //get file size
  fileSize = f.tellg();
  //reset to start of file
  f.seekg(0);
  //allocate space for file
  buf = new char[fileSize + 1]; //add one for terminate
  //read into buffer
  for(int n=0; n<fileSize; n++) {
    f.get(buf[n]);
  }
  //terminate buffer
  buf[fileSize] = 0;
  //close file
  f.close();
  //return buffer
  return buf;
}

/*
 * Creates a shader of type out of given file.
*/
int MakeShader(GLenum type, char* file)
{
  //initialize shader
  int shader = glCreateShader(type);
  //load shader source code
  char* source = ReadFile(file);
  glShaderSource(shader,1,(const char**)&source,NULL);
  //free memory back up
  delete[] source;
  //compile shader
  glCompileShader(shader);
  //return shader
  return shader;
}

//indices for particle shader arrays
#define VELOCITY_ARRAY 3
#define END_ARRAY 4
#define START_ARRAY 5

/*
 * Creates a shader program with given vertex and fragment shaders
*/
int MakeShaderProg(char* vertexFile, char* fragmentFile)
{
  //initialize program
  int program = glCreateProgram();
  //initialize and compile both shaders
  int vert;
  int frag;
  if(vertexFile) vert = MakeShader(GL_VERTEX_SHADER, vertexFile);
  if(fragmentFile) frag = MakeShader(GL_FRAGMENT_SHADER, fragmentFile);
  //attach shaders to program
  if(vertexFile) glAttachShader(program,vert);
  if(fragmentFile) glAttachShader(program,frag);
  //set attribute locations
  glBindAttribLocation(program,VELOCITY_ARRAY,"Vel");
  glBindAttribLocation(program,END_ARRAY,"End");
  glBindAttribLocation(program,START_ARRAY,"Start");
  //link program
  glLinkProgram(program);
  //return shader program
  return program;
}
