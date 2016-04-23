/**
*   @file		Hitbox.h
*   @brief		Definition of Hitbox class.
*
*				This contains the definitions of the public and
*				private member variables, as well as all methods,
*				for the Hitbox class, which is the object 
*				responsible for detecting all collisions between 
*				objects	within the gamespace.
*
*   @author		Tyler Bertram
*   @bug		No known bugs.
*/

#ifndef HITBOX_H
#define HITBOX_H


#include <iostream>

class Hitbox {
private:
	/** Private Member Variables */
	//Width and height are a measure of how many pixels the hitbox comprises on /each side/ of the central coordinate.
	//So a width/height 1 hitbox is a 3x3 square.
	float		hitboxCentreX, hitboxCentreY, hitboxWidth, hitboxHeight;	/**< hitboxCentreX and hitboxCentreY are self-explanatory. */
																			/**< hitboxWidth and hitboxHeight are a measure of the pixels of the hitbox on *each side* of the central coordinates. */
																			/**< For example, a width/height 1 hitbox is a 3x3 square. */

public:
	/** Constructors and Destructors */

	/**
	*   @fn			Hitbox( float x, float y, int width, int length )
	*   @brief		Constructor function.
	*
	*	@param		x				Position on x axis to centre new Hitbox at.
	*	@param		y				Position on y axis to centre new Hitbox at.
	*	@param		width			Width of hitbox (measured as number of pixels on either side of the central pixel).
	*	@param		length			Length of hitbox (measured as number of pixels on either side of the central pixel).
	*
	*   @return		Initialized Hitbox object.
	*/
	Hitbox( float x, float y, int width, int length );

	/**
	*   @fn			Hitbox()
	*   @brief		Default constructor function.
	*
	*   @return		Initialized Hitbox object.
	*/
	Hitbox();

	/** Retrieval Methods */

	/**
	*   @fn			GetHitboxX()
	*   @brief		Returns current Hitbox centred x coordinate.
	*
	*   @return		Float value.
	*/
	float		GetHitboxX();
	
	/**
	*   @fn			GetHitboxY()
	*   @brief		Returns current Hitbox centred y coordinate.
	*
	*   @return		Float value.
	*/
	float		GetHitboxY();
	
	/**
	*   @fn			GetHitboxWidth()
	*   @brief		Returns width of Hitbox (measured as pixels on either side of central pixel).
	*
	*   @return		Float value.
	*/
	float		GetHitboxWidth();
	
	/**
	*   @fn			GetHitboxHeight()
	*   @brief		Returns height of Hitbox (measured as pixels on either side of central pixel).
	*
	*   @return		Float value.
	*/
	float		GetHitboxHeight();

	/** Manipulation Methods */

	/**
	*   @fn			MoveHitbox( float newXLocation, float newYLocation )
	*   @brief		Moves the centre of the hitbox to a new location.
	*
	*	@param		newXLocation	New horizontal location for central pixel of hitbox.
	*	@param		newYLocation	New vertical location for central pixel of hitbox.
	*/
	void		MoveHitbox( float newXLocation, float newYLocation );
	
	/**
	*   @fn			CheckForCollision( Hitbox target )
	*   @brief		Checks if the current Hitbox is inside another Hitbox at any location.
	*
	*	@param		target			Hitbox object to determine collision with.
	*
	*				True is returned if the current and target hitboxes are intersecting at any point, at this moment.
	*				Does not check along paths. If objects move in large enough spans per update cycle, an algorithm
	*				may be needed to prevent objects "skipping" over each other. 
	*
	*   @return		Boolian value.
	*/
	bool		CheckForCollision( Hitbox target );
};

#endif //HITBOX_H