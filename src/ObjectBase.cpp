
// ObjectBase object source code.
// Coded by: Zac McClain

//** Load Dependences:
#include "ObjectBase.h"

ObjectBase::ObjectBase()
{
	position = new Point( 0,0,0 );
}


ObjectBase::ObjectBase( Point location )
{
	position = new Point( location.getX(), location.getY(), location.getZ() );

}

ObjectBase::~ObjectBase()
{
	delete position;
}

//** Functions
void ObjectBase::translate()
{
	position->glTranslate();
}

//** Getters and Setters:

//* Getters:

// Locations:
float ObjectBase::getX()
{
	return( position->getX() );
}

float ObjectBase::getY()
{
	return( position->getY() );
}

float ObjectBase::getZ()
{
	return( position->getZ() );
}

Point* ObjectBase::getLocation()
{
	return( position );
}

Point* ObjectBase::getPosition()
{
	return( position );
}

//* Setters:

// Locations:
void ObjectBase::setX( float newX )
{
	position->setX( newX );
}

void ObjectBase::setY( float newY )
{
	position->setY( newY );
}

void ObjectBase::setZ( float newZ )
{
	position->setZ( newZ );
}

void ObjectBase::setLocation( Point* newLoaction )
{
	setX( newLoaction->getX() );
	setY( newLoaction->getY() );
	setZ( newLoaction->getZ() );
}

void ObjectBase::setPosition( Point newPosition )
{
	setX( newPosition.getX() );
	setY( newPosition.getY() );
	setZ( newPosition.getZ() );
} 

// ######## END ObjectBase ########