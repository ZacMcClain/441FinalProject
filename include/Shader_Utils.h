#ifndef __SHADER_UTILS_H__
#define __SHADER_UTILS_H__

#include <GL/glew.h>

#include <string>
using namespace std;

// PrintOpenGLInfo() ////////////////////////////////////////////////////////////
//
//  Print the OpenGL version and attribute info to the screen
//
////////////////////////////////////////////////////////////////////////////////
void PrintOpenGLInfo();

// printLog() //////////////////////////////////////////////////////////////////
//
//  Check for errors from compiling or linking a vertex/fragment/shader program
//	Prints to terminal
//
////////////////////////////////////////////////////////////////////////////////
void printLog( GLuint handle, string filename );

// createShaderProgram() ///////////////////////////////////////////////////////
//
//  Compile and Register our Vertex and Fragment Shaders
//
////////////////////////////////////////////////////////////////////////////////
GLuint createShaderProgram( char *vertexShaderFilename, char *fragmentShaderFilename, string programName );

#endif