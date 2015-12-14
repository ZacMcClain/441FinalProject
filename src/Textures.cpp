
// Textures object source code.
// Coded by: Zac McClain

//** Load Dependences:

#include "Textures.h"

//** Public Default Constructors and Destructor:
		
Textures::Textures()
{}
		
Textures::~Textures()
{}

//** Functions:

void Textures::add( string name )
{
	add( name, new GLuint );
}

void Textures::push( string name )
{
	add( name, new GLuint );
}

void Textures::add( string newTexureName, GLuint* newTexure )
{
	this->texturesMap.insert( pair< string, GLuint* >( newTexureName, newTexure) );
}

void Textures::push( string newTexureName, GLuint* newTexure )
{
	add( newTexureName, newTexure );
}

void Textures::remove( string name )
{
	this->texturesMap.erase( name );
}

int Textures::size()
{
	return( this->texturesMap.size() );
}

GLuint* Textures::get( string nameKey )
{
	return( texturesMap[nameKey] );
}

GLuint* Textures::at( string nameKey )
{
	return( get(nameKey) );
}

//** Getters and Setters:

// Getters:
map< string, GLuint* > Textures::getMap()
{
	return( texturesMap );
}

// Setters:
void Textures::setMap( map< string, GLuint* > newMap )
{
	this->texturesMap = newMap;
}
