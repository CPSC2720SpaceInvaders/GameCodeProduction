#include "actorEnemyBasic.h"


ActorEnemyBasic::ActorEnemyBasic(float xPosi, float yPosi, int hp, int _hitboxSize, int spriteLoc, int pts, bool right) : Actor(xPosi, yPosi, hp, _hitboxSize, spriteLoc), enemyScore(pts), moveRight(right), movedDown(false) {}
/*ActorEnemyBasic::ActorEnemyBasic(const ActorEnemyBasic& copyTarget) : Actor(copyTarget) {
	enemyScore = copyTarget.enemyScore;
	moveRight = copyTarget.moveRight;
	movedDown = copyTarget.movedDown;
}
ActorEnemyBasic& ActorEnemyBasic::operator=(const ActorEnemyBasic& copyTarget) {
	Actor::operator=(copyTarget);
	enemyScore = copyTarget.enemyScore;
	moveRight = copyTarget.moveRight;
	movedDown = copyTarget.movedDown;

	return *this;
}*/
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
