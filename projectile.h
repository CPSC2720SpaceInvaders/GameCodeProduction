//Header comments

#ifndef PROJECTILE_H__
#define PROJECTILE_H__

//includes
#include <allegro5/allegro.h>

class Projectile {
  Private:
   //Member variables
   int xCoordinate, yCoordinate;
   enum Directions_c (UP, DOWN);
   
  Public:
   //Retrieval methods
   int getXCoord();
   int getYCoord();

   //Manipulation methods
   void moveProjectile(int moveRate, Directions_c projDirection);
   bool checkForCollission(int targetXCoord, int targetYCoord);
}

#endif //Projectile.h
