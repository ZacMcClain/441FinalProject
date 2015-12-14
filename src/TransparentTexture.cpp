
// TransparentTexture object source code.
// Coded by: Zac McClain

//** Load Dependences:

#include "TransparentTexture.h"

//** Helper Functions:

// registerTransparentOpenGLTexture()
//
//  Similar to the helper function that registers a single OpenGL texture, this
//      function registers a texture that has 4 channels (RGBA), but specifically
//      is used when the alpha channel is a separate array. This combination
//      could easily be performed in the function that reads the images from file instead.
//
bool registerTransparentOpenGLTexture(
	unsigned char *imageData, 
	unsigned char *imageMask, 
	int texWidth, 
	int texHeight, 
	GLuint &texHandle
) {
    // combine the 'mask' array with the image data array into an RGBA array.
    unsigned char *fullData = new unsigned char[texWidth*texHeight*4];
    for(int j = 0; j < texHeight; j++) {
        for(int i = 0; i < texWidth; i++) {
            fullData[(j*texWidth+i)*4+0] = imageData[(j*texWidth+i)*3+0];   // R
            fullData[(j*texWidth+i)*4+1] = imageData[(j*texWidth+i)*3+1];   // G
            fullData[(j*texWidth+i)*4+2] = imageData[(j*texWidth+i)*3+2];   // B
            fullData[(j*texWidth+i)*4+3] = imageMask[(j*texWidth+i)*3+0];   // A
        }
    }
    
    // first off, get a real texture handle.
    glGenTextures(1, &texHandle);
    
    // make sure that future texture functions affect this handle
    glBindTexture(GL_TEXTURE_2D, texHandle);
    
    // set this texture's color to be multiplied by the surface colors --
    //  GL_MODULATE instead of GL_REPLACE allows us to take advantage of OpenGL lighting
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // set the minification and magnification functions to be linear; not perfect
    //  but much better than nearest-texel (GL_NEAREST).
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Set the texture to repeat in S and T -- though it doesn't matter here
    //  because our texture coordinates are always in [0,0] to [1,1].
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // actually transfer the texture to the GPU and use MipMaps!!
    /*    gluBuild2DMipMaps(
     GL_TEXTURE_2D,              //still working with 2D textures, obv.
     GL_RGBA,                    //we're going to provide OpenGL with R, G, B, and A components...
     texWidth,                   //...of this width...
     texHeight,                  //...and this height.
     GL_RGBA,                    //and store it, internally, as RGBA (OpenGL will convert to floats between 0.0 and 1.0f)
     GL_UNSIGNED_BYTE,           //this is the format our data is in, and finally,
     fullData);                  //there's the data!
     */
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texWidth, texHeight, GL_RGBA, GL_UNSIGNED_BYTE, fullData );
    
    // clean up our memory on the CPU side since it's already been transfered to the GPU
    delete fullData;
    
    // whoops! i guess this function can't fail. in an ideal world, there would
    // be checks with glGetError() that we could use to determine if this failed.
    return true;
}


void loadImageAndMask( char* imageFile, char* maskFile, GLuint &TexHandle )
{
    ////// LOAD IN OUR TRANSPARENT TEXTURES //////////////////////////////////////////////////
    // some relevant variables for the texture files that we won't need later...so don't make them global
    int rgbWidth, rgbHeight, alphaWidth, alphaHeight, channels;
    unsigned char *texData, *maskData;

    texData = SOIL_load_image( 
        imageFile,
        &rgbWidth, 
        &rgbHeight, 
        &channels,
        SOIL_LOAD_AUTO 
    );
    printf( "[INFO]: read in image treeDiff.jpg of size %d x %d with %d colors\n", rgbWidth, rgbHeight, channels );
    maskData = SOIL_load_image( 
        maskFile,
        &alphaWidth, 
        &alphaHeight, 
        &channels,
        SOIL_LOAD_AUTO 
    );

    registerTransparentOpenGLTexture( texData, maskData, rgbWidth, rgbHeight, TexHandle );
}

//** Public Default Constructors and Destructor:
		
TransparentTexture::TransparentTexture()
{}
		
TransparentTexture::~TransparentTexture()
{}

//** Functions:

//** Getters and Setters:

// Getters:

// Setters:
