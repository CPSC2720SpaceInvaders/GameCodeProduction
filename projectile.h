/**
*   @file		projectile.h
*   @brief		Definition of Projectile class.
*
*				This contains the definitions of the public and
*				private member variables, as well as all methods,
*				for the Projectile class, which handles
*				interactions between actors in the game.
*
*   @author		Tyler Bertram
*   @bug		No known bugs.
*/

#ifndef PROJECTILE_H__
#define PROJECTILE_H__

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include "Hitbox.h"

class Projectile {
protected:
	/** Protected member variables */
	float   xCoordinate, yCoordinate; /**< Determines location of projectile at a given time. */
	enum  directions_c { UP, DOWN }; 
	directions_c bulletDirection; /**< Determines whether a fired projectile should travel towards the top or bottom of the screen. */

public:
	/** Public member variables */
    Hitbox projectileHitbox; /**< Used to detect collisions between any two active objects.*/
	bool projInactive; /**< When false, the bullet is active, can collide and move. When false, the bullet is inactive, and is cleaned up at the start of the next update phase.*/

	/** Constructors and Destructors */

	/**
	*   @fn			Projectile( float xPosi, float yPosi, int dir, int _hitboxSize )
	*   @brief		Constructor function.
	*
	*	@param		xPosi			Position on x axis to place new Projectile at.
	*	@param		yPosi			Position on y axis to place new Projectile at.
	*	@param		dir				Direction new projectile should travel, up or down.
	*	@param		_hitboxSize		Size of the hitbox that should be constructed as a member.
	*
	*   @return		Initialized Projectile object.
	*/
	Projectile( float xPosi, float yPosi, int dir, int _hitboxSize );

	/**
	*	@fn			~Projectile()
	*	@brief		Virtual default constructor function.
	*
	*				Specifically defined as virtual here in order for child classes of Projectile to destruct correctly.
	*/
	virtual ~Projectile();

	/** Retrieval Methods */

   /**
   *   @fn			GetXCoord()
   *   @brief		Exposes and returns xCoordinate.
   *
   *   @return		Integer value.
   */
	float    GetXCoord();
	/**
	*    @fn		GetYCoord()
	*    @brief		Exposes and returns yCoordinate.
	*
	*    @return	Integer value.
	*/
	float    GetYCoord();

	/** Manipulation Methods */

	/**
	*    @fn		MoveProjectile( int moveRate, directions_c projDirection )
	*    @brief		Moves the single-pixel location of a projectile a given
	*				distance down or up. Modifies xCoordinate and yCoordinate.
	*
	*    @param		moveRate		Rate of movement for the projectile (in px).
	*    @param		projDirection	Direction of movement for projectile (up/down).
	*/
	void   MoveProjectile(const int MOVERATE_PROJECTILES);
	/**
	*   @fn			CheckForCollission( int moveRate, int targetXCoord, int targetYCoord )
	*   @brief		Checks along a specified movement path for a collision between
	*				a projectile and an actor.
	*
	*   @param		moveRate			Vertical rate of movement for projectile.
	*   @param		targetXCoord		Location of actor, horizontally.
	*   @param		targetYCoord		Location of actor, vertically.
	*    
	*	@return	Boolian value.
	*/
	void	DrawProjectile();
};

#endif //Projectile.h
