/**
*   @file		objectSpawners.h
*   @brief		Functions to create enemy and bullet objects for use in the game stages.
*
*				Each function defined below creates a certain number
*				(either one or more) of a specific type of object
*				which will activate and act as specified in the
*				game space. 
*
*   @author		Tyler Bertram
*   @bug		No known bugs.
*/

#include <vector>
#include <string>
#include "actor.h"
#include "actorEnemyBasic.h"
//#include "actorEnemySprinter.h"
//#include "actorEnemyBoss.h"
#include "projectile.h"
#include "bullet.h"
#include "Hitbox.h"

using namespace std;

/** Implemented Functions */

/**
*   @fn			SpawnBullet(vector<ProjectileBullet>& targetIndex, float startingXPosi, float startingYPosi, int damage, int direction)
*   @brief		Constructor function.
*
*	@param		targetIndex			Vector index to load the new bullet into.
*	@param		startingXPosi		Initial x-axis position of the new bullet.
*	@param		startingYPosi		Initial y-axis position of the new bullet.
*	@param		damage				Damage the new bullet should deal.
*	@param		direction			Direction the new bullet should travel (0 = UP, 1 = DOWN, see directions_c enum in projectile.h)
*
*				Loads a newly-constructed Bullet object into the specified vector index, where it can be acted upon
*				as desired.
*/
void SpawnBullet( vector<ProjectileBullet>& targetIndex, float startingXPosi, float startingYPosi, int damage, int direction );

/**
*   @fn			SpawnBullet(vector<ProjectileBullet>& targetIndex, float startingXPosi, float startingYPosi, int damage, int direction)
*   @brief		Constructor function.
*
*	@param		enemyIndex			Vector index to load the basic enemies into.
*	@param		startingXPosi		Initial x-axis position of the first enemy spawned.
*	@param		startingYPosi		Initial y-axis position of the row of enemies to be created.
*	@param		newEnemyHealth		Amount of health the new enemies should begin with.
*	@param		newEnemyScore		Value of the new enemies when killed (not currently utilized).
*	@param		spriteLoc			spriteIndex key to draw the new enemies.
*	@param		right				If true, the enemies will begin moving right. If false, they will begin moving left instead.
*	@param		hitboxSize			Size of the hitbox of the spawned enemies.
*	@param		enemiesToSpawn		Number of enemies to spawn in the row. Each enemy will be spawned with a 10 pixel space between its sprite and the sprite of the previously spawned enemy, if any.
*
*				Creates a row of one or more enemies of ActorEnemyBasic type and inserts them into a target vector index.
*				The row exists on only one y-axis location, but enemies are spawned rightwards of a defined starting location.
*/
void SpawnBasicRow(vector<ActorEnemyBasic>& enemyIndex, float startingXPosi, float startingYPosi, int newEnemyHealth, int newEnemyScore, int spriteLoc, bool right, int hitboxSize, int enemiesToSpawn);

/** Unimplemented Functions (Missing Corresponding Classes) */

//void SpawnSprinterColumn(vector<ActorEnemySprinter> enemyIndex, float startingXPosi, float startingYPosi, int enemiesToSpawn);

//void SpawnBoss(vector<ActorEnemyBoss> enemyIndex, float StartingXPosi, float startingYPosi);


