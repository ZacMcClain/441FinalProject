
// Ship header file.
// Coded by: Zac McClain

#ifndef SHIP_H
#define SHIP_H

//** Load Dependences:
#include "ObjectBase.h"
#include "Object.h"

class Ship : public ObjectBase, public Object
{
	public:

	//** Variables:

	//** Public Default Constructors and Destructor:
		
		Ship();
		Ship( string filename );
		~Ship();

	//** Functions:
		void moveUp( bool upKeys );
		void moveDown( bool downKeys );
		void moveLeft( bool leftKeys );
		void moveRight( bool rightKeys );

	//** Getters and Setters:

		// Getters:

		// Setters:

	private:

	//** Variables:

	//** Functions:

	protected:

	//** Variables:
		// min and max used to clamp the ship to the screen
		float maxY;
    	float minY;
    	float maxX;
    	float minX;

    	// Move ship to edge gradually if key pressed
    	float delta;

	//** Functions:
    	void setup();
		
};

#endif // SHIP_H