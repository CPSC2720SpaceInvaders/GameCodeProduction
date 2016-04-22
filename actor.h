/**
*		@file	actor.h
*		@brief	Definition of Actor class.
*
*				This contains the definitions of the public and
*				private member variables, as well as all methods,
*				for the Actor class, which handles basic 
*				functionality for any active "character" or
*				similar in the game area (players, enemies, etc.).
*
*		@author	Tyler Bertram
*		@bug	No known bugs.
*/

#ifndef ACTOR_H
#define ACTOR_H

#include <allegro5/allegro.h>
#include <string>
#include "Hitbox.h"
#include <memory>

class Actor {
protected:
	/** Protected member variables */
   float	xCoord, yCoord;						/**< Determines the location of an actor at a given time. */
   int		health, hitboxSize, hitboxWidth;	/**< health: Actor's current HP. hitboxSize/Width: Length/width of the member hitbox object. */
   int		spriteKey;							/**< Matches the desired sprite's key within the sprite std::map wrapper, used when drawing the actor. */

public:
	/** Public member variables */
	
	Hitbox	actorHitbox;						/**< Used for collision detection. */

	/** Constructors and Destructors */

	/**
	*   @fn			Actor( float xPosi, float yPosi, int hp, int _hitboxSize, int spriteKey )
	*   @brief		Constructor function.
	*
	*	@param		xPosi			Position on x axis to place new Actor at.
	*	@param		yPosi			Position on y axis to place new Actor at.
	*	@param		hp				Health total of the new Actor.
	*	@param		_hitboxSize		Size of the hitbox that should be constructed as a member.
	*	@param		spriteKey		Location in the sprite index of the actor's sprite bitmap.
	*
	*   @return		Initialized Actor object.
	*/
	Actor( float xPosi, float yPosi, int hp, int _hitboxSize, int spriteKey );

	/**
	*   @fn			Actor()
	*   @brief		Default constructor function.
	*
	*   @return		Initialized Actor object.
	*/
	Actor();

	/** Retrieval Methods */

	/**
	*   @fn			GetXCoord()
	*   @brief		Getter function for xCoord.
	*
	*   @return		Float value of xCoord var.
	*/
	float GetXCoord();
	
	/**
	*   @fn			GetYCoord()
	*   @brief		Getter function for yCoord.
	*
	*   @return		Float value of yCoord var.
	*/
	float GetYCoord();
	
	/**
	*   @fn			GetHealth()
	*   @brief		Getter function for health.
	*
	*   @return		Integer value of health var.
	*/
	int GetHealth();
	
	/**
	*   @fn			GetSpriteKey()
	*   @brief		Getter function for spriteKey.
	*
	*   @return		Integer value of spriteKey var.
	*/
	int GetSpriteKey();

	/**< Manipulation Methods */
	
	/**
	*   @fn			MoveActor()
	*   @brief		Empty movement function, overloaded by inheriting classes.
	*
	*				Specific actor types (player, enemies, etc.) should overload
	*				this function with that actor type's movement logic.
	*				Would have been implemented as a virtual function, however
	*				different child classes need different parameters.
	*/
	void MoveActor();
	
	/**
	*   @fn			SetXCoord( float newCoord )
	*   @brief		Setter function for xCoord var.
	*
	*	@param		newCoord		Designates the new horizontal location for the
	*								actor object.
	*/
	void SetXCoord( float newCoord );
	
	/**
	*   @fn			SetYCoord( float newCoord )
	*   @brief		Setter function for yCoord var.
	*
	*	@param		newCoord		Designates the new vertical location for the
	*								actor object.
	*/
	void SetYCoord( float newCoord );
	
	/**
	*   @fn			ModifyHealth( int damageTaken )
	*   @brief		Modifies the health variable by a certain amount, mostly used
	*				for damaging actors (hence the arg name).
	*
	*	@param		damageTaken		The amount to subtract from the Actor's health.
	*								Will heal the Actor if negative.
	*/
	void ModifyHealth( int damageTaken );
	
	/**
	*   @fn			ChangeActorSprite(int newSpriteLoc)
	*   @brief		Changes the spriteKey index location for the actor's sprite when
	*				drawn.
	*
	*	@param		newSpriteLoc	The new 3-digit index for the spriteIndex map.
	*/
	void ChangeActorSprite( int newSpriteLoc );
	
	/**
	*   @fn			CheckDead()
	*   @brief		Checks if HP is at/below 0, if so, returns true to allow death
	*				resolution logic to occur. Also sets HP to 0 if below.
	*
	*   @return		Boolian value.
	*/
	bool CheckDead();
};

#endif //actor.h
