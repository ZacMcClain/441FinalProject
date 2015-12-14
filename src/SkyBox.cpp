
// SkyBox object source code.
// Coded by: Zac McClain

//** Load Dependences:

#include "SkyBox.h"

//** Public Default Constructors and Destructor:
		
SkyBox::SkyBox()
{}
		
SkyBox::~SkyBox()
{}

//** Functions:

//* Rendering:

void SkyBox::draw()
{
	drawSkybox( size );
}

//  void drawSkyboxPanel( ...params... )
//
//  Draws a single textured quad.  This became a bit more complex than intended, but it
//      allows for a generic definition.  We specify the two in-plane dimensions (dim1
//      and dim2) to determine our four corners.  These corners are centered around
//      point and are size distance away.  The quad is oriented with the provided
//      normal.  The provided texture is applied to the quad and can be flipped
//      along either axis if needed.
//
void SkyBox::drawSkyboxPanel( GLuint texHandle, Point point, Vector dim1, Vector dim2, Vector normal, int flippingFactor, int flippingFactor2, int size ) {
    // we're cheating by making our quads intersect at the edges to try and remove the joint line we sometimes see
    Point p1 = point + dim1*-(size+1) + dim2*-(size+1);  // LL corner
    Point p2 = point + dim1*(size+1) + dim2*-(size+1);   // LR corner
    Point p3 = point + dim1*(size+1) + dim2*(size+1);    // UR corner
    Point p4 = point + dim1*-(size+1) + dim2*(size+1);   // UL corner
    
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, texHandle );
    glPushMatrix(); {
        glColor4f(1,1,1,1);
        glBegin( GL_QUADS ); {
            glTexCoord2f(0, 0);
            normal.glNormal();
            p1.glVertex();
            
            glTexCoord2f(1*flippingFactor, 0);
            normal.glNormal();
            p2.glVertex();
            
            glTexCoord2f(1*flippingFactor, 1*flippingFactor2);
            normal.glNormal();
            p3.glVertex();
            
            glTexCoord2f(0, 1*flippingFactor2);
            normal.glNormal();
            p4.glVertex();
        }; glEnd();
    }; glPopMatrix();
    glDisable( GL_TEXTURE_2D );
}

//
//  void drawSkybox( int size )
//
//  Draws the six planes of our sky box.  Texturing each and having them oriented the correct way.
//
void SkyBox::drawSkybox( int size ) {
    //                 texHandle             Point                  dim1            dim2            Normal         flip   size          panel
    drawSkyboxPanel( handles[0], Point(   -1,     0, -size), Vector(1,0,0), Vector(0,1,0), Vector( 0, 0, 1), -1,  1, size );     // back
    drawSkyboxPanel( handles[1], Point(-size,     0,    -1), Vector(0,0,1), Vector(0,1,0), Vector( 1, 0, 0),  1,  1, size );     // left
    drawSkyboxPanel( handles[2], Point(    1,     0,  size), Vector(1,0,0), Vector(0,1,0), Vector( 0, 0,-1),  1,  1, size );     // front
    drawSkyboxPanel( handles[3], Point( size,     0,     1), Vector(0,0,1), Vector(0,1,0), Vector(-1, 0, 0), -1,  1, size );     // right
    drawSkyboxPanel( handles[4], Point(    0, -size,     0), Vector(1,0,0), Vector(0,0,1), Vector( 0, 1, 0), -1, -1, size );     // bottom
    drawSkyboxPanel( handles[5], Point(    0,  size,     0), Vector(1,0,0), Vector(0,0,1), Vector( 0,-1, 0), -1,  1, size );     // top
    //                 texHandle             Point                  dim1            dim2            Normal         flip   size          panel
}


//** Getters and Setters:

// Getters:
int SkyBox::getSize()
{
	return( size );
}

// Setters:
void SkyBox::setSize( int newSize )
{
	this->size = newSize;
}
