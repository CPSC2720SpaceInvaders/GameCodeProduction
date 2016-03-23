//Header comments
#ifndef ACTOR_H__
#define ACTOR_H__
//includes
#include <allegro5/allegro.h>

class Actor {
private:
   int xCoord, yCoord, curHealth, maxHealth;

public:
   //Retrieval methods
   int getXCoord();
   int getYCoord();
   int getCurrentHealth();
   int getMaxHealth();

   //Manipulation methods
   void moveActor(int moveRate);
   void modifyCurrentHealth(int damageTaken);
   bool checkDead();
};

//##### NEW CODE ###########

struct ACTOR
{
    float playerX=ScreenWidth/2, playerY=ScreenHeight-100.0; /**< represent the original position of the spaceship */
    float playerWidth=60.0, playerHeight=40.0;
    int currBullets = 0;

} playerShip;

/**
* @class classEnemy
* @brief All stuff related to the alien
* @author Victor Adad.
*/
//class classEnemy
//{
//public:
//    int enemyX = 10;
//    int enemyY = 100;
//    int enemyMaxHealth = 1;
//    ALLEGRO_BITMAP *enemy;
//    int enemieWidth, enemieHeight;    //width and height of character
//    int animation;
//    void initialize_enemy(int _ememyX, int _enemyY, int _life);
//
//    int moveEnemy(int enemyX, int enemyY);
//};



void drawSpaceship(ALLEGRO_BITMAP *player, struct ACTOR playerShip)
{
    al_draw_bitmap_region(player, 0, 0, playerShip.playerWidth, playerShip.playerHeight, playerShip.playerX, playerShip.playerY, NULL);
}



#endif //actor.h
