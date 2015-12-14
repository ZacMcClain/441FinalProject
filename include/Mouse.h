// Mouse object header file.
// Coded by: Zac McClain

#ifndef MOUSE_H
#define MOUSE_H

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

class Mouse
{
	public:

	//** Public Default Constructors and Destructor:
		
		Mouse();
		~Mouse();

	//** Functions
		void update();

	//** Getters and Setters:

		// State:

		// Getters:
		GLint getLeftMouseButton();
		bool isLeftMouseButtonDown();
		bool isRightMouseButtonDown();
		bool getZoomMode();

		// Setters:
		void setLeftMouseButton( GLint newLeftMouseButton );
		void setRightMouseButton( GLint newRightMouseButton );
		void setZoomMode( bool newZoomMode );
		void toggleZoomMode();

		//** Locations:

		// Getters:
		float getX();
		float getY();

		// Setters:
		void setX( float newX );
		void setY( float newY );

	private:

	//** Variables:

		// State:
		GLint leftMouseButton;
		GLint rightMouseButton;
		bool leftButtonDown;
		bool rightButtonDown;

		// Location:
		float myX;
		float myY;
		
};

#endif // MOUSE_H