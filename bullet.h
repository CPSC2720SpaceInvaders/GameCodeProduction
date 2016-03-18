//Header comments

#ifndef BULLET_H__
#define BULLET_H__

//includes
#include <allegro5/allegro.h>
#include "projectile.h"

class Bullet public Projectile {
  Private:
   //Member variables
   int bulletDamage;

  Public:
   //Retrieval methods
   int getBulletDamage();
   
   //Animation Methods
   void animateBullet(/*relevant inputs*/);
};

#endif //Bullet.h
