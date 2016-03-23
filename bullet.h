//includes
//#include "projectile.h"
#include <allegro5/allegro.h>
//Header comments
#ifndef BULLET_H__
#define BULLET_H__

struct Bullets
{
    float bulletX, bulletY;
    float destinyX, destinyY;

};

class ProjectileBullet  //public Projectile
{
private:
    //Member variables
    int bulletDamage;

public:
    //Retrieval methods
    int getBulletDamage();
};

/** @fn createBullet
* @brief initializes the position of a bullet, without drawing it
* @param
* @param maxBullets is the constant that limits the amount of bullet at the same time
* @param BuletsArray is the array that has all the bullets in it
* @param bulletX is the horizontal position where the bullet will be initialized
* @param bulletY is the vertical position where the bullet will be initialized
* @param destinyY is the vertical direction of the bullet
* @param CanPlayerShoot is a boolean used to control the time between bullets
*/

bool createBullet(struct ACTOR player2, const int maxBullets, struct Bullets BulletsArray[])
{

    if(player2.currBullets < maxBullets-1)  //initializes bullet
    {
        player2.currBullets++;
        BulletsArray[player2.currBullets].bulletX = player2.playerX+30;
        BulletsArray[player2.currBullets].bulletY = player2.playerY;
        BulletsArray[player2.currBullets].destinyX = 0.0; /** because the bullet will go straight*/
        BulletsArray[player2.currBullets].destinyY = -3.0;
        //al_draw_line(BulletsArray[player2.currBullets].bulletX, BulletsArray[player2.currBullets].bulletY, BulletsArray[player2.currBullets].bulletX, BulletsArray[player2.currBullets].bulletY+10, al_map_rgb(255,255,255), 5.0); /**< Draws the bullets*/
        return true;
    }
    return false;
}

/** @fn drawBullet
* @brief draws the bullets on the position where they were intialized
* @param
* @param maxBullets is the constant that limits the amount of bullet at the same time
* @param BuletsArray is the array that has all the bullets in it
* @param bulletX is the horizontal position where the bullet will be initialized
* @param bulletY is the vertical position where the bullet will be initialized
* @param destinyX is the horizontal direction of the bullet, by default we use 0 because the bullet goes straight up
* @param destinyY is the vertical direction of the bullet
*/

void drawBullet(struct ACTOR player2, const int maxBullets, struct Bullets BulletsArray[])
{
    if(player2.currBullets > 0)  //draws bullet
    {
        for (int i=1; i <= player2.currBullets; i++)  //looks for all the current bullents in the array
        {
            BulletsArray[i].bulletX += BulletsArray[i].destinyX; // in this case, it's 0=0+0 because the bullet goes straight
            BulletsArray[i].bulletY += BulletsArray[i].destinyY; //increases vertical position of the bullet

            al_draw_line(BulletsArray[i].bulletX, BulletsArray[i].bulletY, BulletsArray[i].bulletX, BulletsArray[i].bulletY+10, al_map_rgb(255,255,255), 5.0); /**< Draws the bullets*/
        }
    }
}


bool deleteBullet(struct ACTOR player2, const int maxBullets, struct Bullets BulletsArray[])
{
    if(player2.currBullets > 0)  //draws bullet
    {
        for (int i=1; i <= player2.currBullets; i++)  //looks for all the current bullents in the array
        {
            BulletsArray[i].bulletX += BulletsArray[i].destinyX; // in this case, it's 0=0+0 because the bullet goes straight
            BulletsArray[i].bulletY += BulletsArray[i].destinyY; //increases vertical position of the bullet

            if(BulletsArray[i].bulletY > ScreenHeight || BulletsArray[i].bulletY < 0 || BulletsArray[i].bulletX > ScreenWidth || BulletsArray[i].bulletX < 0 )  //is the bullet inside the screen?
            {

                BulletsArray[i] = BulletsArray[player2.currBullets]; // overwrite the values of BulletsArray[i]
                player2.currBullets--; //disappears a bullet
                return true;
            }
        }
    }
    return false;
}


#endif //Bullet.h
