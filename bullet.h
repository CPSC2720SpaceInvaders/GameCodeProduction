/**
*		@file	bullet.h
*		@brief	Definition of bullet class.
*
*				This contains the definitions of the public and
*				private member variables, as well as all methods,
*				for the Bullet class, the primary gameplay 
*				mechanic which allows actors to damage and
*				destroy each other.
*
*		@author	Tyler Bertram
*		@bug	No known bugs (uncompiled, untested).
*/

#ifndef BULLET_H__
#define BULLET_H__

#include <allegro5/allegro.h>
#include "projectile.h"

class ProjectileBullet Public Projectile {
Private:
	//Member variables
	int bulletDamage; /**< The damage a given bullet object deals on a collision. Usually 1, to match standard HP. */

Public:
	//Retrieval methods
	/**
	*		@fn			GetBulletDamage()
	*		@brief		Exposes and returns bulletDamage.
	*		@return		Integer value.
	*/
	int GetBulletDamage();
};

#endif //Bullet.h