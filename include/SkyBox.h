
// SkyBox header file.
// Coded by: Zac McClain

#ifndef SKYBOX_H
#define SKYBOX_H

//** Load Dependences:

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Point.h"
#include "Vector.h"
#include <string>

class SkyBox 
{
	public:

	//** Variables:
	GLuint handles[6];

	//** Public Default Constructors and Destructor:
		
		SkyBox();
		~SkyBox();

	//** Functions:

		//* Setup

		//* Rendering
		void draw();
		void drawSkybox( int size );

		//* Updating:
		void update();

	//** Getters and Setters:

		// Getters:
		int getSize();

		// Setters:
		void setSize( int newSize );

	private:

	//** Variables:
	unsigned int size;

	//** Functions:

	protected:

	//** Variables:

	//** Functions:
	void drawSkyboxPanel( GLuint texHandle, Point point, Vector dim1, Vector dim2, Vector normal, int flippingFactor, int flippingFactor2, int size );
		
};

#endif // SKYBOX_H