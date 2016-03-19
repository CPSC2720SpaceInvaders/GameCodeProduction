//Header comments

//includes
#include <allegro5/allegro.h>
#include "actor.h"

//Constructors
Actor (int xC, int yC, int curH, int maxH, ALLEGRO_BITMAP *actSprite) : xCoord(xC), yCoord(yC), curHealth(curH), maxHealth(maxH), actorSprite(actSprite) { };
Actor (int xC, int yC, int curH, ALLEGRO_BITMAP *actSprite) : xCoord(xC), yCoord(yC), curHealth(curH), maxHealth(1), actorSprite(actSprite) { };
Actor (int xC, int yC, ALLEGRO_BITMAP *actSprite) : xCoord(xC), yCoord(yC), curHealth(1), maxHealth(1), actorSprite(actSprite) { };

//Retrieval methods
int getXCoord (){
   return xCoord;
}int getYCoord(){
   return YCoord;
}int getCurrentHealth(){
   return curHealth;
}int getMaxHealth(){
   return maxHealth;
}

//Manipulation methods
void moveActorHorizon(int moveRate){
   xCoord += moveRate;
}void moveActorVert(int moveRate){
   yCoord += moveRate;
}void modifyCurrentHealth(int damageTaken){
   if (curHealth >= damageTaken){
      curHealth += damageTaken;
   }else {
      curHealth = 0;
   }
}bool checkDead(){
   if (curHealth <= 0){
      return true;
   }return false;
}void drawActor( ) {
   al_draw_bitmap(actorSprite, xCoord, yCoord);
}