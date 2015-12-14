
// TransparentTexture header file.
// Coded by: Zac McClain

#ifndef TRANSPARENTTEXTURE_H
#define TRANSPARENTTEXTURE_H

//** Load Dependences:
#include "Texture.h"

class TransparentTexture : public Texture
{
	public:

	//** Variables:

	//** Public Default Constructors and Destructor:
		
		TransparentTexture();
		~TransparentTexture();

	//** Functions:

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

//** Helper Functions:
bool registerTransparentOpenGLTexture(
    unsigned char *imageData, 
    unsigned char *imageMask, 
    int texWidth, 
    int texHeight, 
    GLuint &texHandle 
);
void loadImageAndMask( char* imageFile, char* maskFile, GLuint &handle );

#endif // TRANSPARENTTEXTURE_H