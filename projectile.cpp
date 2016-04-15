/**		
*		@file	projectile.cpp
*		@brief	Implementation of projectile class.
*		
*				This contains the implementation for the methods
*				of the Projectile class, which handles
*				the vectors of interaction between actors
*				in the game.
*				
*		@author	Tyler Bertram
*		@bug	No known bugs (uncompiled, untested).
*/

//includes
#include "projectile.h"

//Private methods

//Public methods
Projectile::Projectile(float xPosi, float yPosi, int dir, const char *spriteLoc, int _hitboxSize) : xCoordinate(xPosi), yCoordinate(yPosi), projectileHitbox(xPosi, yPosi, _hitboxSize, _hitboxSize) {
	projectileSprite = al_load_bitmap(spriteLoc);
	bulletDirection = static_cast<directions_c>(dir);
}
Projectile::Projectile(const Projectile& copyTarget) {
	xCoordinate = copyTarget.xCoordinate;
	yCoordinate = copyTarget.yCoordinate;
	bulletDirection = copyTarget.bulletDirection;
	spritePath = copyTarget.spritePath;
	projectileHitbox = copyTarget.projectileHitbox;

	projectileSprite = al_load_bitmap(spritePath);
}
Projectile& Projectile::operator=(const Projectile& copyTarget) {
	xCoordinate = copyTarget.xCoordinate;
	yCoordinate = copyTarget.yCoordinate;
	bulletDirection = copyTarget.bulletDirection;
	spritePath = copyTarget.spritePath;
	projectileHitbox = copyTarget.projectileHitbox;

	projectileSprite = al_load_bitmap(spritePath);
	return *this;
}
Projectile::~Projectile() {
	al_destroy_bitmap(projectileSprite);
}
float Projectile::GetXCoord(){
   return xCoordinate;
}float Projectile::GetYCoord(){
	return yCoordinate;  
}

/**
*	Additional comments about MoveProjectile method.
*/
void Projectile::MoveProjectile (const int MOVERATE_PROJECTILES){
	if (bulletDirection == UP){
      yCoordinate += MOVERATE_PROJECTILES;
   }else{
      yCoordinate -= MOVERATE_PROJECTILES;
   }
   projectileHitbox.MoveHitbox(xCoordinate, yCoordinate);
}

void Projectile::DrawProjectile() {
	al_draw_bitmap(projectileSprite, xCoordinate, yCoordinate, NULL);
}
