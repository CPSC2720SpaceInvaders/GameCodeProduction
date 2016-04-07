#include "actorEnemyBasic.h"

void MoveActor(int moveRate, const int SCREEN_WIDTH){
   if (xCoord > 25 && xCoord < 775){
      if (moveRight){
	 xCoord += moveRate;
      }else {
	 xCoord -= moveRate;
      }
   }else {
      yCoord -= moveRate;
      if (moveRight){
	 moveRight = false;
      }else {
	 moveRight = true;
      }
   }
   actorHitbox.MoveHitbox();
}void InitializeBasicEnemy(ALLEGRO_BITMAP *enemySprite, float x, float y, int enemySpriteWidth, int enemySpriteHeight, int enemyHealth, int newEnemyScore){
   xCoord = x;
   yCoord = y;
   *actorSprite = *enemySprite;
   spriteWidth = enemySpriteWidth;
   spriteHeight = enemySpriteHeight;
   actorHitbox = actorHitbox(x, y, 5, 5);
   enemyScore = newEnemyScore;
   moveRight = true;
}
