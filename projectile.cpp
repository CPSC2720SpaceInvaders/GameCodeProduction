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
int GetXCoord(){
   return xCoordinate;
}int GetYCoord(){
   return yCoordinate;  
}

/**
*	Additional comments about MoveProjectile method.
*/
void MoveProjectile (const int MOVERATE_PROJECTILES, Directions_c projDirection){
   if (projDirection == UP){
      yCoordinate -= MOVERATE_PROJECTILES;
   }else{
      yCoordinate += MOVERATE_PROJECTILES;
   }
   projectileHitbox.MoveHitbox(xCoordinate, yCoordinate);
}

void DrawProjectile() {
	al_draw_bitmap(projectileSprite, 0, 0, xCoord, yCoord, NULL);
}
