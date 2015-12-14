
// ObjectBase object source code.
// Coded by: Zac McClain

//** Load Dependences:

#include "Camera.h"

//** Public Default Constructors and Destructor:

Camera::Camera()
{
	init( 0.0, 10.0, 35.0, 35.0f, 2.89f, 2.0f );
}

Camera::Camera( float myRadius, float myTheta, float myPhi )
{
	init( 0.0, 10.0, 35.0, myRadius, myTheta, myPhi );
}
		
Camera::Camera(  double myX, double myY, double myZ  )
{
	init( myX, myY, myZ, 35.0f, 2.89f, 2.0f );
}

Camera::Camera(  double myX, double myY, double myZ, float myRadius, float myTheta, float myPhi  )
{
	init( myX, myY, myZ, myRadius, myTheta, myPhi );
}
		
Camera::~Camera()
{
	delete position;
	delete lookAtPoint;
	delete upVector;
}

//** Functions:

void Camera::init( double myX, double myY, double myZ, float myRadius, float myTheta, float myPhi )
{
	this->position = new Point( myX, myY, myZ );
	this->lookAtPoint = new Point( 0,0,0 );
	this->upVector = new Vector( 0,1,0 );
	this->radius = myRadius;
	this->theta = myTheta;
	this->phi = myPhi;
	clacDirection();
}

void Camera::lookAt()
{
	gluCamLookAt( this->position, this->lookAtPoint, this->upVector );
}

void Camera::clacDirection()
{
	// the view
	direction = vectorFrom( position, lookAtPoint );
	direction.normalize();
}

void Camera::updateDirection()
{
	updateVector( &direction, position, lookAtPoint );
	direction.normalize();
}

//** Getters and Setters:

// Getters:
Point* Camera::lookingAt()
{
	return( getLookAtPoint() );
}

Point* Camera::getLookAtPoint()
{
	return( lookAtPoint );
}

double Camera::getLookPointAt( int i )
{
	return( lookAtPoint->at(i) );
}

double Camera::getLookAtX()
{
	return( lookAtPoint->getX() );
}

double Camera::getLookAtY()
{
	return( lookAtPoint->getY() );
}

double Camera::getLookAtZ()
{
	return( lookAtPoint->getZ() );
}


Vector* Camera::getUpVector()
{
	return( upVector );
}
Vector* Camera::getUp()
{
	return( getUpVector() );
}

CameraType Camera::getType()
{
	return( this->type );
}

Vector* Camera::getDirection()
{
	return( &direction );
}

float Camera::getRadius()
{
	return( radius );
}

float Camera::getTheta()
{
	return( theta );
}

float Camera::getPhi()
{
	return( phi );
}

// Setters:
void Camera::setLookAtPoint( Point* newPoint )
{
	this->lookAtPoint = newPoint;
	updateDirection();
}

void Camera::setLookAtScaler( int i, double value )
{
	switch( i )  {
		case 0:
			this->lookAtPoint->setX( value );
		break;
		case 1:
			this->lookAtPoint->setY( value );
		break;
		case 2:
			this->lookAtPoint->setZ( value );
		break;
	}
	updateDirection();
}

void Camera::setLookAtX( double newX )
{
	this->lookAtPoint->setX( newX );
	updateDirection();
}

void Camera::setLookAtY( double newY )
{
	this->lookAtPoint->setY( newY );
	updateDirection();
}

void Camera::setLookAtZ( double newZ )
{
	this->lookAtPoint->setZ( newZ );
	updateDirection();
}


void Camera::setUpVector( Vector* newUpVector )
{
	this->upVector = newUpVector;
	updateDirection();
}

void Camera::setTheta( float newTheta )
{
	this->theta = newTheta;
	updateDirection();
}

void Camera::setRadius( float newRadius )
{
	this->radius = newRadius;
}

void Camera::setPhi( float newPhi )
{
	this->phi = newPhi;
	updateDirection();
	// boundPhi();
}

void gluCamLookAt( Point* eye, Point* lookAt, Vector* up ) {
    gluLookAt( 
    	eye->getX(), 
    	eye->getY(), 
    	eye->getZ(),
       	lookAt->getX(), 
       	lookAt->getY(), 
       	lookAt->getZ(),
        up->getX(), 
        up->getY(), 
        up->getZ() 
    );
}
