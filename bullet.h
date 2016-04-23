/**
*   @file		bullet.h
*   @brief		Definition of ProjectileBullet class.
*
*				This contains the definitions of the public and
*				private member variables, as well as all methods,
*				for the ProjectileBullet class, which is the
*				primary vector of (violent) interaction between
*				actors in the game space.
*
*   @author		Tyler Bertram
*   @bug		No known bugs.
*/

#ifndef BULLET_H
#define BULLET_H

#include "projectile.h"
#include <allegro5/allegro.h>

class ProjectileBullet : public Projectile
{
private:
    /** Private Member Variables */
    int		bulletDamage;		/**< Damage dealt to an actor when struck by the bullet. */

public:
	/** Constructors and Destructors */

	/**
	*   @fn			ProjectileBullet( float xPosi, float yPosi, int dir, int dam )
	*   @brief		Constructor function.
	*
	*	@param		xPosi			Position on x axis to place new ProjectileBullet at.
	*	@param		yPosi			Position on y axis to place new ProjectileBullet at.
	*	@param		dir				Direction new projectile should travel, up or down.
	*	@param		dam				Damage the bullet should deal.
	*
	*				All ProjectileBullets have a hitbox size of 5, this is not specified
	*				in the constructor.
	*
	*   @return		Initialized ProjectileBullet object.
	*/
	ProjectileBullet( float xPosi, float yPosi, int dir, int dam );

    /** Retrieval Methods */
    
	/**
	*   @fn			GetBulletDamage()
	*   @brief		Getter function for bulletDamage variable.
	*
	*   @return		Integer value.
	*/
	int GetBulletDamage();
};

#endif //Bullet.h
