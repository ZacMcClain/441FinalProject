// Color object header file.
// Coded by: Zac McClain

#ifndef COLOR_H
#define COLOR_H

//** Load Dependences:
#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					    // else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

class Color
{
	public:

	//** Public Default Constructors and Destructor:
		Color();
		Color( float initRed, float initGreen, float initBlue );
		Color( float initRed, float initGreen, float initBlue, float initA );
		~Color();

	//** Helper Methods:

		void setCurrent();

	//** Getters and Setters:

		// Getters:
		float getRed();
		float getGreen();
		float getBlue();
		float getA();

		// Setters:
		void setRed( float newRed );
		void setGreen( float newGreen );
		void setBlue( float newBlue );
		void setA( float newA );


	private:

	//** Variables:
		float red;
		float green;
		float blue;
		float a;
		
};

#endif // COLOR_H