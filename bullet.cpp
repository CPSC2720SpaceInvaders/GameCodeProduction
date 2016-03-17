/**
*		@file	bullet.cpp
*		@brief	Implementation of bullet class.
*
*				This contains the implementation for the methods
*				of the Bullet class, the primary gameplay mechanic,
*				which allows actors to damage or destroy each other.
*
*		@author	Tyler Bertram
*		@bug	No known bugs (uncompiled, untested).
*/

#include <allegro5/allegro.h>
#include "bullet.h"

//Private methods

//Public methods
/**
*	Additional comments about GetBulletDamage method.
*/
int GetBulletDamage(){
   return bulletDamage;
}

/**
*	Additional comments about AnimateBullet method.
*/
void AnimateBullet( ALLEGRO_BITMAP *bulletSprite ){
	al_draw_bitmap(*bulletSprite, xCoordinate, yCoordinate, NULL);
}

/**
*	Additional comments about DestroyBullet method.
*/
void DestroyBullet( ALLEGRO_COLOR backgrColor ) {
	al_clear_to_color( backgrColor );
}
