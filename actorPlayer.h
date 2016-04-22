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
   int playerScore, lives, maxBullets;

public:
	/** Public Member Variables */
	int bulletControlCounter;

	/** Constructors and Destructors */
	ActorPlayer(float xPosi, float yPosi, int hp, int _hitboxSize, int spriteLoc);

	/** Retrieval Methods */
	int GetScore();
	int GetMaxBullets();
	int GetLives();

	/** Manipulation Methods */
	void MoveActor(bool moveUp, bool moveDown, bool moveLeft, bool moveRight, const int MOVERATE_ACTORS);
	void UpdateScore(int scoreGained);
	void KillPlayer(int newSpriteLoc, float oldSpriteWidth, float oldSpriteHeight, float defaultXPosi, float defaultYPosi);
};

#endif
