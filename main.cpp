
#include <GL/glew.h>

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <SOIL/SOIL.h>

#include <fstream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Point.h"
#include "Shader_Utils.h"
#include "Mouse.h"
#include "ArcballCamera.h"
#include "Window.h"
#include "SkyBox.h"
#include "Textures.h"
#include "Object.h"

using namespace std;

// GLOBAL VARIABLES ////////////////////////////////////////////////////////////

Mouse* mouse;
ArcballCamera* cam;
SkyBox* skyBox;
Window window;
Textures textures;
Object* ship;

// int windowWidth = 512, windowHeight = 512;  // window dimensions

// GLint leftMouseButton, rightMouseButton;    // status of the mouse buttons
// int mouseX = 0, mouseY = 0;                 // last known X and Y of the mouse

// Point cameraTPR;                            // spherical coordinates of camera mapped XYZ - TPR (theta phi radius)
// Point cameraLookAt;                         // cpoint camera is looking at

// GLuint groundTexHandle;                     // a handle to the textures in our OpenGL context
// GLuint skyboxHandles[6];                    // all of our skybox handles

bool DISPLAY_WIREFRAME = false;

GLuint blurShaderProgramHandle;
GLuint framebufferSizeLoc, blurSizeLoc;
GLfloat BLUR_SIZE = 1;

GLuint framebufferHandle; // not used yet.
GLuint renderbufferHandle;
GLuint framebufferWidth, framebufferHeight; // set these to the desired size

GLuint fboTexHandle;


// END GLOBAL VARIABLES ///////////////////////////////////////////////////////

//
//  void resizeWindow(int w, int h)
//
//      We will register this function as GLUT's reshape callback.
//   When the window is resized, the OS will tell GLUT and GLUT will tell
//   us by calling this function - GLUT will give us the new window width
//   and height as 'w' and 'h,' respectively - so save those to our global vars.
//
void resizeWindow( int w, int h ) {
    
    window.setDimensions( w, h );
    
    // update the viewport to fill the window
    glViewport( 0, 0, w, h );
    
    // update the projection matrix with the new window properties
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0, window.getAspectRatio(), 0.1, 100000 );
}

//  void mouseCallback(int button, int state, int thisX, int thisY)
//
//  GLUT callback for mouse clicks. We save the state of the mouse button
//      when this is called so that we can check the status of the mouse
//      buttons inside the motion callback (whether they are up or down).
//
void mouseCallback( int button, int state, int thisX, int thisY ) {
    //update the left and right mouse button states, if applicable
    if( button == GLUT_LEFT_BUTTON ) {
        mouse->setLeftMouseButton( state );
    } else if( button == GLUT_RIGHT_BUTTON ) {
        mouse->setRightMouseButton( state );
    }
    
    //and update the last seen X and Y coordinates of the mouse
    mouse->setX( thisX );
    mouse->setY( thisY );
}

//  void mouseMotion(int x, int y)
//
//  GLUT callback for mouse movement. We update cameraPhi, cameraTheta, and/or
//      cameraRadius based on how much the user has moved the mouse in the
//      X or Y directions (in screen space) and whether they have held down
//      the left or right mouse buttons. If the user hasn't held down any
//      buttons, the function just updates the last seen mouse X and Y coords.
//
void mouseMotion( int x, int y ) {
    // mouse is moving; if left button is held down...
    if( mouse->isLeftMouseButtonDown() ) {
        
        cam->setTheta( cam->getTheta() + ((x - mouse->getX())*0.005) );
        cam->setPhi( cam->getPhi() + ((y - mouse->getY())*0.005 ) );
        
        cam->update();

    } else if( mouse->isRightMouseButtonDown() ) {
        // for the right mouse button, just determine how much the mouse has moved total.
        // not the best "zoom" behavior -- if X change is positive and Y change is negative,
        // (along the X = Y line), nothing will happen!! but it's ok if you zoom by
        // moving left<-->right or up<-->down, which works for most people i think.
        double totalChangeSq = ( (x - mouse->getX()) + (y - mouse->getY()) );
        cam->setRadius( cam->getRadius() + (totalChangeSq * 0.01) );
        
        cam->update();
    }
    
    // and save the current mouseX and mouseY.
    mouse->setX( x );
    mouse->setY( y );
}

