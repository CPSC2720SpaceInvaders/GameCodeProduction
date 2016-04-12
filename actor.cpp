//Header comments

//includes
#include <allegro5/allegro.h>
#include "actor.h"

//Constructors
Actor (int xC, int yC, int curH, int maxH) : xCoord(xC), yCoord(yC), curHealth(curH), maxHealth(maxH) { };
Actor (int xC, int yC, int curH) : xCoord(xC), yCoord(yC), curHealth(curH), maxHealth(1) { };
Actor (int xC, int yC) : xCoord(xC), yCoord(yC), curHealth(1), maxHealth(1);

//Retrieval methods
float GetXCoord (){
   return xCoord;
}float GetYCoord(){
   return YCoord;
}int GetHealth(){
   return health;
}

//Manipulation methods
void ModifyCurrentHealth(int damageTaken){
   health -= damageTaken;
}void ChangeActorSprite(ALLEGRO_BITMAP *newSprite, float newSpriteWidth, float newSpriteHeight) {
	*actorSprite = *newSprite; 
	spriteWidth = newSpriteWidth;
	spriteHeight = newSpriteHeight;
}void DrawActor(){
   al_draw_bitmap_region(actorSprite, 0, 0, spriteWidth, spriteHeight, xCoord, yCoord, NULL);
}bool CheckDead() {
	if (curHealth <= 0) {
		return true;
	}return false;
}
