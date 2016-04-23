/**
*		@file	actorEnemyBasic.h
*		@brief	Definition of ActorEnemyBasic class.
*
*				This contains the definitions of the public and
*				private member variables, as well as all methods,
*				for the ActorEnemyBasic class, which handles 
*				functionality specifically for the basic, or most
*				average/typical enemy type in the game, notably
*				also the only current enemy type in the game.
*
*		@author	Tyler Bertram
*		@bug	If an enemy unit is spawned within 25 pixels of either screen edge, due to the moveActor logic, it will careen towards the bottom of the screen instead of correctly moving. Don't place units within this space.
*/

#ifndef ACTORENEMYBASIC_H
#define ACTORENEMYBASIC_H

#include <allegro5/allegro.h>
#include "actor.h"
#include "Hitbox.h"

class ActorEnemyBasic : public Actor {
private:
	
	/** Private Member Variables */
	
	int		enemyScore;				/**< The worth of the enemy when killed. */
	bool	moveRight, movedDown;	/**< Boolian vars used to control movement. */

public:

	/** Public Member Variables */
	
	bool	isDead = false;			/**< Used to exclude an object from collision while animating its death. */

	/** Constructors and Destructors */

	/**
	*   @fn			ActorEnemyBasic( float xPosi, float yPosi, int hp, int _hitboxSize, int spriteLoc, int pts, bool right )
	*   @brief		Constructor function.
	*
	*	@param		xPosi			Position on x axis to place new Actor at.
	*	@param		yPosi			Position on y axis to place new Actor at.
	*	@param		hp				Health total of the new Actor.
	*	@param		_hitboxSize		Size of the hitbox that should be constructed as a member.
	*	@param		spriteLoc		Location in the sprite index of the actor's sprite bitmap.
	*	@param		pts				Value of enemy when killed.
	*	@param		right			Whether the enemy should start moving right(true) or left(false).
	*
	*   @return		Initialized ActorEnemyBasic object.
	*/
	ActorEnemyBasic( float xPosi, float yPosi, int hp, int _hitboxSize, int spriteLoc, int pts, bool right );

	/** Manipulation Methods */

	/**
	*   @fn			MoveActor( const int MOVERATE_ACTORS, const int SCREEN_WIDTH )
	*   @brief		Constructor function.
	*
	*				Enemy will move right across the gamespace until it comes within
	*				25 pixels of the edge, at which point it will move its height down
	*				and reverse movement towards the opposite edge. Loops like this as
	*				long as the enemy is active.
	*
	*	@param		MOVERATE_ACTORS	Speed at which actors move through the gamespace.
	*	@param		SCREEN_WIDTH	Width of the screen.
	*
	*/
	void MoveActor( const int MOVERATE_ACTORS, const int SCREEN_WIDTH );
};

#endif //ACTORENEMYBASIC_H
