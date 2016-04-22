/**		
*		@file	projectile.cpp
*		@brief	Implementation of Projectile class.
*		
*				This contains the implementation for the methods
*				of the Projectile class, which handles
*				the vectors of interaction between actors
*				in the game.
*				
*		@author	Tyler Bertram
*		@bug	No known bugs.
*/

//includes
#include "projectile.h"

/** Private Methods */

/** Public Methods */
Projectile::Projectile(float xPosi, float yPosi, int dir, int _hitboxSize) : xCoordinate(xPosi), yCoordinate(yPosi), projectileHitbox(xPosi, yPosi, _hitboxSize, _hitboxSize), projInactive(false) {
	bulletDirection = static_cast<directions_c>(dir);
}

float Projectile::GetXCoord(){
   return xCoordinate;
}

float Projectile::GetYCoord(){
	return yCoordinate;  
}

/**
*	Additional comments about MoveProjectile method (if any).
*/
void Projectile::MoveProjectile (const int MOVERATE_PROJECTILES){
	if (bulletDirection == UP){
      yCoordinate += MOVERATE_PROJECTILES;
   }else{
      yCoordinate -= MOVERATE_PROJECTILES;
   }
   projectileHitbox.MoveHitbox(xCoordinate, yCoordinate);
}

/**
*	Additional comments about DrawProjectile method (if any).
*/
void Projectile::DrawProjectile() {
	al_draw_line (xCoordinate, yCoordinate-5, xCoordinate, yCoordinate +5, al_map_rgb(255, 255, 255), 5.0);
}
