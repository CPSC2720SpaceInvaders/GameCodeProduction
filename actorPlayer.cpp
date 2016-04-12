#include "actorPlayer.h"

void MoveActor(bool moveUp, bool moveDown, bool moveLeft, bool moveRight, const int MOVERATE_ACTORS) {
	if (moveUp) {
		yCoord += MOVERATE_ACTORS;
	}
	else if (moveDown) {
		yCoord -= MOVERATE_ACTORS;
	}
	if (moveRight) {
		xCoord += MOVERATE_ACTORS;
	}
	else if (moveLeft) {
		xCoord -= MOVERATE_ACTORS;
	}
	actorHitbox.MoveHitbox(xCoord, yCoord);
}int GetScore(){
   return playerScore;
}int GetLives(){
	return lives;
}int GetMaxBullets(){
    return maxBullets;
}void UpdateScore(int scoreGained){
   playerScore += scoreGained;
}void KillPlayer(ALLEGRO_BITMAP *oldSprite, float oldSpriteWidth, float oldSpriteHeight, float defaultXPosi, float defaultYPosi) {
      lives--;
	  health = 1;
	  actorSprite = oldSprite;
      xCoord = defaultXPosi;
      yCoord = defaultYPosi;
}
