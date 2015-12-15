#pragma once

#include <GL/glew.h>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Point.h"
#include <stdlib.h>
#include <math.h>

class Enemy {
public:
    enum Type { SHIP, ROCK };
    Type type;

    Enemy(float x, float y, float z, float shipX, float shipY);

    // Moves towards the target
    void move();
    // calls glRotatef to face the direction heading
    void callRotate();

    float getX() { return position.getX(); }
    float getY() { return position.getY(); }
    float getZ() { return position.getZ(); }

    Point getPosition() { return position; }

    float getScale() { return( scale ); }

    void calcRandAsteroidSizeScaler();
private:
    Point position;
    // Towards ship at the time of this enemy spawning
    Vector direction;
    // Angle and axis to rotate towards heading
    float angle;
    Vector axis;
    // Rotation along heading for a little spinning animation
    float rotation;
    // Random rotation update speed
    float deltaRot;
    // Random move speed
    float deltaPos;
    // Scale
    float scale;
};
