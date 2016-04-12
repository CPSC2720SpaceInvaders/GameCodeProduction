#include "Hitbox.h"

float GetHitboxX() {
	return hitboxCentreX;
}

float GetHitboxY() {
	return hitboxCentreY;
}

float GetHitboxWidth() {
	return hitboxWidth;
}

float GetHitboxHeight() {
	return hitboxHeight;
}

void MoveHitbox(float newXLocation, float newYLocation) {
	hitboxCentreX = newXLocation;
	hitboxCenterY = newYLocation;
}
bool CheckForCollision(Hitbox target) {
	if ((hitboxCentreY + hitboxHeight) < (target.GetHitboxY() - target.GetHitboxHeight()) && (hitboxCentreY - hitboxHeight) > (target.GetHitboxY() + target.GetHitboxHeight())) {
		return false;
	}
	else if ((hitboxCentreX + hitboxWidth) < (target.GetHitboxX() - target.GetHitboxWidth()) && (hitboxCentreX - hitboxWidth) > (target.GetHitboxX() + target.GetHitboxWidth())) {
		return false;
	}
	else {
		return true;
	}
}