void init( const char *filename, const char *animfile )
{
    /* Initialize OpenGL context */
    glClearColor( 0.5f,0.5f,0.5f,1.0f );
    
    //tell OpenGL not to use the material system; just use whatever we pass with glColor()
    glEnable( GL_COLOR_MATERIAL );
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    
    float lightCol[4] = { 1,1,1,1 };
    float ambientCol[4] = { 0.1,0.1,0.1,1.0 };
    glLightfv( GL_LIGHT0,GL_DIFFUSE,lightCol );
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientCol );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    
    glDisable( GL_CULL_FACE );
    glEnable( GL_NORMALIZE );
    glEnable( GL_DEPTH_TEST );
    
    //tells OpenGL to blend colors across triangles. Once lighting is
    //enabled, this means that objects will appear smoother - if your object
    //is rounded or has a smooth surface, this is probably a good idea;
    //if your object has a blocky surface, you probably want to disable this.
    glShadeModel( GL_SMOOTH );
    
    mouse = new Mouse();
    skyBox = new SkyBox();
    // init our camera a pretty starting point
    cam = new ArcballCamera( 35.0f, 1.025f, 2.0f );
    // cameraTPR = Point( 2.0, 1.57, 200.0 );
    // cameraLookAt = Point( 0,0,0 );
    
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    
    // Setup Framebuffer, not sure why this is NOT working.
    // glGenFramebuffers( 1, &framebufferHandle ); // set framebufferHandel

    // framebufferWidth = 1024;  // set fb width
    // framebufferHeight = 1024; // set fb hight

    // glGenRenderbuffers( 1, &renderbufferHandle ); // set renderbufferHandle

    // glBindFramebuffer( GL_FRAMEBUFFER, framebufferHandle );
    // glBindRenderbuffer( GL_RENDERBUFFER, renderbufferHandle );

    // glRenderbufferStorage( 
    //     GL_RENDERBUFFER,
    //     GL_DEPTH_COMPONENT,
    //     framebufferWidth,
    //     framebufferHeight 
    // );

    // glFramebufferRenderbuffer( 
    //     GL_FRAMEBUFFER,
    //     GL_DEPTH_ATTACHMENT,
    //     GL_RENDERBUFFER,
    //     renderbufferHandle 
    // );

    // glGenTextures( 1, &fboTexHandle ); // setting the texture handle
    // glBindTexture( GL_TEXTURE_2D, fboTexHandle ); // binding it to a texture 2d

    // glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); // liner min filter
    // glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); // liner max filter 
    // glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ); // clamp s to the edge
    // glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ); // clamp t to the edge

    // glTexImage2D( 
    //     GL_TEXTURE_2D,
    //     0,
    //     GL_RGBA, //this needs to match the color buffer requested from GLUT
    //     framebufferWidth,
    //     framebufferHeight,
    //     0,
    //     GL_RGBA,
    //     GL_UNSIGNED_BYTE,
    //     NULL
    // );

    // glFramebufferTexture2D( 
    //     GL_FRAMEBUFFER,
    //     GL_COLOR_ATTACHMENT0,
    //     GL_TEXTURE_2D,
    //     fboTexHandle,
    //     0
    // );

    // GLenum status = glCheckFramebufferStatus( GL_FRAMEBUFFER );

    // if( status == GL_FRAMEBUFFER_COMPLETE ) {
    //     printf( "Framebuffer initialized completely!\n" );
    // } else {
    //     printf( "Framebuffer FAILED TO INITIALIZE COMPLETELY.\n" );
    // }
}

void reshape( int w, int h )
{
    if( h == 0 ) {
        h = 1;
    }
    
    glViewport( 0, 0, (GLsizei)w, (GLsizei)h );
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0, w/(GLdouble)h, 0.1, 1000.0 );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void drawObjs()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    skyBox->drawSkybox( 300 );

    glPushMatrix(); {   
        // ship->draw();
    }; glPopMatrix();
}

void display() {
    int i;
    
    static double curent_time = 0;
    static double last_time = 0;
    
    last_time = curent_time;
    curent_time = ( (double)glutGet(GLUT_ELAPSED_TIME) / 1000.0 );
    
    // Bind Framebuffer and Render full scene to framebuffer texture - not working b/c
    // the init is not working
    // glBindFramebuffer( GL_FRAMEBUFFER, framebufferHandle );
    // glBindRenderbuffer( GL_RENDERBUFFER, renderbufferHandle );
        glPushAttrib( GL_VIEWPORT_BIT ); {
            // glViewport( 0, 0, framebufferWidth, framebufferHeight );

            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            
            // update the modelview matrix based on the camera's position
            glMatrixMode( GL_MODELVIEW );         // make sure we aren't changing the projection matrix!
            glLoadIdentity();
            cam->lookAt();
            
            // enable a default light for the scene;
            float lPosition[4] = { 100, 100, 100, 1 };
            glLightfv( GL_LIGHT0, GL_POSITION, lPosition );
            
            drawObjs();

            // Make sure that OpenGL has finished rendering everything...
            glFlush(); glFinish();
            // the first pass is now inside of that texture! (fboTexHandle!)
        }; glPopAttrib();
        
    // Unbind framebuffer
    // glBindRenderbuffer( GL_RENDERBUFFER, 0 );
    // glBindFramebuffer( GL_FRAMEBUFFER, 0 );

    
    // TODO #9: Render texture to a 2D quad filling the scene
    // glMatrixMode( GL_PROJECTION );
    // glPushMatrix(); {
    //     glLoadIdentity();
    //     gluOrtho2D( -1, 1, -1, 1 );

    //     //and the modelview...
    //     glMatrixMode( GL_MODELVIEW );
    //     glLoadIdentity();
    //     glDisable( GL_LIGHTING );
    //     glEnable( GL_TEXTURE_2D );
    //     glBindTexture( GL_TEXTURE_2D, fboTexHandle );
    //     glUseProgram( blurShaderProgramHandle );
    //     glBegin( GL_QUADS ); {
    //         glTexCoord2f( 0,0 ); glVertex2f( -1,-1 );
    //         glTexCoord2f( 1,0 ); glVertex2f( 1,-1 );
    //         glTexCoord2f( 1,1 ); glVertex2f( 1,1 );
    //         glTexCoord2f( 0,1 ); glVertex2f( -1,1 );
    //     }; glEnd();
    //     glUseProgram( 0 );
    //     glDisable( GL_TEXTURE_2D );
    //     glEnable( GL_LIGHTING );
    // }; glMatrixMode( GL_PROJECTION );
    // glPopMatrix();

    glutSwapBuffers();
}

