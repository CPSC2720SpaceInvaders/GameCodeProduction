//includes
#include "projectile.h"
#include <allegro5/allegro.h>
//Header comments
#ifndef BULLET_H
#define BULLET_H

class ProjectileBullet : public Projectile
{
private:
    //Member variables
    int bulletDamage;

public:
    //Retrieval methods
    int GetBulletDamage();
};

#endif //Bullet.h
