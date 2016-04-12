#include "actorEnemyBasic.h"

void MoveActor(const int MOVERATE_ACTORS, const int SCREEN_WIDTH) {
	if (xCoord > 25 && xCoord < 775) {
		if (moveRight) {
			xCoord += MOVERATE_ACTORS;
		}
		else {
			xCoord -= MOVERATE_ACTORS;
		}
	}
	else {
		yCoord -= MOVERATE_ACTORS;
		if (moveRight) {
			moveRight = false;
		}
		else {
			moveRight = true;
		}
	}
	actorHitbox.MoveHitbox(xCoord, yCoord);
}
