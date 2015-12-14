// Color Object source code
// Coded by: Zac McClain

//** Load Dependences:
#include "Color.h"

//** Public Default Constructors and Destructor

Color::Color()
{
	// default to white
	red = 0;
	green = 0;
	blue = 0;
	a = 1;
}


Color::Color( float initRed, float initGreen, float initBlue )
{
	this->red = initRed;
	this->green = initGreen;
	this->blue = initBlue;
	this->a = 1;
}

Color::Color( float initRed, float initGreen, float initBlue, float initA )
{
	this->red = initRed;
	this->green = initGreen;
	this->blue = initBlue;
	this->a = initA;
}

Color::~Color() {}

//** Helper methods:

void Color::setCurrent() 
{
	glColor4f( red, green, blue, a );
}

//** Getters and Setters:

//** Locations:

// Getters:
float Color::getRed()
{
	return( red );
}
		
float Color::getGreen(){
	return( green );
}

float Color::getBlue()
{
	return( blue );
}

float Color::getA()
{
	return( a );
}

// Setters:
void Color::setRed( float newRed )
{
	this->red = newRed;
}

void Color::setGreen( float newGreen )
{
	this->green = newGreen;
}

void Color::setBlue( float newBlue )
{
	this->blue = newBlue;
}

void Color::setA( float newA )
{
	this->a = newA;
}
