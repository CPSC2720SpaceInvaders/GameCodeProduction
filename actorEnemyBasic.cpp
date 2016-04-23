/**
*		@file	actorEnemyBasic.cpp
*		@brief	Implementation of ActorEnemyBasic class.
*
*				This contains the implementations of all methods
*				for the ActorEnemyBasic class, which handles
*				functionality specifically for the basic, or most
*				average/typical enemy type in the game, notably
*				also the only current enemy type in the game.
*
*		@author	Tyler Bertram
*		@bug	If an enemy unit is spawned within 25 pixels of either screen edge, due to the moveActor logic, it will careen towards the bottom of the screen instead of correctly moving. Don't place units within this space.
*/

#include "actorEnemyBasic.h"

/** Constructors and Destructors */

/** 
* Additional comments about ActorEnemyBasic constructors (if any).
*/
ActorEnemyBasic::ActorEnemyBasic(float xPosi, float yPosi, int hp, int _hitboxSize, int spriteLoc, int pts, bool right) : Actor(xPosi, yPosi, hp, _hitboxSize, spriteLoc), enemyScore(pts), moveRight(right), movedDown(false), isDead(false) {}

/** Manipulation Methods */

/**
* Due to the nature of the current movement logic, any enemy unit initialized within x coordinates 0 to 25 and 
* (SCREEN_WIDTH - 25) to SCREEN_WIDTH will simply dive down the screen at a rapid clip. This is a known bug
* but has not yet been solved. An easy solution is to not spawn basic enemies within those two buffers - be careful
* when calling the corresponding objectSpawner function.
*/
void ActorEnemyBasic::MoveActor(const int MOVERATE_ACTORS, const int SCREEN_WIDTH) {
	if (xCoord > 25 && xCoord < (SCREEN_WIDTH - 25) || movedDown) {
		if (moveRight) {
			xCoord += MOVERATE_ACTORS;
		}
		else {
			xCoord -= MOVERATE_ACTORS;
		}
		movedDown = false;
	}
	else {
		yCoord += 50;
		if (moveRight) {
			moveRight = false;
		}
		else {
			moveRight = true;
		}
		movedDown = true;
	}
	actorHitbox.MoveHitbox(xCoord, yCoord);
}
