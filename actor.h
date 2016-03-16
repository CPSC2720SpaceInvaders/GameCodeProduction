//Header comments

#ifndef ACTOR_H__
#define ACTOR_H__

//includes
#include <allegro5/allegro.h>

class Actor {
  Private:
   int xCoord, yCoord, curHealth, maxHealth;
   
  Public:
   //Retrieval methods
   int getXCoord();
   int getYCoord();
   int getCurrentHealth();
   int getMaxHealth();

   //Manipulation methods
   void moveActor(int moveRate);
   void modifyCurrentHealth(int damageTaken);
   bool checkDead();
}

#endif //actor.h
