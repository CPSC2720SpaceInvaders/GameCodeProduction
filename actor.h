//Header Comments
#ifndef ACTOR_H
#define ACTOR_H

//includes
#include <allegro5/allegro.h>
#include "Hitbox.h"

class Actor {
private:
   float xCoord, yCoord, spriteWidth, spriteHeight;
   int health, hitboxSize, hitboxWidth;

   ALLEGRO_BITMAP *actorSprite;

public:
   Hitbox actorHitbox;

   //Retrieval methods
   float GetXCoord();
   float GetYCoord();
   int GetHealth();

   //Manipulation methods
   void MoveActor();
   void ModifyHealth(int damageTaken);
   void ChangeActorSprite(ALLEGRO_BITMAP *newSprite, float newSpriteWidth, float newSpriteHeight);
   void DrawActor();
   bool CheckDead();
   void DeleteActorSprite();
};

#endif //actor.h
