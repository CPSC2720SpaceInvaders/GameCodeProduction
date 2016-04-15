//Header comments
//includes
#include <allegro5/allegro.h>
#include "bullet.h"

//Private methods

//Public methods
ProjectileBullet::ProjectileBullet(float xPosi, float yPosi, int dir, const char *spritePath, int dam) : Projectile(xPosi, yPosi, dir, spritePath, 5), bulletDamage(dam) {}

int ProjectileBullet::GetBulletDamage(){
   return bulletDamage;
}

//void createBullet(int& currBullets, const int maxBullets, struct Bullets BulletsArray[], const float bulletX, const float bulletY, const float destinyY);

//void drawBullet(int& currBullets, const int maxBullets, struct Bullets BulletsArray[]);

//void deleteBullet(int& currBullets, const int maxBullets, struct Bullets BulletsArray[], const int ScreenHeight, const int ScreenWidth);
