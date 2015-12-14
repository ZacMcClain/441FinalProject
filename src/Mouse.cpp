// Mouse object source code.
// Coded by: Zac McClain

//** Load Dependences:
#include "Mouse.h"

//** Public Default Constructors and Destructor:
Mouse::Mouse(){
	myX = 0;
	myY = 0;
	leftButtonDown = false;
	rightButtonDown = false;
}

Mouse::~Mouse() {}

//** Functions
void Mouse::update()
{
	if( leftMouseButton == GLUT_DOWN )  {
		leftButtonDown = true;
	} else {
		leftButtonDown = false;
	}

	if( rightMouseButton == GLUT_DOWN ) {
		rightButtonDown = true;
	} else {
		rightButtonDown = false;
	}
}

//** Getters and Setters:

// State:

// Getters:
GLint Mouse::getLeftMouseButton()
{
	return( leftMouseButton );
}


bool Mouse::isLeftMouseButtonDown()
{
	return( leftButtonDown );
}

bool Mouse::isRightMouseButtonDown()
{
	return( rightButtonDown );
}

// Setters:
void Mouse::setLeftMouseButton( GLint newLeftMouseButton )
{
	leftMouseButton = newLeftMouseButton;
	update();
}

void Mouse::setRightMouseButton( GLint newRightMouseButton )
{
	rightMouseButton = newRightMouseButton;
	update();
}

//** Locations:

// Getters:
float Mouse::getX()
{
	return( myX );
}

float Mouse::getY()
{
	return( myY );
}

// Setters
void Mouse::setX( float newX )
{
	myX = newX;
}

void Mouse::setY( float newY )
{
	myY = newY;
}