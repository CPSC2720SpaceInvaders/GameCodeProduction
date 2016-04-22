/**
*		@file	actor.cpp
*		@brief	Implementation of Actor class.
*
*				This contains the implementations of the 
*				public and private methods for the Actor
*				class.
*
*		@author	Tyler Bertram
*		@bug	No known bugs.
*/

#include <allegro5/allegro.h>
#include "actor.h"

/** Constructors and Destructors */

/** Further comments about the constructors (if any). */
Actor::Actor(float xPosi, float yPosi, int hp, int _hitboxSize, int spriteLoc) : xCoord(xPosi), yCoord(yPosi), health(hp), hitboxSize(_hitboxSize), actorHitbox(xPosi, yPosi, hitboxSize, hitboxSize), spriteKey(spriteLoc) {}
Actor::Actor() {};

/** Retrieval methods */

/** Further comments about GetXCoord() (if any). */
float Actor::GetXCoord (){
   return xCoord;
}

/** Further comments about GetYCoord() (if any). */
float Actor::GetYCoord(){
   return yCoord;
}

/** Further comments about SetXCoord() (if any). */
void Actor::SetXCoord(float newCoord) {
	xCoord = newCoord;
}

/** Further comments about SetYCoord() (if any). */
void Actor::SetYCoord(float newCoord) {
	yCoord = newCoord;
}

/** Further comments about GetHealth() (if any). */
int Actor::GetHealth(){
   return health;
}

/** Further comments about GetSpriteKey() (if any). */
int Actor::GetSpriteKey() {
	return spriteKey;
}

/** Manipulation methods */

/** Further comments about ModifyHealth() (if any). */
void Actor::ModifyHealth(int damageTaken){
   health -= damageTaken;
}

/** Further comments about ChangeActorSprite() (if any). */
void Actor::ChangeActorSprite(int newSpriteLoc) {
	spriteKey = newSpriteLoc;
}

/** Further comments about CheckDead() (if any). */
bool Actor::CheckDead() {
	if (health <= 0) {
		return true;
	}return false;
}
