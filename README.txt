CSCI441
Castamere's All Mighty Guild of Cool Pants

Names: 

	Zac McClain ( Castamere Castelli / zamcclai@mines.edu )
	Walter Schlosser ( All Might / wschloss@mymail.mines.edu )
    Tyler Bank ( CoolPantsBro / tbank@mymail.mines.edu )

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

    'wasd'        -       Move the main ship around the screen
    ' ' (space)   -       Fire laser
    't', 'T' keys -       Testing mode toggle

    Camera  - To pan around the ship click and drag the left mouse button.
    		- To Zoom in or out click and drag the right mouse button.


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
		Laser can be seen though the ship due to order of rendering layers to 
        the screen.  Other orders break the rendering for some reason.

	Implementation Details:
		... Please see comments in the source code for more details ...

Input File:
    
    Our program does not require an input file.

Distribution of work:
    
    Walter:
        Framebuffer/Shader setup debugging
        Layered/Multipass rendering setup to apply shaders to specific objects
        Model loading and texturing
        Enemy spawning and movement
        Shifting texture shader
        Pass/Red Shake shader 

    Zac:
    	Project setup
    	Part of the glow shader
    	Loading and random sizing of the asteroid model
    	Creation (using some of Walters code) of the Ship class
    	Life bar and live score display
    	Game over screen

    Tyler:
        Laser rendering/effects/interaction
        Part of the glow shader
        Attached spotlight to player ship
        Bounding sphere collision detection
		Raytrace collision detection with spheres for the laser.

Stats:
	Time Investment:
        Walter  - approx 8 hours
        Zac     - approx 8-9 hours (bit of a slow coder)
        Tyler   - approx 8 hours
	Learning Score[0, 10]:
        Walter  - 7/10
        Zac     - 8/10
        Tyler   - 8/10
	Entertainment Score[0, 10]:
        Walter  - 8/10
        Zac     - 9/10
        Tyler   - 9/10
