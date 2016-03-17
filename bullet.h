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

class Projectile_Bullet public Projectile {
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

	//Animation Methods
	/**
	*		@fn			AnimateBullet( ALLEGRO_BITMAP *bulletSprite )
	*		@brief		Animates the bullet image whenever called at the current coordinates of the bullet.
	*					
	*					Assumes the existence of an initialized Allegro display, and should be called
	*					whenever MoveProjectile is.
	*
	*		@param		*bulletSprite	Bitmap pointer which should be pre-loaded with the bullet sprite.
	*									This will be drawn by the method whenever called.
	*/
	void AnimateBullet( ALLEGRO_BITMAP *bulletSprite );

	//Animation Methods
	/**
	*		@fn			DestroyBullet()
	*		@brief		Clears the bullet bitmap at the current location.
	*
	*					Should be called prior to moving the bitmap while drawing, as well as whenever
	*					the bullet is destroyed (collides with an actor, escapes window bounds).
	*					
	*		@param		backgrColor		ALLEGRO_COLOR color which matches the background of the game
	*									display so that DestroyBullet "erases" the bullet.
	*/
	
	void DestroyBullet(ALLEGRO_COLOR backgrColor);
};

#endif //Bullet.h
