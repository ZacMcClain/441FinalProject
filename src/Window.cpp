
// Window object source code.
// Coded by: Zac McClain

//** Load Dependences:

#include "Window.h"

//** Public Default Constructors and Destructor:
		
Window::Window()
{
	setDimensions( 640, 400 );
}


Window::Window( int myWidth, int myHeight )
{
	setDimensions( myWidth, myHeight );
}
		
Window::~Window()
{}

//** Functions:
void Window::updateAspectRatio()
{
	aspectRatio = ( width / (float)height );
}

//** Getters and Setters:

// Getters:
int Window::getHeight()
{
	return( height );
}
		
int Window::getWidth()
{
	return( width );
}

float Window::getAspectRatio()
{
	return( aspectRatio );
}
// Setters:
void Window::setHeight( int newHeight )
{
	this->height = newHeight;
	updateAspectRatio();
}
		
void Window::setWidth( int newWidth )
{
	this->width = newWidth;
	updateAspectRatio();
}

void Window::setDimensions( int newWidth, int newHeight )
{
	this->height = newHeight;
	this->width = newWidth;
	updateAspectRatio();
}
