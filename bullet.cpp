/**
*   @file		bullet.h
*   @brief		Implementation of ProjectileBullet class.
*
*				This contains the implementation of all methods
*				for the ProjectileBullet class, which is the
*				primary vector of (violent) interaction between
*				actors in the game space.
*
*   @author		Tyler Bertram
*   @bug		No known bugs.
*/

#include <allegro5/allegro.h>
#include "bullet.h"

/** Retrieval Methods */

/** 
* Once again, to improve code reusability, an argument to specify the Projectile hitbox size could and probably should be added, rather than
* using the magic number 5.
*/
ProjectileBullet::ProjectileBullet(float xPosi, float yPosi, int dir, int dam) : Projectile(xPosi, yPosi, dir, 5), bulletDamage(dam) {}

/** 
* Additional comments about GetBulletDamage() method (if any).
*/
int ProjectileBullet::GetBulletDamage(){
   return bulletDamage;
}

/** Deprecated Functions (no commentary) */

//void createBullet(int& currBullets, const int maxBullets, struct Bullets BulletsArray[], const float bulletX, const float bulletY, const float destinyY);

//void drawBullet(int& currBullets, const int maxBullets, struct Bullets BulletsArray[]);

//void deleteBullet(int& currBullets, const int maxBullets, struct Bullets BulletsArray[], const int ScreenHeight, const int ScreenWidth);

