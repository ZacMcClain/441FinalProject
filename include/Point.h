#ifndef _POINT_H_
#define _POINT_H_ 1

#include <math.h>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "PointBase.h"
#include "Vector.h"
#include "Matrix.h"
#include <assert.h>

class Point : public PointBase {
public:

	// CONSTRUCTORS / DESTRUCTORS
    Point();

	Point( int a, int b, int c );
    Point( double a, double b, double c );
    Point( float a, float b, float c );

	// MISCELLANEOUS
    double at(int i);

    /* call glVertex3f( a, b, c ) */
    void glVertex();

    /* call glTexCoord2f( a, b ) */
	void glTexCoord();

	/* call glTranslatef( a, b, c ) */
	void glTranslate();

	Point& operator+=(Vector rhs);
	Point& operator-=(Vector rhs);
	Point& operator*=(float rhs);
	Point& operator/=(float rhs);

};

// RELATED OPERATORS

Point operator*(Point a, float f);
Point operator/(Point a, float f);
Point operator/(float f, Point p);
Point operator*(float f, Point a);
Vector operator-(Point a, Point b);
Point operator+(Point a, Vector b);
Point operator+(Vector a, Point b);

Point operator+(Point a, Point b);
Point operator*(Matrix m, Point a);
bool operator==(Point a, Point b);
bool operator!=(Point a, Point b);

void glTranslatef( Point p );
void glTranslatef( Point* p );
Vector vectorFrom( Point a, Point b );
Vector vectorFrom( Point* a, Point* b );
void updateVector( Vector* oldVector, Point* a, Point* b );

#endif
