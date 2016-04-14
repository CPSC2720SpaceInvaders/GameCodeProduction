//Header comments

//includes
#include <allegro5/allegro.h>
#include "actor.h"

//Constructors
Actor (int xC, int yC, int curH, int maxH) : xCoord(xC), yCoord(yC), curHealth(curH), maxHealth(maxH) { };
Actor (int xC, int yC, int curH) : xCoord(xC), yCoord(yC), curHealth(curH), maxHealth(1) { };
Actor (int xC, int yC) : xCoord(xC), yCoord(yC), curHealth(1), maxHealth(1);

//Retrieval methods
/** @fn GetXCoord
* @brief returns the horizontal Actor's position
*/
float GetXCoord (){
   return xCoord;
}
/** @fn GetYCoord
* @brief returns the vertical Actor's position
*/
float GetYCoord(){
   return YCoord;
}
/** @fn GetHealth
* @brief returns the Actor's health
*/
int GetHealth(){
   return health;
}

//Manipulation methods
/** @fn ModifyHealth
* @brief after taking damage, the actor needs to lose health
* @param integer with the damage that the bullet caused
*/
void ModifyHealth(int damageTaken){
   health -= damageTaken;
}
/** @fn ChangeActorSprite
* @brief updates the sprite of the actor
* @param newSprite is the new bitmap file that will be drawn
* @param newSpriteWidth is the width of the new bitmap to be drawn
* @param newSpriteHeight is the height of the new bitmap to be drawn
*/
void ChangeActorSprite(ALLEGRO_BITMAP *newSprite, float newSpriteWidth, float newSpriteHeight) {
	*actorSprite = *newSprite;
	spriteWidth = newSpriteWidth;
	spriteHeight = newSpriteHeight;
}
/** @fn DrawActor
* @brief draws the actor on its given positions
*/
void DrawActor(){
   al_draw_bitmap_region(actorSprite, 0, 0, spriteWidth, spriteHeight, xCoord, yCoord, NULL);
}
/** @fn CheckDead
* @brief checks actor's health, if it is lower than 0, it wil active its dead
*/
bool CheckDead() {
	if (curHealth <= 0) {
		return true;
	}return false;
}
