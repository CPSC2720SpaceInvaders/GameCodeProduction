#include "enemySpawners.h"

void SpawnBasicRow(vector<Actor> *enemyIndex, float startingXPosi, float startingYPosi, int enemiesToSpawn, int enemyHealth, int newEnemyScore, ALLEGRO_BITMAP *enemySprite){
   ActorEnemyBasic newEnemy;
   for (i = 0; i < enemiesToSpawn; i++){
      newEnemy.InitializeBasicEnemy(*enemySprite, startingXPosi, startingYPosi, 50, 40, enemyHealth, newEnemyScore);
      enemyIndex.push_back(newEnemy);
      startingXPosi += 50;
   }  
   }void SpawnSprinterColumn(vector<Actor> *enemyIndex, float startingXPosi, float startingYPosi, int enemiesToSpawn, ALLEGRO_BITMAP *enemySprite){

   }void SpawnBoss(vector<Actor> *enemyIndex, float StartingXPosi, float startingYPosi, ALLEGRO_BITMAP *enemySprite){

}
