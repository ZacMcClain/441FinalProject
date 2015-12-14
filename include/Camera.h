
// Camera header file.
// Coded by: Zac McClain

#ifndef CAMERA_H
#define CAMERA_H

//** Load Dependences:

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include "Point.h"
#include "Vector.h"
#include "ObjectBase.h"

#include <math.h>

enum CameraType {  
	ARCBALL,
	FREE
};

class Camera : public ObjectBase
{
	public:

	//** Variables:

	//** Public Default Constructors and Destructor:
		Camera();
		Camera( double myX, double myY, double myZ );
		Camera( float myRadius, float myTheta, float myPhi );
		Camera( double myX, double myY, double myZ, float myRadius, float myTheta, float myPhi  );
		~Camera();

	//** Functions:
		void lookAt();
		virtual void update() = 0;

	//** Getters and Setters:

		// Getters:
		Point* lookingAt();
		Point* getLookAtPoint();
		double getLookPointAt( int i );
		double getLookAtX();
		double getLookAtY();
		double getLookAtZ();
		Vector* getUpVector();
		Vector* getUp();
		Vector* getDirection();

		CameraType getType();

		float getRadius();
		float getTheta();
		float getPhi();


		// Setters:
		void setLookAtPoint( Point* newPoint );
		void setLookAtScaler( int i, double value );
		void setLookAtX( double newX );
		void setLookAtY( double newY );
		void setLookAtZ( double newZ );
		void setUpVector( Vector* newUpVector );

		void setRadius( float newRadius );
		void setTheta( float newTheta );
		void setPhi( float newPhi );

	private:

	//** Variables:

	//** Functions:

	protected:

	//** Variables:
		CameraType type;

		Point* lookAtPoint;
		Vector* upVector;
		Vector direction;

		float radius;
		float theta;
		float phi;


	//** Functions:
		void init( double myX, double myY, double myZ, float myRadius, float myTheta, float myPhi );
		void clacDirection();
		void updateDirection();
};

// Helper Functions:
void gluCamLookAt( Point* eye, Point* lookAt, Vector* up );

#endif // CAMERA_H