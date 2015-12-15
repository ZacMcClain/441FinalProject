#include "Enemy.h"

Enemy::Enemy(float x, float y, float z, float shipX, float shipY) {
    position = Point(x,y,z);
    // The ship z is locked to 0
    Point target = Point(shipX, shipY, 0.0f);
    direction = target - position;
    direction.normalize();
    // find the rotation parameters
    angle = 180.0 / M_PI * acos(dot(direction, Vector(0.0, 0.0, 1.0)));
    axis = cross(Vector(0.0, 0.0, 1.0), direction);
}

// Moves towards the target
void Enemy::move() {
    position += 3*direction;
}

// calls glRotatef to face the direction heading
void Enemy::callRotate() {
    glRotatef(angle, axis.getX(), axis.getY(), axis.getZ());
}
