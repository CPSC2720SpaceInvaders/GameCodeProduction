/**
*   @file		Hitbox.cpp
*   @brief		Implementation of Hitbox class.
*
*				This contains the implementation of all methods
*				for the Hitbox class, which is the object 
*				responsible for detecting all collisions between 
*				objects	within the gamespace.
*
*   @author		Tyler Bertram
*   @bug		No known bugs.
*/

#include "Hitbox.h"

/** Constructors and Destructors */

/** 
* Additional comments about Hitbox constructors (if any).
*/
Hitbox::Hitbox(float x, float y, int width, int height): hitboxCentreX(x), hitboxCentreY(y), hitboxWidth(width), hitboxHeight(height) {}
Hitbox::Hitbox() {};

/** Retrieval Methods */

/** 
* Additional comments about GetHitboxX method (if any).
*/
float Hitbox::GetHitboxX() {
	return hitboxCentreX;
}

/**
* Additional comments about GetHitboxY method (if any).
*/
float Hitbox::GetHitboxY() {
	return hitboxCentreY;
}

/**
* Additional comments about GetHitboxWidth method (if any).
*/
float Hitbox::GetHitboxWidth() {
	return hitboxWidth;
}

/**
* Additional comments about GetHitboxHeight method (if any).
*/
float Hitbox::GetHitboxHeight() {
	return hitboxHeight;
}

/** Manipulation Methods */

/** 
* Additional comments about MoveHitbox method (if any).
*/
void Hitbox::MoveHitbox(float newXLocation, float newYLocation) {
	hitboxCentreX = newXLocation;
	hitboxCentreY = newYLocation;
}

/**
* Additional comments about CheckForCollision method (if any).
*/
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