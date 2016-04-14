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
using namespace std;

//Private methods

//Public methods
int Projectile::GetXCoord(){
   return xCoordinate;
}int Projectile::GetYCoord(){
   return yCoordinate;  
}

/**
*	Additional comments about MoveProjectile method.
*/
void Projectile::MoveProjectile (const int MOVERATE_PROJECTILES, directions_c projDirection){
   if (projDirection == UP){
      yCoordinate -= MOVERATE_PROJECTILES;
   }else{
      yCoordinate += MOVERATE_PROJECTILES;
   }
   projectileHitbox.MoveHitbox(xCoordinate, yCoordinate);
}

void Projectile::DrawProjectile() {
	al_draw_bitmap(projectileSprite, xCoordinate, yCoordinate, NULL);
}
