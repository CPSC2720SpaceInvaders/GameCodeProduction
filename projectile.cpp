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
float	GetXCoord(){
	return xCoordinate;
}float	GetYCoord(){
	return yCoordinate;  
}

/**
*	Additional comments about MoveProjectile method.
*/
void	MoveProjectile (int moveRate, Directions_c projDirection){
   if (projDirection == UP) {
		yCoordinate -= moveRate;
   }else {
		yCoordinate += moveRate;
   }
}

/**
* Additional comments about DrawProjectile method.
*/
void DrawProjectile(){
   al_draw_bitmap(bulletSprite, xCoordinate, yCoordinate);
}

/**
*	Additional comments about CheckForCollission method.
*/
bool CheckForCollision(int moveRate, int targetXCoord, int targetYCoord, projectileDirection_t projDirection){
   if (xCoordinate == targetXCoord || xCoordinate == (targetXCoord - 1) || xCoordinate == (targetXCoord + 1)){
      if ( targetYCoord == yCoordinate){
	 return true;
      }else if (projDirection == UP && (yCoordinate < targetYCoord && targetYCoord < (yCoordinate + moveRate))){
	 return true;
      }else if (projDirection == DOWN && (yCoordinate > targetYCoord && targetYCoord > (yCoordinate - moveRate))){
	 return true;
      }else {
	 return false;
      }

}
