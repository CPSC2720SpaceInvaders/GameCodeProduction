//Header comments

#ifndef ACTORPLAYER_H
#define ACTORPLAYER_H

//includes
#include <allegro5/allegro.h>
#include "actor.h"
#include "hitbox.h"

class ActorPlayer public Actor {
  private:
   int playerScore, lives, maxBullets, bulletControlCounter;
   
  public:
   void MoveActor(ALLEGRO_KEYBOARD_STATE keyboardState1, const int MOVERATE_ACTORS);
   int GetScore();
   int GetLives();
   void UpdateScore(int scoreGained);
   void KillPlayer(ALLEGRO_BITMAP *oldSprite, float oldSpriteWidth, float oldSpriteHeight, float defaultXPosi, float defaultYPosi);
}
