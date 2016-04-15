//Header Comments
#ifndef ACTOR_H
#define ACTOR_H

//includes
#include <allegro5/allegro.h>
#include <string>
#include "Hitbox.h"

class Actor {
protected:
   float xCoord, yCoord;
   int health, hitboxSize, hitboxWidth;
   const char* spritePath;

   ALLEGRO_BITMAP *actorSprite;

public:
   Hitbox actorHitbox;

   //Constructors and Destructors
   Actor(float xPosi, float yPosi, int hp, int _hitboxSize, const char *spritePath);
   Actor(const Actor&);
   Actor& operator=(const Actor&);
   virtual ~Actor();

   //Retrieval methods
   float GetXCoord();
   float GetYCoord();
   int GetHealth();

   //Manipulation methods
   void MoveActor();
   void ModifyHealth(int damageTaken);
   void ChangeActorSprite(const char *newSpriteLoc);
   void DrawActor();
   bool CheckDead();
};

#endif //actor.h
