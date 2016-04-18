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
	bulletDirection = static_cast<directions_c>(dir);
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
	al_draw_line (xCoordinate, yCoordinate-5, xCoordinate, yCoordinate +5, al_map_rgb(255, 255, 255), 5.0);
}
