//Header comments

#ifndef BULLET_H__
#define BULLET_H__

//includes
#include <allegro5/allegro.h>
#include "projectile.h"

class ProjectileBullet public Projectile {
  Private:
   //Member variables
   int bulletDamage;

  Public:
   //Retrieval methods
   int getBulletDamage();
};

#endif //Bullet.h
