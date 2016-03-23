//Header comments

//includes
#include <allegro5/allegro.h>
#include "actor.h"

//Constructors
Actor (int xC, int yC, int curH, int maxH) : xCoord(xC), yCoord(yC), curHealth(curH), maxHealth(maxH) { };
Actor (int xC, int yC, int curH) : xCoord(xC), yCoord(yC), curHealth(curH), maxHealth(1) { };
Actor (int xC, int yC) : xCoord(xC), yCoord(yC), curHealth(1), maxHealth(1);

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
void moveActor(int moveRate){
   xCoord += moveRate;
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
}
