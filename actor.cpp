//Header comments

//includes
#include <allegro5/allegro.h>
#include "actor.h"

using namespace std;

//Constructors

//Retrieval methods
float GetXCoord (){
   return xCoord;
}float GetYCoord(){
   return YCoord;
}int GetHealth(){
   return health;
}

//Manipulation methods
void ModifyHealth(int damageTaken){
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
}void DeleteActorSprite() {
	al_destroy_bitmap(*actorSprite);
}
