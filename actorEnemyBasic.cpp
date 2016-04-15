#include "actorEnemyBasic.h"


ActorEnemyBasic::ActorEnemyBasic(float xPosi, float yPosi, int hp, int _hitboxSize, const char *spriteLoc, int pts, bool right) : Actor(xPosi, yPosi, hp, _hitboxSize, spriteLoc), enemyScore(pts), moveRight(right), movedDown(false) {}
void ActorEnemyBasic::MoveActor(const int MOVERATE_ACTORS, const int SCREEN_WIDTH) {
	if (xCoord > 25 && xCoord < 775 || movedDown) {
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
