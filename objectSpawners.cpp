/**
*   @file		objectSpawners.cpp
*   @brief		Functions to create enemy and bullet objects for use in the game stages.
*
*				Implements the functions defined in objectSpawners.h.
*
*   @author		Tyler Bertram
*   @bug		No known bugs.
*/

#include "objectSpawners.h"

/** Implemented Functions */

/**
* Additional comments about SpawnBullet function (if any).
*/
void SpawnBullet(vector<ProjectileBullet>& targetIndex, float startingXPosi, float startingYPosi, int damage, int direction) {
	ProjectileBullet tempBullet(startingXPosi, startingYPosi, direction, damage);
	targetIndex.push_back(tempBullet);
}

/**
* According to Dr. Memory (Windows memory leak detection tool), there may be a memory leak in this 
*/
void SpawnBasicRow(vector<ActorEnemyBasic>& enemyIndex, float startingXPosi, float startingYPosi, int newEnemyHealth, int newEnemyScore, int spriteLoc, bool right, int hitboxSize, int enemiesToSpawn) {
	for (int i = 0; i < enemiesToSpawn; i++) {
		enemyIndex.push_back(ActorEnemyBasic(startingXPosi, startingYPosi, newEnemyHealth, hitboxSize, spriteLoc, newEnemyScore, right));
		startingXPosi += 60;
	}
}

/** Unimplemented Functions (Missing Corresponding Classes) */

//void SpawnSprinterColumn(vector<ActorEnemySprinter> enemyIndex, float startingXPosi, float startingYPosi, int enemiesToSpawn, ALLEGRO_BITMAP *enemySprite){

//}void SpawnBoss(vector<ActorEnemyBoss> enemyIndex, float StartingXPosi, float startingYPosi, ALLEGRO_BITMAP *enemySprite){

//}
