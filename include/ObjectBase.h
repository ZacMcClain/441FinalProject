
// ObjectBase header file.
// Coded by: Zac McClain

#ifndef OBJECTBASE_H
#define OBJECTBASE_H

//** Load Dependences:

#include "Point.h"

class ObjectBase
{
	public:

	//** Variables:

	//** Public Default Constructors and Destructor:
		
		ObjectBase();
		ObjectBase( Point location );
		~ObjectBase();

	//** Functions:

	//** Getters and Setters:

		//* Getters:

		// Locations:
		float getX();
		float getY();
		float getZ();
		Point* getLocation();
		Point* getPosition();

		//* Setters:

		// Locations:
		void setX( float newX );
		void setY( float newY );
		void setZ( float newZ );
		void setLocation( Point* newLoaction );
		void setPosition( Point newPosition );

	//** object detentions

	private:

	//** Variables:

	//** Functions:

	protected:

	//** Variables:
		Point* position;

	//** Functions:

		
};

#endif // OBJECTBASE_H