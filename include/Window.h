
// Window header file.
// Coded by: Zac McClain

#ifndef WINDOW_H
#define WINDOW_H

//** Load Dependences:


class Window
{
	public:

	//** Variables:

	//** Public Default Constructors and Destructor:
		
		Window();
		Window( int myWidth, int myHeight );
		~Window();

	//** Functions:
		void updateAspectRatio();

	//** Getters and Setters:

		// Getters:
		int getHeight();
		int getWidth();
		float getAspectRatio();

		// Setters:
		void setHeight( int newHeight );
		void setWidth( int newWidth );
		void setDimensions( int newWidth, int newHeight );

	private:

	//** Variables:
		int height;
		int width;
		float aspectRatio;

	//** Functions:

	protected:

	//** Variables:

	//** Functions:
		
};

#endif // CLASSNAME_H