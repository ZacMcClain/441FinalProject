#include "Enemy.h"

Enemy::Enemy( float x, float y, float z, float shipX, float shipY ) {
    position = Point( x,y,z );
    // The ship z is locked to 0
    Point target = Point( shipX, shipY, 0.0f );
    direction = target - position;
    direction.normalize();
    // find the rotation parameters
    angle = ( 180.0 / M_PI * acos(dot(direction, Vector(0.0, 0.0, 1.0))) );
    axis = cross( Vector(0.0, 0.0, 1.0), direction );

    // generate a spin speed and random move speed
    deltaPos = rand() % 4 + 1;
    deltaRot = rand() % 6;
    // init the scaling factor default to 1;
    scale = 1;
}

// Moves towards the target
void Enemy::move() {
    position += deltaPos*direction;
    rotation += deltaRot;
}

// calls glRotatef to face the direction heading, and spins around
void Enemy::callRotate() {
	// heading rotation
    glRotatef( angle, axis.getX(), axis.getY(), axis.getZ() );
    // Spin rotation
    glRotatef( rotation, direction.getX(), direction.getY(), direction.getZ() );
}

void Enemy::calcRandAsteroidSizeScaler()
{
    int tmp = rand() % 5;
    switch( tmp ) {
        case 0:
            scale = 0.05;
            break;
        case 1:
            scale = 0.1;
            break;
        case 2:
            scale = 0.3;
            break;
        case 3:
            scale = 0.6;
            break;
        case 4:
            scale = 0.8;
            break;
    }
}