//Header comments

#ifndef ACTORPLAYER_H
#define ACTORPLAYER_H

//includes
#include <allegro5/allegro.h>
#include "actor.h"
#include "Hitbox.h"

class ActorPlayer : public Actor {
private:
   int playerScore, lives, maxBullets;

public:
	ActorPlayer(float xPosi, float yPosi, int hp, int _hitboxSize, const char *spriteLoc);
	int bulletControlCounter;
	void MoveActor(bool moveUp, bool moveDown, bool moveLeft, bool moveRight, const int MOVERATE_ACTORS);
	int GetScore();
	int GetMaxBullets();
	int GetLives();
	void UpdateScore(int scoreGained);
	void KillPlayer(const char *newSpriteLoc, float oldSpriteWidth, float oldSpriteHeight, float defaultXPosi, float defaultYPosi);
};

#endif
