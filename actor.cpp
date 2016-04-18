//Header comments

//includes
#include <allegro5/allegro.h>
#include "actor.h"

//Constructors and Destructors
Actor::Actor(float xPosi, float yPosi, int hp, int _hitboxSize, int spriteLoc) : xCoord(xPosi), yCoord(yPosi), health(hp), hitboxSize(_hitboxSize), actorHitbox(xPosi, yPosi, hitboxSize, hitboxSize), spriteKey(spriteLoc) {}
Actor::Actor() {};
/*Actor::Actor(const Actor& copyTarget) {
	xCoord = copyTarget.xCoord;
	yCoord = copyTarget.yCoord;
	health = copyTarget.health;
	hitboxSize = copyTarget.hitboxSize;
	actorHitbox = copyTarget.actorHitbox;
	spritePath = copyTarget.spritePath;

	actorSprite = al_load_bitmap(spritePath);
}
Actor& Actor::operator=(const Actor& copyTarget) {
	xCoord = copyTarget.xCoord;
	yCoord = copyTarget.yCoord;
	health = copyTarget.health;
	hitboxSize = copyTarget.hitboxSize;
	actorHitbox = copyTarget.actorHitbox;
	spritePath = copyTarget.spritePath;

	al_destroy_bitmap(actorSprite);
	actorSprite = al_load_bitmap(spritePath);

	return *this;
}
Actor::~Actor() {
	al_destroy_bitmap(actorSprite);
}*/

//Retrieval methods
/** @fn GetXCoord
* @brief returns the horizontal Actor's position
*/
float Actor::GetXCoord (){
   return xCoord;
}
/** @fn GetYCoord
* @brief returns the vertical Actor's position
*/
float Actor::GetYCoord(){
   return yCoord;
}
/** @fn GetHealth
* @brief returns the Actor's health
*/
int Actor::GetHealth(){
   return health;
}
int Actor::GetSpriteKey() {
	return spriteKey;
}

//Manipulation methods
/** @fn ModifyHealth
* @brief after taking damage, the actor needs to lose health
* @param integer with the damage that the bullet caused
*/
void Actor::ModifyHealth(int damageTaken){
   health -= damageTaken;
}
/** @fn ChangeActorSprite
* @brief updates the sprite of the actor
* @param newSprite is the new bitmap file that will be drawn
* @param newSpriteWidth is the width of the new bitmap to be drawn
* @param newSpriteHeight is the height of the new bitmap to be drawn
*/
/*void Actor::ChangeActorSprite(const char *newSpriteLoc) {
	spritePath = newSpriteLoc;
	actorSprite = al_load_bitmap(spritePath);
}*/
void Actor::ChangeActorSprite(int newSpriteLoc) {
	spriteKey = newSpriteLoc;
}
/** @fn DrawActor
* @brief draws the actor on its given positions
*/
/*void Actor::DrawActor(){
   al_draw_bitmap(actorSprite, xCoord, yCoord, NULL);
}*/
/** @fn CheckDead
* @brief checks actor's health, if it is lower than 0, it wil active its dead
*/
bool Actor::CheckDead() {
	if (health <= 0) {
		return true;
	}return false;
}
