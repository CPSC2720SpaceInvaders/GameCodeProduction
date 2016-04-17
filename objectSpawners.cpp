#include "objectSpawners.h"

void SpawnBullet(vector<ProjectileBullet>& targetIndex, float startingXPosi, float startingYPosi, int damage, int direction, const char *spriteLoc) {
	//ProjectileBullet tempBullet(startingXPosi, startingYPosi, direction, spriteLoc, damage);
	ProjectileBullet *tempBullet = new ProjectileBullet(startingXPosi, startingYPosi, direction, spriteLoc, damage);
	targetIndex.push_back(*tempBullet);
	delete tempBullet;
}void SpawnBasicRow(vector<ActorEnemyBasic>& enemyIndex, float startingXPosi, float startingYPosi, int newEnemyHealth, int newEnemyScore, const char *spriteLoc, bool right, int hitboxSize, int enemiesToSpawn){
	for (int i = 0; i < enemiesToSpawn; i++) {
		ActorEnemyBasic tempEnemy(startingXPosi, startingYPosi, newEnemyHealth, hitboxSize, spriteLoc, newEnemyScore, right);
		enemyIndex.push_back(tempEnemy);
		startingXPosi += 60;
	}
}//void SpawnSprinterColumn(vector<ActorEnemySprinter> enemyIndex, float startingXPosi, float startingYPosi, int enemiesToSpawn, ALLEGRO_BITMAP *enemySprite){

//}void SpawnBoss(vector<ActorEnemyBoss> enemyIndex, float StartingXPosi, float startingYPosi, ALLEGRO_BITMAP *enemySprite){

//}
