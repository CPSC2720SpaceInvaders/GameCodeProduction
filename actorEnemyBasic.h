//Header comments
#ifndef ACTORENEMYBASIC_H
#define ACTORENEMYBASIC_H

//includes
#include <allegro5/allegro.h>
#include "actor.h"
#include "Hitbox.h"

class ActorEnemyBasic : public Actor {
private:
	int enemyScore;
	bool moveRight, movedDown;

public:
	//Constructors and Destructors
	ActorEnemyBasic(float xPosi, float yPosi, int hp, int _hitboxSize, const char *spritePath, int pts, bool right);
	bool isDead = false; /**< Used to exclude an object from collision while animating its death. */
	void MoveActor(const int MOVERATE_ACTORS, const int SCREEN_WIDTH);
};

#endif //ACTORENEMYBASIC_H
