//Header comments

#ifndef ACTOR_H__
#define ACTOR_H__

//includes
#include <allegro5/allegro.h>

class Actor {
  Private:
   int xCoord, yCoord, curHealth, maxHealth;
   ALLEGRO_BITMAP *actorSprite;
   
  Public:
   //Retrieval methods
   int getXCoord();
   int getYCoord();
   int getCurrentHealth();
   int getMaxHealth();

   //Manipulation methods
   void moveActorHorizon(int moveRate);
   void moveActorVert(int moveRate);
   void modifyCurrentHealth(int damageTaken);
   bool checkDead();			
   void drawActor();
   void destroyActor();
}

#endif //actor.h