#include "objectSpawners.h"

void SpawnBullet(vector<ProjectileBullet>& targetIndex, float startingXPosi, float startingYPosi, int damage, int direction, const char *spriteLoc) {
	//ProjectileBullet tempBullet(startingXPosi, startingYPosi, direction, spriteLoc, damage);
	ProjectileBullet tempBullet(startingXPosi, startingYPosi, direction, spriteLoc, damage);
	targetIndex.push_back(tempBullet);
}void SpawnBasicRow(vector<ActorEnemyBasic>& enemyIndex, float startingXPosi, float startingYPosi, int newEnemyHealth, int newEnemyScore, int spriteLoc, bool right, int hitboxSize, int enemiesToSpawn) {
	for (int i = 0; i < enemiesToSpawn; i++) {
		enemyIndex.push_back(ActorEnemyBasic(startingXPosi, startingYPosi, newEnemyHealth, hitboxSize, spriteLoc, newEnemyScore, right));
		startingXPosi += 60;
	}
}//void SpawnSprinterColumn(vector<ActorEnemySprinter> enemyIndex, float startingXPosi, float startingYPosi, int enemiesToSpawn, ALLEGRO_BITMAP *enemySprite){

//}void SpawnBoss(vector<ActorEnemyBoss> enemyIndex, float StartingXPosi, float startingYPosi, ALLEGRO_BITMAP *enemySprite){

//}
