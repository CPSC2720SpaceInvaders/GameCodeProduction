//includes
#include "projectile.h"
#include <allegro5/allegro.h>
#define SCREENWIDTH 1200
#define SCREENHEIGHT 800
//Header comments
#ifndef BULLET_H__
#define BULLET_H__

class ProjectileBullet  //public Projectile
{
private:
    //Member variables
    int bulletDamage;

public:
    //Retrieval methods
    int getBulletDamage();
};

//############# NEW CODE, VICTOR ############

struct BULLETS
{
    float bulletX, bulletY;
    float destinyX, destinyY;
    int bulletDamage = 1;

    int getBulletDamage();
    bool collision(float xCoord, float yCoord, float playerWidth, float playerHeight);
    bool enemyBulletCollision(struct ACTOR enemyIndex[], struct ACTOR spaceShip);
};

/** @fn createBullet
* @brief initializes the position of a bullet, without drawing it
* @param player2 is the ACTOR structure that is shooting
* @param BuletsArray is the array that has all the bullets in it
* @param UpOrDown is an int: if positive, the bullet goes down, if negative, it goes up
*/

bool createBullet(struct ACTOR player, struct BULLETS BulletsArray[], const int MOVERATE_PROJECTILES, ALLEGRO_KEYBOARD_STATE keyboardState1, ALLEGRO_SAMPLE *sfxShoot, bool canPlayerShoot)
{
    if (al_key_down(&keyboardState1, ALLEGRO_KEY_SPACE) && canPlayerShoot==true)
    { //shoots
        if((player.currBullets < player.maxBullets-1))  //initializes bullet
        {
            al_play_sample(sfxShoot, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); /**< plays sound */
            player.currBullets++;
            BulletsArray[player.currBullets].bulletX = player.xCoord+30;
            BulletsArray[player.currBullets].bulletY = player.yCoord;
            BulletsArray[player.currBullets].destinyX = 0.0; /**< because the bullet will go straight*/
            BulletsArray[player.currBullets].destinyY = MOVERATE_PROJECTILES; /**< the number is negative, so the bullet will go up */
            return true;
        }
        return false;
    }
    return false;
}

bool createEnemyBullet(struct ACTOR player2, struct BULLETS BulletsArray[], const int MOVERATE_PROJECTILES, ALLEGRO_SAMPLE *sfxShoot)
{
    if(player2.currBullets < player2.maxBullets-1)  //initializes bullet
    {
        al_play_sample(sfxShoot, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); /**< plays sound */
        player2.currBullets++;
        BulletsArray[player2.currBullets].bulletX = player2.xCoord+30;
        BulletsArray[player2.currBullets].bulletY = player2.yCoord;
        BulletsArray[player2.currBullets].destinyX = 0.0; /**< because the bullet will go straight*/
        BulletsArray[player2.currBullets].destinyY = MOVERATE_PROJECTILES; /**< the number is positive, so the bullet will go down */
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
bool drawBullet(struct ACTOR player2, struct BULLETS BulletsArray[]) //it also deletes
{
    if(player2.currBullets > 0)  //draws bullet
    {
        for (int i=1; i <= player2.currBullets; i++)  //looks for all the current bullents in the array
        {
            BulletsArray[i].bulletX += BulletsArray[i].destinyX; // in this case, it's 0=0+0 because the bullet goes straight
            BulletsArray[i].bulletY += BulletsArray[i].destinyY; //increases vertical position of the bullet

            al_draw_line(BulletsArray[i].bulletX, BulletsArray[i].bulletY, BulletsArray[i].bulletX, BulletsArray[i].bulletY+10, al_map_rgb(255,255,255), 5.0); /**< Draws the bullets*/

            if(BulletsArray[i].bulletY > SCREENHEIGHT || BulletsArray[i].bulletY < 0 || BulletsArray[i].bulletX > SCREENWIDTH || BulletsArray[i].bulletX < 0 )  //is the bullet inside the screen?
            { //TODO: Change values of screenWidth to 1200 and find where is screenHeight initialized

                BulletsArray[i] = BulletsArray[player2.currBullets]; // overwrite the values of BulletsArray[i]
                player2.currBullets--; //disappears a bullet
                return true;
            }
        }
    }
    return false;
}

bool BULLETS::collision(float xCoord, float yCoord, float playerWidth, float playerHeight){

    if( (xCoord < bulletX) && (bulletX < xCoord+playerWidth) &&
        (yCoord < bulletY) && (bulletY < yCoord+playerHeight)){ //bullet inside the sprite

            return true;

        } else {

            return false;
        }

}

bool BULLETS::enemyBulletCollision(struct ACTOR enemyIndex[], struct ACTOR playerShip){

    if(playerShip.currBullets > 0 && playerShip.currBullets < playerShip.maxBullets)  //draws bullet
    {
        int enemyNumber = -1;
        for(int row=0; row<5; row++){
            for (int column=0; column<11; column++){
                enemyNumber++;
                if(collision(enemyIndex[enemyNumber].xCoord,
                            enemyIndex[enemyNumber].yCoord,
                            enemyIndex[enemyNumber].playerWidth,
                            enemyIndex[enemyNumber].playerHeight) &&
                            enemyIndex[enemyNumber].maxHealth > 0){

                            playerShip.currBullets--;
                            enemyIndex[enemyNumber].maxHealth -= 1; /**< delete the enemy */
                            if (enemyIndex[enemyNumber].maxHealth == 0){
                                enemyIndex[enemyNumber].enemyExplotes();
                            }
                            return true;
                }
            }
        }
    }
    return false; //this function is bool because if it's true, then spaceShip.currBullets--
}

    void gameOverScreen(bool& draw, bool& done, ALLEGRO_FONT *font){
    al_rest(0.5);
    al_draw_text(font, al_map_rgb(254,117,200), SCREENWIDTH/2, SCREENHEIGHT/3, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
    al_flip_display();
    //al_clear_to_color(backgroundColor); /**< cleans screen and only shows GAME OVER */
    al_rest(1.0);
    draw = false;
    done = true; /**< ends the game */
}

#endif //Bullet.h
