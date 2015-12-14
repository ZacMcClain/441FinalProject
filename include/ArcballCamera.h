
// ArcballCamera header file.
// Coded by: Zac McClain

#ifndef ARCBALLCAMERA_H
#define ARCBALLCAMERA_H

//** Load Dependences:
#include "Camera.h"


class ArcballCamera : public Camera
{
	public:

	//** Variables:

	//** Public Default Constructors and Destructor:
		
		ArcballCamera( float myRadius, float myTheta, float myPhi );
		~ArcballCamera();

	//** Functions
		void update();
		void boundPhi();

		void boundRadius();
		void computePosition();

	//** Getters and Setters:

		// Getters:

		// Setters:

	private:

	//** Variables:

	//** Functions:

	protected:

	//** Variables:

	//** Functions:
		
};

#endif // ARCBALLCAMERA_H