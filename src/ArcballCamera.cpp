
// ArcballCamera object source code.
// Coded by: Zac McClain

//** Load Dependences:

#include "ArcballCamera.h"

#define PI 3.14159265358979323846264338327950288

//** Public Default Constructors and Destructor:
		
ArcballCamera::ArcballCamera( float myRadius, float myTheta, float myPhi ) : Camera( myRadius, myTheta, myPhi )
{
    this->type = ARCBALL;
	update();
}
		
ArcballCamera::~ArcballCamera()
{}

//** Functions:
void ArcballCamera::update()
{
	this->boundRadius();
	this->computePosition();
}

void ArcballCamera::computePosition()
{
	position->setX( (radius * sinf(theta)*sinf(phi)) + lookAtPoint->getX() );
    position->setY( (radius * -cosf(phi)) + lookAtPoint->getY() );
    position->setZ( (radius * -cosf(theta)*sinf(phi)) + lookAtPoint->getZ() );
}

void ArcballCamera::boundPhi()
{
	if( phi <= 0 )
        phi = 0+0.001;
   	if( phi >= PI)
        phi = PI-0.001;
}


void ArcballCamera::boundRadius()
{
    if( radius < 2.0 )
        radius = 2.0;
    if( radius > 150.0 )
        radius = 150.0;
}


//** Getters and Setters:

// Getters:

// Setters:

