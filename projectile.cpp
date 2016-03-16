//Header comments

//includes
#include "projectile.h"

//Private methods

//Public methods
int getXCoord(){
   return xCoordinate;
}int getYCoord(){
   return yCoordinate;  
}void moveProjectile (int moveRate, Directions_c projDirection){
   if (projDirection == UP){
      yCoordinate -= moveRate;
   }else{
      yCoordinate += moveRate;
   }
}bool checkForCollission(int targetXCoord, int targetYCoord){
   if (xCoordinate == targetXCoord && yCoordinate == targetYCoord){
      return true;
   }return false;
}
