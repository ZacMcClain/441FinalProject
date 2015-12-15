
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

Mouse* mouse; // keeps track of our mouse stuff
ArcballCamera* cam; // our camera model
SkyBox* skyBox; // our background sky box
Window window; // keeps take of our window stuff
Textures textures; // a container for out textures
Object* ship; // our ship model object

// One enemy for testing
Object* enemy;

GLuint blurShaderProgramHandle, shiftShaderProgramHandle, passTextureShaderProgramHandle;
GLuint framebufferSizeLoc, blurSizeLoc, timeLoc;
GLfloat BLUR_SIZE = 1;

GLuint framebufferHandle;
GLuint renderbufferHandle;
GLuint framebufferWidth, framebufferHeight;

GLuint fboTexHandle; // this is a handle to the texture that we will render our FBO to

// END GLOBAL VARIABLES ///////////////////////////////////////////////////////

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
    glClearColor( 1, 1, 1, 0.0 );
    
    //tell OpenGL not to use the material system; just use whatever we pass with glColor()
    glEnable( GL_COLOR_MATERIAL );
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    
    float lightCol[4] = { 1,1,1,1 };
    float ambientCol[4] = { 0.1,0.1,0.1,1.0 };
    glLightfv( GL_LIGHT0, GL_DIFFUSE, lightCol );
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientCol );
    glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5 );
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
    // init our camera to a nice starting point
    cam = new ArcballCamera( 35.0f, 0.0f, 90.0f );
    
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    
    // Generate Framebuffer
    glGenFramebuffers( 1, &framebufferHandle ); // set framebufferHandle
    // set to active
    glBindFramebuffer( GL_FRAMEBUFFER, framebufferHandle );

    // set dimension vars
    framebufferWidth = 1024;  // set fb width
    framebufferHeight = 1024; // set fb hight

    // Generate the render buffer
    glGenRenderbuffers( 1, &renderbufferHandle ); // set renderbufferHandle
    // set to active
    glBindRenderbuffer( GL_RENDERBUFFER, renderbufferHandle );

    // Set up the options for the frame and render buffers
    glRenderbufferStorage( 
        GL_RENDERBUFFER,
        GL_DEPTH_COMPONENT,
        framebufferWidth,
        framebufferHeight 
    );

    glFramebufferRenderbuffer( 
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_RENDERBUFFER,
        renderbufferHandle 
    );

    // Generate texture data that will be used with the frame buffer
    glGenTextures( 1, &fboTexHandle ); // setting the texture handle
    glBindTexture( GL_TEXTURE_2D, fboTexHandle ); // binding it to a texture 2d

    // Load nothing into the texture
    glTexImage2D( 
        GL_TEXTURE_2D,
        0,
        GL_RGBA, //this needs to match the color buffer requested from GLUT
        framebufferWidth,
        framebufferHeight,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        NULL
    );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); // liner min filter
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); // liner max filter 
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE ); // clamp s to the edge
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ); // clamp t to the edge
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );


    // Attach the texture to the framebuffer
    glFramebufferTexture2D( 
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        fboTexHandle,
        0
    );

    // Error check
    GLenum status = glCheckFramebufferStatus( GL_FRAMEBUFFER );

    if( status == GL_FRAMEBUFFER_COMPLETE ) {
        printf( "Framebuffer initialized completely!\n" );
    } else {
        printf( "Framebuffer FAILED TO INITIALIZE COMPLETELY.\n" );
    }
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

// Draws objects that should glow (just the lasers when finished)
void drawGlowObjs() {
  // just a cube for testing
  glDisable(GL_TEXTURE_2D);
  glColor4f(0, 1, 0, 1);
  glPushMatrix(); {
    glTranslatef(0, 10, 0);
    glutSolidCube(5);
  } glPopMatrix();
  
  glPushMatrix();
    glDisable(GL_LIGHTING);
    glEnable(GL_LINE_SMOOTH);
	glLineWidth( 5 );
	glTranslatef(5.0, 2.15, 0.0);
	// glRotate with ship direction
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	  glVertex3f(0, 0, 0);
	  glVertex3f(0, 0, 10);
	glEnd();
  
  glEnable(GL_LIGHTING);
  glPopMatrix();
  
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glEnable(GL_LINE_SMOOTH);
	glLineWidth( 5 );
	glTranslatef(-5.0, 2.15, 0.0);
	// glRotate with ship direction
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	  glVertex3f(0, 0, 0);
	  glVertex3f(0, 0, 10);
	glEnd();
  
  glEnable(GL_LIGHTING);
  glPopMatrix();
}

