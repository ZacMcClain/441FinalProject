
// Texture object source code.
// Coded by: Zac McClain

//** Load Dependences:

#include "Texture.h"

//** Helper Functions:

//  registerSOILTexture( filename, handle )
//
//  Loads a texture using SOIL and registers it with OpenGL
//
void registerSOILTexture( string filename, GLuint &tHandle ) {
    // load the texture image and return a handle to the texture
    tHandle = SOIL_load_OGL_texture( 
        filename.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y| SOIL_FLAG_COMPRESS_TO_DXT 
    );
    glBindTexture( GL_TEXTURE_2D, tHandle );                               // bind the handle
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );        // set our mode to modulate with lighting
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );   // lerp MIPMAP and lerp on texel on min filter
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );   // lerp on mag filter
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );       // repeat along S dimension
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );       // repeat along T dimesion
}

// readPPM() ///////////////////////////////////////////////////////////////////
//
//  This function reads an ASCII PPM, returning true if the function succeeds and
//      false if it fails. If it succeeds, the variables imageWidth and
//      imageHeight will hold the width and height of the read image, respectively.
//
//  It's not terribly robust.
//
//  Returns the image as an unsigned character array containing
//      imageWidth*imageHeight*3 entries (for that many bytes of storage).
//
//  NOTE: this function expects imageData to be UNALLOCATED, and will allocate
//      memory itself. If the function fails (returns false), imageData
//      will be set to NULL and any allocated memory will be automatically deallocated.
//
////////////////////////////////////////////////////////////////////////////////
bool readPPM( string filename, int &imageWidth, int &imageHeight, unsigned char* &imageData )
{
    FILE *fp = fopen( filename.c_str(), "r" );
    int temp, maxValue;

    fscanf( fp, "P%d", &temp );
    if( temp != 3 )  {
        fprintf(
            stderr, 
            "Error: PPM file is not of correct format! (Must be P3, is P%d.)\n", 
            temp
        );
        fclose( fp );
        return false;
    }
    
    //got the file header right...
    fscanf( fp, "%d", &imageWidth );
    fscanf( fp, "%d", &imageHeight );
    fscanf( fp, "%d", &maxValue );
    
    //now that we know how big it is, allocate the buffer...
    imageData = new unsigned char[imageWidth*imageHeight*3];
    if( !imageData )  {
        fprintf(
            stderr, 
            "Error: couldn't allocate image memory. Dimensions: %d x %d.\n", 
            imageWidth, 
            imageHeight
        );
        fclose( fp );
        return false;
    }
    
    //and read the data in.
    for( int j = 0; j < imageHeight; j++ )
    {
        for( int i = 0; i < imageWidth; i++ )
        {
            int r, g, b;
            fscanf( fp, "%d", &r );
            fscanf( fp, "%d", &g );
            fscanf( fp, "%d", &b );
            
            imageData[(j*imageWidth+i)*3+0] = r;
            imageData[(j*imageWidth+i)*3+1] = g;
            imageData[(j*imageWidth+i)*3+2] = b;
        }
    }
    
    fclose( fp );
    return true;
}

//  registerOpenGLRGBTexture( ...params... )
//
//  Takes in the RGB data of a texture of size width * height.  Registers
//      the texture with OpenGL setting the handle value to textureHandle.
//      Also sets the texture parameters for Min, Mag, S, T, and application
//      mode.
//
bool registerOpenGLRGBTexture(
    unsigned char *textureData,
    unsigned int texWidth, 
    unsigned int texHeight,
    GLuint &textureHandle
) {
    // make sure we are receiving data
    if(textureData == 0) {
        fprintf(stderr,"Cannot register texture; no data specified.");
        return false;
    }
    
    glGenTextures( 1, &textureHandle );                                   // generate a handle
    glBindTexture( GL_TEXTURE_2D, textureHandle );                        // bind the handle
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );        // set our mode to modulate with lighting
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );   // lerp on min filter
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );   // lerp on mag filter
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );       // repeat along S dimension
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );       // repeat along T dimesion
    
    GLenum errCode;
    const GLubyte *errString;
    
    // check for error
    if ((errCode = glGetError()) != GL_NO_ERROR) {
        errString = gluErrorString(errCode);
        fprintf(stderr,"Cannot register texture; OpenGL error: %s.", errString);
        return false;
    }
    
    // send the texture to the GPU
    glTexImage2D( 
        GL_TEXTURE_2D,      // texture type (a 2D texture)
        0,                  // level of detail
        GL_RGB,             // internal storage data format
        texWidth,           // width of texture
        texHeight,          // height of texture
        0,                  // border = 0
        GL_RGB,             // display format, must match the internal format
        GL_UNSIGNED_BYTE,   // data type in storage
        textureData         // the actual data
    );   
    
    return true;
}


//** Public Default Constructors and Destructor:
		
Texture::Texture()
{}

Texture::Texture( char* file )
{
    this->fileName = file;
}

Texture::Texture( GLuint texHandle )
{
    this->fileName = NULL;
    this->handle = texHandle;
}
		
Texture::~Texture()
{}

//** Functions:

//** Getters and Setters:

// Getters:

// Setters:
