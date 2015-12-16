
// Ship object source code.
// Coded by: Zac McClain

//** Load Dependences:
#include "Ship.h"

//** Public Default Constructors and Destructor:
		
Ship::Ship()
{
	setup();
}

Ship::Ship( string filename ) : Object( filename )
{
	setup();
}
		
Ship::~Ship()
{}

//** Functions:
void Ship::setup()
{
	maxY = 10;
    minY = -12;
    maxX = 15;
    minX = -15;

    delta = 0.3;

    life = maxLife = 1000;
}

void Ship::moveUp( bool upKeys )
{
	if( upKeys ) {
        setY( getY() + delta );
        setY( fmax(minY, fmin(getY(), maxY)) );
    }
}

void Ship::moveDown( bool downKeys )
{
	if( downKeys ) {
        setY( getY() - delta );
        setY( fmax(minY, fmin(getY(), maxY)) );
    }

}

void Ship::moveLeft( bool leftKeys )
{
	if( leftKeys ) {
        setX( getX() + delta );
        setX( fmax(minX, fmin(getX(), maxX)) );
    }
}

void Ship::moveRight( bool rightKeys )
{
	if( rightKeys ) {
        setX( getX() - delta );
        setX( fmax(minX, fmin(getX(), maxX)) );
    }
}

//** Getters and Setters:

// Getters:

// Setters:
