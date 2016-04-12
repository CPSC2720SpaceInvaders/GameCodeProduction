/**
*   @file projectile.h
*   @brief  Definition of projectile class.
*
*       This contains the definitions of the public and
*       private member variables, as well as all methods,
*       for the Projectile class, which handles
*       interactions between actors in the game.
*
*   @author Tyler Bertram
*   @bug  No known bugs (uncompiled, untested).
*/

#ifndef PROJECTILE_H__
#define PROJECTILE_H__

#include <allegro5/allegro.h>
#include "Hitbox.h"

class Projectile {
private:
	//Member variables
	int   xCoordinate, yCoordinate; /**< Determines location of projectile at a given time. */
	enum  directions_c { UP, DOWN }; /**< Determines whether a fired projectile should travel towards the top or bottom of the screen. */

	ALLEGRO_BITMAP *projectileSprite;


public:
    Hitbox projectileHitbox;

	//Retrieval methods
   /**
   *   @fn     GetXCoord()
   *   @brief    Exposes and returns xCoordinate.
   *   @return   integer value.
   */
	int    GetXCoord();
	/**
	*    @fn     GetYCoord()
	*    @brief    Exposes and returns yCoordinate.
	*    @return   Integer value.
	*/
	int    GetYCoord();

	//Manipulation methods
	/**
	*    @fn     MoveProjectile( int moveRate, directions_c projDirection )
	*    @brief    Moves the single-pixel location of a projectile a given
	*          distance down or up. Modifies xCoordinate and yCoordinate.
	*    @param    moveRate    Rate of movement for the projectile (in px).
	*    @param    projDirection Direction of movement for projectile (up/down).
	*/
	void   MoveProjectile(const int MOVERATE_PROJECTILES, directions_c projDirection);
	/**
	*    @fn     CheckForCollission( int moveRate, int targetXCoord, int targetYCoord )
	*    @brief    Checks along a specified movement path for a collision between
	*          a projectile and an actor.
	*    @param    moveRate    Vertical rate of movement for projectile.
	*    @param    targetXCoord  Location of actor, horizontally.
	*    @param    targetYCoord  Location of actor, vertically.
	*    @return   Boolian value.
	*/
	void	DrawProjectile();
};

#endif //Projectile.h
