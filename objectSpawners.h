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

void SpawnBullet(vector<ProjectileBullet>& targetIndex, float startingXPosi, float startingYPosi, int damage, int direction, const char *spriteLoc);

void SpawnBasicRow(vector<ActorEnemyBasic>& enemyIndex, float startingXPosi, float startingYPosi, int newEnemyHealth, int newEnemyScore, const char *spriteLoc, bool right, int hitboxSize, int enemiesToSpawn);

//void SpawnSprinterColumn(vector<ActorEnemySprinter> enemyIndex, float startingXPosi, float startingYPosi, int enemiesToSpawn);

//void SpawnBoss(vector<ActorEnemyBoss> enemyIndex, float StartingXPosi, float startingYPosi);


