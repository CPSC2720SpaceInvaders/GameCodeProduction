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

/** Additional comments about the constructors (if any). */
Actor::Actor(float xPosi, float yPosi, int hp, int _hitboxSize, int spriteLoc) : xCoord(xPosi), yCoord(yPosi), health(hp), hitboxSize(_hitboxSize), actorHitbox(xPosi, yPosi, hitboxSize, hitboxSize), spriteKey(spriteLoc) {}
Actor::Actor() {};

/**
* Additional comments about ~Actor virtual destructor (if any).
*/
Actor::~Actor() {}

/** Retrieval methods */

/** 
* Additional comments about GetXCoord() (if any). 
*/
float Actor::GetXCoord (){
   return xCoord;
}

/** 
* Additional comments about GetYCoord() (if any). 
*/
float Actor::GetYCoord(){
   return yCoord;
}

/** 
* Additional comments about SetXCoord() (if any). 
*/
void Actor::SetXCoord(float newCoord) {
	xCoord = newCoord;
}

/** 
* Additional comments about SetYCoord() (if any). 
*/
void Actor::SetYCoord(float newCoord) {
	yCoord = newCoord;
}

/** 
* Additional comments about GetHealth() (if any). 
*/
int Actor::GetHealth(){
   return health;
}

/** 
* Additional comments about GetSpriteKey() (if any). 
*/
int Actor::GetSpriteKey() {
	return spriteKey;
}

/** Manipulation methods */

/** 
* Additional comments about ModifyHealth() (if any). 
*/
void Actor::ModifyHealth(int damageTaken){
   health -= damageTaken;
}

/** 
* Additional comments about ChangeActorSprite() (if any). 
*/
void Actor::ChangeActorSprite(int newSpriteLoc) {
	spriteKey = newSpriteLoc;
}

/** 
* Additional comments about CheckDead() (if any). 
*/
bool Actor::CheckDead() {
	if (health <= 0) {
		return true;
	}return false;
}