void cleanup() {
    // free memory
    // delete mouse;
    // delete cam;
    // delete skyBox;
    // delete ship;
}

void keyboard( unsigned char key, int x, int y )
{
    /* Escape */
    if( (key == 27) || (key == 'q') || (key == 'Q') ){
        exit( 0 );
    } else if( key == '+' ) {
        BLUR_SIZE += 1;
    } else if( key == '-' ) {
        BLUR_SIZE -= 1;
        if( BLUR_SIZE < 1 ) BLUR_SIZE = 1;
    } else if( key == ' ' ) {
        // shoot laser
    }
}

// void myTimer(int value)
//
//  We have to take an integer as input per GLUT's timer function prototype;
//  but we don't use that value so just ignore it. We'll register this function
//  once at the start of the program, and then every time it gets called it
//  will perpetually re-register itself and tell GLUT that the screen needs
//  be redrawn. yes, I said "needs be."
//
void update( int value ) {
    glutPostRedisplay();
    
    glutTimerFunc( (unsigned int)(1000.0 / 60.0), update, 0 );
}

//  registerTextures()
//
//  Register all of our textures with OpenGL.  This includes the brick for our spheres,
//      our ground plane, and our skybox.  Provide some output to the user so they know
//      what is causing the loading delay.
//
void registerTextures() {
    ////// LOAD IN OUR TEXTURES //////////////////////////////////////////////////////////////

    // this is how to use the textures obj
    // textures.add( "example" );
    // registerSOILTexture( "textures/ground.jpg", *textures.at("example") );
    // printf( "[INFO]: example texture read in and registered\n" );
    
    printf( "[INFO]: registering skybox..." );
    fflush( stdout );
    
    registerSOILTexture( "textures/skybox/stars_bk.jpg", skyBox->handles[0] );   printf( "." ); fflush( stdout );
    registerSOILTexture( "textures/skybox/stars_bk.jpg", skyBox->handles[1] );   printf( "." ); fflush( stdout );
    registerSOILTexture( "textures/skybox/stars_bk.jpg", skyBox->handles[2] );   printf( "." ); fflush( stdout );
    registerSOILTexture( "textures/skybox/stars_bk.jpg", skyBox->handles[3] );   printf( "." ); fflush( stdout );
    registerSOILTexture( "textures/skybox/stars_bk.jpg", skyBox->handles[4] );   printf( "." ); fflush( stdout );
    registerSOILTexture( "textures/skybox/stars_bk.jpg", skyBox->handles[5] );   printf( "." ); fflush( stdout );
    
    printf( "skybox textures read in and registered!\n" );
    //////////////////////////////////////////////////////////////////////////////////////////
}

int main( int argc, char *argv[] ) {
    // if (argc < 1) {
    //     fprintf (stderr, "usage: %s <config file> \n", argv[0]);
    //     return 0;
    // }

    // ship = new Object( "./models/Ship/X-Wing/X-Wing.obj" );
    
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( window.getWidth(), window.getHeight() );
    glutCreateWindow( "keyToTheKingdom" );
    
    /* initialize GLEW */
    GLenum glewResult = glewInit();
    /* check for an error */
    if( glewResult != GLEW_OK ) {
        printf( "[ERROR]: Error initalizing GLEW\n");
        return 0;
    }
    /* make sure OpenGL 2.0 is supported */
    if( !glewIsSupported( "GL_VERSION_2_0" ) ) {
        printf( "[ERROR]: System does not support OpenGL 2.0 and GLSL 1.20\n" );
        return 0;
    }
    
    PrintOpenGLInfo();
    
    printf( "[INFO]: System supports OpenGL2.0 and GLSL 1.20!\n\n" );
    
    atexit( cleanup );

    init( argv[1], (argc > 2) ? argv[2] : NULL );
    printf( "[INFO]: OpenGL Scene set up\n" );

    registerTextures();
    
    blurShaderProgramHandle = createShaderProgram( "shaders/blur.v.glsl", "shaders/blur.f.glsl", "Blur Shader Program" );
    framebufferSizeLoc = glGetUniformLocation( blurShaderProgramHandle, "framebufferSize" );
    blurSizeLoc = glGetUniformLocation( blurShaderProgramHandle, "blurSize" );
    
    glutReshapeFunc( reshape );
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutMouseFunc( mouseCallback );
    glutMotionFunc( mouseMotion );
    glutTimerFunc( (unsigned int)(1000.0 / 60.0), update, 0 );
    
    glutMainLoop ();
    
    return 0;
}
