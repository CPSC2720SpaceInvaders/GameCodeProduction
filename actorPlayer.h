//Header comments

#ifndef ACTORPLAYER_H
#define ACTORPLAYER_H

//includes
#include <allegro5/allegro.h>
#include "actor.h"
#include "hitbox.h"

class ActorPlayer public Actor {
  private:
   int playerScore, lives;
   
  public:
   void MoveActor(ALLEGRO_KEYBOARD_STATE keyboardState1, const int MOVERATE_ACTORS);
   int GetScore();
   void UpdateScore(int scoreGained);
   void KillPlayer();
}
