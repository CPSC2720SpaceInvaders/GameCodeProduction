#include "Hitbox.h"

Hitbox::Hitbox(float x, float y, int width, int height): hitboxCentreX(x), hitboxCentreY(y), hitboxWidth(width), hitboxHeight(height) {}
Hitbox::Hitbox() {};

float Hitbox::GetHitboxX() {
	return hitboxCentreX;
}

float Hitbox::GetHitboxY() {
	return hitboxCentreY;
}

float Hitbox::GetHitboxWidth() {
	return hitboxWidth;
}

float Hitbox::GetHitboxHeight() {
	return hitboxHeight;
}

void Hitbox::MoveHitbox(float newXLocation, float newYLocation) {
	hitboxCentreX = newXLocation;
	hitboxCentreY = newYLocation;
}
bool Hitbox::CheckForCollision(Hitbox target) {
	if ((hitboxCentreY + hitboxHeight) < (target.GetHitboxY() - target.GetHitboxHeight()) || (hitboxCentreY - hitboxHeight) > (target.GetHitboxY() + target.GetHitboxHeight())) {
		return false;
	}
	else if ((hitboxCentreX + hitboxWidth) < (target.GetHitboxX() - target.GetHitboxWidth()) || (hitboxCentreX - hitboxWidth) > (target.GetHitboxX() + target.GetHitboxWidth())) {
		return false;
	}
	else {
		return true;
	}
}