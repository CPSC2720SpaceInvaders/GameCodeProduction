#include "actorPlayer.h"

ActorPlayer::ActorPlayer(float xPosi, float yPosi, int hp, int _hitboxSize, int spriteLoc) : Actor(xPosi, yPosi, hp, _hitboxSize, spriteLoc), playerScore(0), lives(3), maxBullets(5), bulletControlCounter(5) {}

void ActorPlayer::MoveActor(bool moveUp, bool moveDown, bool moveLeft, bool moveRight, const int MOVERATE_ACTORS) {
	if (moveUp) {
		if (yCoord <= 10) {}
		else {
			yCoord -= MOVERATE_ACTORS;
		}
	}
	else if (moveDown) {
		if (yCoord >= 750) {}
		else {
			yCoord += MOVERATE_ACTORS;
		}
	}
	if (moveRight) {
		if (xCoord <= 10) {}
		else {
			xCoord -= MOVERATE_ACTORS;
		}
	}
	else if (moveLeft) {
		if (xCoord >= 1140) {}
		else {
			xCoord += MOVERATE_ACTORS;
		}
	}
	actorHitbox.MoveHitbox(xCoord, yCoord);
}int ActorPlayer::GetScore(){
   return playerScore;
}int ActorPlayer::GetLives(){
	return lives;
}int ActorPlayer::GetMaxBullets(){
    return maxBullets;
}void ActorPlayer::UpdateScore(int scoreGained){
   playerScore += scoreGained;
}void ActorPlayer::KillPlayer(int newSpriteLoc, float oldSpriteWidth, float oldSpriteHeight, float defaultXPosi, float defaultYPosi) {
      lives--;
	  health = 1;
	  ChangeActorSprite(newSpriteLoc);
      xCoord = defaultXPosi;
      yCoord = defaultYPosi;
}
