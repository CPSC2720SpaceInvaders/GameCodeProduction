//Header comments
#ifndef ACTORENEMYBASIC_H
#define ACTORENEMYBASIC_H

//includes
#include <allegro5/allegro.h>
#include "actor.h"
#include "hitbox.h"

class ActorEnemyBasic public Actor {
  private:
   int enemyScore;
   bool moveRight;

  public:
   void MoveActor(int moveRate, const int );
   void InitializeBasicEnemy(ALLEGRO_BITMAP *enemySprite, float x, float y, int enemySpriteWidth, int enemySpriteHeight, int enemyHealth, int enemyScore);
