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
void MoveProjectile (int moveRate, Directions_c projDirection){
   if (projDirection == UP){
      yCoordinate -= moveRate;
   }else{
      yCoordinate += moveRate;
   }
}

/**
*	Additional comments about CheckForCollission method.
*/
bool CheckForCollision(int moveRate, int targetXCoord, int targetYCoord){
   if (xCoordinate == targetXCoord && yCoordinate == targetYCoord){
      return true;
   }return false;
}