void display() {
    static double curent_time = 0;
    static double last_time = 0;
    
    last_time = curent_time;
    curent_time = ( (double)glutGet(GLUT_ELAPSED_TIME) / 1000.0 );
    
    // Bind Framebuffer and render glowing objects to framebuffer texture
    glBindFramebuffer( GL_FRAMEBUFFER, framebufferHandle );
        // push viewport to stack 
        glPushAttrib( GL_VIEWPORT_BIT ); {
            // Set the rendering viewport to match the framebuffer dimensions
            glViewport( 0, 0, framebufferWidth, framebufferHeight );

            // clear the framebuffer
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
            
            // update the modelview matrix based on the camera's position
            glMatrixMode( GL_MODELVIEW );         // make sure we aren't changing the projection matrix!
            glLoadIdentity();
            cam->lookAt();
            
            // enable a default light for the scene;
            float lPosition[4] = { 100, 1000, 100, 1 };
            glLightfv( GL_LIGHT0, GL_POSITION, lPosition );
            
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
            // Draws only objects that should glow
            drawGlowObjs();

            // Make sure that OpenGL has finished rendering everything...
            glFlush(); glFinish();
            // the first pass is now inside of that texture! (fboTexHandle!)
        }; glPopAttrib();
        
    // Unbind framebuffer
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    // Clear the screen now
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    // Render the background with the "shifting texture" shader
    glUseProgram(shiftShaderProgramHandle);
    glUniform1f(timeLoc, (float)curent_time);
    glLoadIdentity();
    cam->lookAt();
    skyBox->drawSkybox( 300 );

    // And now render the ship...
    glUseProgram(passTextureShaderProgramHandle);
    glPushMatrix(); {
      glScalef(0.1, 0.1, 0.1);
      //glEnable(GL_TEXTURE_2D);
      glBindTexture( GL_TEXTURE_2D, *textures.at("x-wing") );
      ship->draw();
    } glPopMatrix();

    // TESTING enemy object
    glPushMatrix(); {
      glTranslatef(0, -15, 0);
      glBindTexture( GL_TEXTURE_2D, *textures.at("tiefighter"));
      enemy->draw();
    } glPopMatrix();

    // Then render the framebuffer contents as a textured 2d quad
    // on top of the scene with the glow shader
    glMatrixMode( GL_PROJECTION );
    glPushMatrix(); {
        glLoadIdentity();
        gluOrtho2D( -1, 1, -1, 1 );

        //and the modelview...
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        
        glDisable( GL_LIGHTING );
        glDisable( GL_DEPTH_TEST );

        glBindTexture( GL_TEXTURE_2D, fboTexHandle );

        glUseProgram( blurShaderProgramHandle ); 
        // Pass the framebuffersize and the blursize to the shader
        glUniform1f(framebufferSizeLoc, (float)framebufferWidth);
        glUniform1f(blurSizeLoc, BLUR_SIZE);
        
        glBegin( GL_QUADS ); {
            glTexCoord2f( 0,0 ); glVertex2f( -1,-1 );
            glTexCoord2f( 1,0 ); glVertex2f( 1,-1 );
            glTexCoord2f( 1,1 ); glVertex2f( 1,1 );
            glTexCoord2f( 0,1 ); glVertex2f( -1,1 );
        }; glEnd();

        glUseProgram( 0 );
    } glMatrixMode( GL_PROJECTION );
    glPopMatrix();

    // reenable features
    glEnable( GL_LIGHTING );
    glEnable( GL_DEPTH_TEST );
    

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

    // load the x wing texture
    textures.add("x-wing");
    registerSOILTexture("./models/Ship/X-Wing/all_fly_xwing.png", *textures.at("x-wing"));
    printf("[INFO]: X-Wing texture read in and registered\n");

    // losf the tie fighter texture
    textures.add("tiefighter");
    registerSOILTexture("./models/Enemy/tie_fighter/imp_fly_tiefighter.png", *textures.at("tiefighter"));
    printf("[INFO]: TIE Fighter texture read in and registered\n");
    //////////////////////////////////////////////////////////////////////////////////////////
}

int main( int argc, char *argv[] ) {
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( window.getWidth(), window.getHeight() );
    glutCreateWindow( "keyToTheKingdom" );

    ship = new Object( "./models/Ship/X-Wing/X-Wing.obj" );
    enemy = new Object("./models/Enemy/tie_fighter/imp_fly_tiefighter.obj");
    
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

    shiftShaderProgramHandle = createShaderProgram("shaders/shift.v.glsl", "shaders/shift.f.glsl", "Shift Shader Program");
    timeLoc = glGetUniformLocation( shiftShaderProgramHandle, "time" );

    // This one fixes our x-wing texturing problems.  Its just a pass through.
    passTextureShaderProgramHandle = createShaderProgram("shaders/pass.v.glsl", "shaders/pass.f.glsl", "Pass Texture Program");
    
    glutReshapeFunc( reshape );
    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
    glutMouseFunc( mouseCallback );
    glutMotionFunc( mouseMotion );
    glutTimerFunc( (unsigned int)(1000.0 / 60.0), update, 0 );
    
    glutMainLoop ();
    
    return 0;
}
