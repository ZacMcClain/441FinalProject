Names: 
	Zac McClain ( Castamere Castelli )
	Walter Schlosser ( All Might / wschloss@mymail.mines.edu )
    Tyler Bank ( CoolPantsBro )

Program Title: 
	Key To The Kingdom ( Final Project )

Description:

	This program has been designed to showcase several of the topics learned in
	the CSCI441, Computer Graphics course at the Colorado School of Mines.

    The program is a space shooter where the user's goal is to shoot the enemies
    and avoid crashing into them.  The program demonstrates the use of .obj files
    which are loaded for the player's ship, the enemy ships, and the asteroids.

    In addition, the program demonstrates the user of shaders.  
    The first shader (dubbed the glow shader) is applied to the lasers, and 
    blurs/whitewashes the edges of the lines to create a glowing effect.  This technique 
    is accomplished with a multipass render on just the lasers.  The second shader (called the
    shift shader) is applied to the skybox and moves the texture radially out from
    the center as time passes to create the illusion of motion.  The third shader
    (called the pass shader) is used for the ships, and textures the ships.  It
    also shakes the ships back and forth and shades them red if desired, which is used
    when the main ship is hit.

    Lastly, the scene is created by rendering the lasers to a buffer, then rendering
    the skybox to the screen, then the ship/enemies to the screen, and lastly the
    buffer as a textured 2D quad with the glow effect applied. The program also
    demonstrates basic bounding sphere collision detection.

Usage:

    'wasd'      -       Move the main ship around the screen
    ' ' (space) -       Fire laser
    left mouse  -       Click and drag to pan camera
    right mouse -       Click and drag to zoom camera    

Build Instructions:

	Simply navigate to the working directory and type 'make.' main.cpp needs
    to be linked with the OpenGL / freeglut libraries and GLUI as well as GLEW.
    It also has a number of custom classes and files whose sources can be found
    in src/ folder. main.cpp must also be linked to the header files for these classes
    found in the include/ directory.

	~/path/to/main.cpp $ make
	if( OS X or *nix )
		~/path/to/main.cpp $ ./keyToTheKingdom 
	else
		~/path/to/main.cpp $ ./keyToTheKingdom.exe
	end
	
Notes:

	Bugs: 
	Implementation Details:

Distribution of work:
    
    Walter
        Framebuffer/Shader setup debugging
        Layered/Multipass rendering setup to apply shaders to specific objects
        Model loading and texturing
        Enemy spawning
        Shifting texture shader
        Pass/Red Shake shader 

    Zac

    Tyler

Stats:
	Time Investment:
	Learning Score[0, 10]:
	Entertainment Score[0, 10]:
