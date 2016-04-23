/**
*		@file	actorPlayer.h
*		@brief	Definition of ActorPlayer class.
*
*				This contains the definitions of the public and
*				private member variables, as well as all methods,
*				for the ActorPlayer class, which handles all
*				internal functionality for the player's 
*				ship in the game.
*
*		@author	Tyler Bertram
*		@bug	No known bugs.
*/

#ifndef ACTORPLAYER_H
#define ACTORPLAYER_H

#include <allegro5/allegro.h>
#include "actor.h"
#include "Hitbox.h"

class ActorPlayer : public Actor {
private:
	/** Private Member Variables */
	int		playerScore, lives;		/**< playerScore is not used currently, but would accumulate the score values of all killed enemies. */
									/**< lives is the number of times a player can safely die remaining. (3 lives permit the player to die 3 times - the fourth death will game over. */

public:
	/** Public Member Variables */
	int		bulletControlCounter; /**< Used to count update cycles, such that a player must wait at least x update cycles before firing a second projectile. */

	/** Constructors and Destructors */

	/**
	*   @fn			ActorPlayer( float xPosi, float yPosi, int hp, int _hitboxSize, int spriteKey )
	*   @brief		Constructor function.
	*
	*	@param		xPosi			Position on x axis to place new ActorPlayer at.
	*	@param		yPosi			Position on y axis to place new ActorPlayer at.
	*	@param		hp				Health total of the new ActorPlayer.
	*	@param		_hitboxSize		Size of the hitbox that should be constructed as a member.
	*	@param		spriteLoc		Location in the sprite index of the ActorPlayer sprite bitmap.
	*
	*   @return		Initialized ActorPlayer object.
	*/
	ActorPlayer( float xPosi, float yPosi, int hp, int _hitboxSize, int spriteLoc );

	/** Retrieval Methods */

	/**
	*   @fn			GetScore()
	*   @brief		Returns current player score amount.
	*
	*   @return		Integer value.
	*/
	int GetScore();
	
	/**
	*   @fn			GetLives()
	*   @brief		Returns current player life total.
	*
	*   @return		Integer value.
	*/
	int GetLives();

	/** Manipulation Methods */

	/**
	*   @fn			MoveActor( )
	*   @brief		When passed a series of bools, moves the actor appropriately.
	*
	*	@param		moveUp				If true, the actor will move upwards a distance defined by the moverate.
	*	@param		moveDown			If true, the actor will move downwards a distance defined by the moverate.
	*	@param		moveLeft			If true, the actor will move left a distance defined by the moverate.
	*	@param		moveRight			If true, the actor will move right a distance defined by the moverate.
	*	@param		MOVERATE_ACTORS		The number of pixels to move the actor's location in a given direction.
	*
	*				This function is intended to be fed information based on keypress values. For an example
	*				implementation, see the main function.
	*/
	void MoveActor( bool moveUp, bool moveDown, bool moveLeft, bool moveRight, const int MOVERATE_ACTORS );
	
	/**
	*   @fn			UpdateScore( int scoreGained )
	*   @brief		Updates the player's score by a specified amount.
	*
	*	@param		scoreGained		Increases playerScore by the specified amount. If negative, will decrease playerScore instead.
	*
	*				This function is not currently used.
	*/
	void UpdateScore( int scoreGained );

	/**
	*   @fn			SetLives( int newLifeTotal )
	*   @brief		Sets the player's life total to a new value.
	*
	*	@param		newLifeTotal	The new value to assign to lives member.
	*/
	void SetLives( int newLifeTotal );
	
	/**
	*   @fn			KillPlayer( int newSpriteLoc, float defaultXPosi, float defaultYPosi )
	*   @brief		Decrements lives by 1, changes the player spriteIndex key, and moves the player back to the starting position.
	*
	*	@param		newSpriteLoc	The key to the player's new sprite (can be the same as the current sprite if desired).
	*	@param		defaultXPosi	The location on the x axis to place the player (should usually be the same as the place the player starts initially).
	*	@param		defaultYPosi	The location on the y axis to place the player (should usually be the same as the place the player starts initially).
	*
	*				This code needs to be rewritten, not for functionality (it works fine) but because it's ugly and stylistically undesirable. However,
	*				time constraints mean it won't be.
	*/
	void KillPlayer( int newSpriteLoc, float defaultXPosi, float defaultYPosi );
};

#endif
