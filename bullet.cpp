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