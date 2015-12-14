
// Textures header file.
// Coded by: Zac McClain

#ifndef TEXTURES_H
#define TEXTURES_H

//** Load Dependences:
#include <map>
#include <cstdlib>

#include "Texture.h"
#include "TransparentTexture.h"

using namespace std;

class Textures
{
	public:

	//** Variables:

	//** Public Default Constructors and Destructor:
		
		Textures();
		~Textures();

	//** Functions:
		void add( string name );
		void add( string newTexureName, GLuint* newTexure );
		void push( string name );
		void push( string newTexureName, GLuint* newTexure );
		void remove( string name );
		int size();
		GLuint* get( string name );
		GLuint* at( string name );

	//** Getters and Setters:

		// Getters:
		map< string, GLuint* > getMap();

		// Setters:
		void setMap( map< string, GLuint* > newMap );

	private:

	//** Variables:

	//** Functions:

	protected:

	//** Variables:
		map< string, GLuint* > texturesMap;

	//** Functions:
		
};

#endif // TEXTURES_H