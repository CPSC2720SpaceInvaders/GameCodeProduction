#include 
#include "actor.h"
#include "actorEnemyBasic.h"
//#include "actorEnemySprinter.h"
//#include "actorEnemyBoss.h"

void SpawnBasicRow(vector<Actor> *enemyIndex, float startingXPosi, float startingYPosi, int enemiesToSpawn);

void SpawnSprinterColumn(vector<Actor> *enemyIndex, float startingXPosi, float startingYPosi, int enemiesToSpawn);

void SpawnBoss(vector<Actor> *enemyIndex, float StartingXPosi, float startingYPosi);
