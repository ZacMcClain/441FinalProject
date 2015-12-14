
// Texture header file.
// Coded by: Zac McClain

#ifndef TEXTURE_H
#define TEXTURE_H

//** Load Dependences:
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <SOIL/soil.h>

#include <fstream>
#include <list>
#include <string>

using namespace std;

class Texture
{
	public:

	//** Variables:
	GLuint handle;

	//** Public Default Constructors and Destructor:
		
		Texture();
		Texture( char* fileName );
		Texture( GLuint texHandle );
		~Texture();

	//** Functions:
		bool readPPM( string filename, int &imageWidth, int &imageHeight, unsigned char* &imageData );
		bool registerOpenGLRGBTexture(
			unsigned char *textureData,
			unsigned int texWidth, 
			unsigned int texHeight,
            GLuint &textureHandle
        );
        void registerSOILTexture( string filename, GLuint &handle );
        void loadImageAndMask( char* imageFile, char* maskFile );

	//** Getters and Setters:

		// Getters:
		char* getFileName();

		// Setters:
		void setFileName();

	private:

	//** Variables:

	//** Functions:

	protected:

	//** Variables:
		char* fileName;

	//** Functions:
		
};

//** Helper Functions:
bool readPPM( string filename, int &imageWidth, int &imageHeight, unsigned char* &imageData );
bool registerOpenGLRGBTexture(
	unsigned char *textureData,
	unsigned int texWidth, 
	unsigned int texHeight,
    GLuint &textureHandle
);
void registerSOILTexture( string filename, GLuint &handle );

#endif // TEXTURE_H