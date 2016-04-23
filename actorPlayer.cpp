/**
*		@file	actorPlayer.cpp
*		@brief	Implementation of ActorPlayer class.
*
*				This contains the implementation of all methods
*				for the ActorPlayer class, which handles all
*				internal functionality for the player's
*				ship in the game.
*
*		@author	Tyler Bertram
*		@bug	No known bugs.
*/

#include "actorPlayer.h"

/** Constructors and Destructors */

/** 
* playerScore is initialized to 0 for obvious reasons. The constructor should be expanded however to allow initialization of lives.
* bulletControlCounter is set to 5 by default, as this is the value checked for in main when allowing the player to fire. Ergo,
* a newly constructed ActorPlayer object can fire on its first update cycle if the player chooses.
*/
ActorPlayer::ActorPlayer( float xPosi, float yPosi, int hp, int _hitboxSize, int spriteLoc ) : Actor( xPosi, yPosi, hp, _hitboxSize, spriteLoc ), playerScore( 0 ), lives( 3 ), bulletControlCounter( 5 ) {}

/** 
* The magic numbers used here correspond to the screen edges necessary to make the player stop 10 pixels from the screen edge.
* A file should really be defined to allow access to those variable values for this purpose, as it would avoid needing to pass
* four+ const int vars to each function that needs to know (which keeps the arguments much tidier).
*/
void ActorPlayer::MoveActor( bool moveUp, bool moveDown, bool moveLeft, bool moveRight, const int MOVERATE_ACTORS ) {
	if (moveUp) {
		if (yCoord <= 10) {}
		else {
			yCoord -= MOVERATE_ACTORS;
		}
	}
	else if (moveDown) {
		if (yCoord >= 750) {}
		else {
			yCoord += MOVERATE_ACTORS;
		}
	}
	if (moveRight) {
		if (xCoord <= 10) {}
		else {
			xCoord -= MOVERATE_ACTORS;
		}
	}
	else if (moveLeft) {
		if (xCoord >= 1140) {}
		else {
			xCoord += MOVERATE_ACTORS;
		}
	}
	actorHitbox.MoveHitbox(xCoord, yCoord);
}

/** 
* Additional comments about GetScore method (if any).
*/
int ActorPlayer::GetScore(){
   return playerScore;
}
/** 
* Additional comments about GetLives method (if any).
*/
int ActorPlayer::GetLives(){
	return lives;
}

/** 
* Additional comments about UpdateScore method (if any).
*/
void ActorPlayer::UpdateScore( int scoreGained ){
   playerScore += scoreGained;
}

/**
* Additional comments about SetLives method (if any).
*/
void ActorPlayer::SetLives( int newLifeTotal ) {
	lives = newLifeTotal;
}

/**
* This entire function should be rewritten and can probably be replaced wholesale by a series of getter/setter functions
* and existing code calls external to the class. It probably doesn't need to be here, but it serves its purpose in the code
* as it stands.
*/
void ActorPlayer::KillPlayer( int newSpriteLoc, float defaultXPosi, float defaultYPosi ) {
      lives--;
	  health = 1;
	  ChangeActorSprite(newSpriteLoc);
      xCoord = defaultXPosi;
      yCoord = defaultYPosi;
}
