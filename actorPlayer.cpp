#include "actorPlayer.h"

void MoveActor(ALLEGRO_KEYBOARD_STATE keyboardState1, const int MOVERATE_ACTORS){

   if(al_key_down(&keyboardState1, ALLEGRO_KEY_DOWN)){
      yCoord += MOVERATE_ACTORS;

   } else if (al_key_down(&keyboardState1, ALLEGRO_KEY_UP)){
      yCoord -= MOVERATE_ACTORS;
   }

   if (al_key_down(&keyboardState1, ALLEGRO_KEY_RIGHT)){
      xCoord += MOVERATE_ACTORS;

   }else if (al_key_down(&keyboardState1, ALLEGRO_KEY_LEFT)){
      xCoord -= MOVERATE_ACTORS;
   }
   actorHitbox.MoveHitbox();
}

int GetScore(){
   return playerScore;
}void UpdateScore(int scoreGained){
   playerScore += scoreGained;
}void KillPlayer(float defaultXPosi, float defaultYPosi){
   if (CheckDead()){
      lives--;
      xCoord = defaultXPosi;
      yCoord = defaultYPosi;
   }
}
