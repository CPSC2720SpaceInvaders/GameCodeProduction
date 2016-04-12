//Header comments
#ifndef HITBOX_H
#define HITBOX_H

//includes
#include <iostream>

class Hitbox {
private:
	//Width and height are a measure of how many pixels the hitbox comprises on /each side/ of the central coordinate.
	//So a width/height 1 hitbox is a 3x3 square.
	float		hitboxCentreX, hitboxCentreY, hitboxWidth, hitboxHeight;

public:
	float		GetHitboxX();
	float		GetHitboxY();
	float		GetHitboxWidth();
	float		GetHitboxHeight();
	void		MoveHitbox(float newXLocation, float newYLocation);
	bool		CheckForCollision(Hitbox target);
};

#endif //HITBOX_H