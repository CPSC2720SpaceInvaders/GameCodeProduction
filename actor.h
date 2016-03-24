//Header comments
#ifndef ACTOR_H__
#define ACTOR_H__
//includes
#include <allegro5/allegro.h>
const int ScreenWidth = 800;
const int ScreenHeight = 800;

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

//######## NEW CODE, MARCH 22, VICTOR ###########

struct ACTOR
{
    float xCoord;
    float yCoord; /**< represent the original position of the spaceship */
    float playerWidth;
    float playerHeight; /**< represent the width and height of the spaceship inside the PNG file */
    int currBullets;
    int maxBullets;
    int BulletControlCounter; /** controls the time between shoots */
    int kindOfActor; /** 0=Player, 1=Enemy */
    int enemyMaxHealth = 1;

    ALLEGRO_BITMAP *spritePlayer;

    void initializeActor(char* sprite_source, int x, int y, int _playerWidth, int _playerHeight, int _kindOfActor);
    void drawActor(ALLEGRO_BITMAP *spritePlayer);
    void moveSpaceship(ALLEGRO_KEYBOARD_STATE keyboardState1, const int MOVERATE_ACTORS);
    bool canPlayerShoot();
    bool moveEnemy(bool leftright);
    void drawOneEnemy(ALLEGRO_BITMAP *spriteSheet, int kindOfEnemy);

};

void ACTOR::moveSpaceship(ALLEGRO_KEYBOARD_STATE keyboardState1, const int MOVERATE_ACTORS){
    if(al_key_down(&keyboardState1, ALLEGRO_KEY_DOWN))
        yCoord += MOVERATE_ACTORS;
    else if (al_key_down(&keyboardState1, ALLEGRO_KEY_UP))
        yCoord -= MOVERATE_ACTORS;
    else if (al_key_down(&keyboardState1, ALLEGRO_KEY_RIGHT))
        xCoord += MOVERATE_ACTORS;
    else if (al_key_down(&keyboardState1, ALLEGRO_KEY_LEFT))
        xCoord -= MOVERATE_ACTORS;
}

/** @fn initializeSpaceship
* @brief Gives the requiered values to a new ACTOR
* @param sprite_source is the location of the png file that will represent the actor
* @param x is the position where the ACTOR will appear for the first time
* @param y is the vertical position where the ACTOR will appear for the first time
* @param _playerWidth is a float that represents the width of the individual sprite inside the png file
* @param _playerHeight is a float that represents the height of the individual sprite inside the png file
*/
void ACTOR::initializeActor(char* sprite_source, int x, int y, int _playerWidth, int _playerHeight, int _kindOfActor)
{
    xCoord = x;
    yCoord = y; /**< represent the original position of the spaceship */
    playerWidth =_playerWidth;
    playerHeight = _playerHeight; /**< size in pixels of the individual sprite on the bitmap */
    currBullets = 0;
    maxBullets = 5;
    BulletControlCounter = 0; // tic, tac, tic, tac
    kindOfActor = _kindOfActor;

    spritePlayer = al_load_bitmap(sprite_source); /**< loads sprite */
    if(!spritePlayer){ /**< Display an alert message box in case the sprite couldn't be found */
     al_show_native_message_box(NULL, "Message Title", "Bitmap Settings", "Could not load Player image.", NULL, NULL);
  }
}

void ACTOR::drawActor(ALLEGRO_BITMAP *spritePlayer)
{
    /** @fn al_draw_bitmap_region();
    * @brief Draws the player on the display from a PNG file.
    * @param player is and ALLEGRO_BITMAP variable that contains a PNG reference.
    * @param sx is a float that indiques where the sprite starts in the PNG file (usually x=0)
    * @param sy is a float that indiques where the sprite starts in the PNG file (usually y=0) so (X,Y) = (0,0)
    * @param sw is a float that indiques the actual width of the sprite
    * @param sh is a float that indiques the actual height of the sprite
    * @param x is the position on display where the sprite will be drawed
    * @param y is the position on display where the sprite will be drawed
    * @param the last parameter is a flag of the bitmap
    */
    al_draw_bitmap_region(spritePlayer, 0, 0, playerWidth, playerHeight, xCoord, yCoord, NULL);
}

void ACTOR::drawOneEnemy(ALLEGRO_BITMAP *spriteSheet, int kindOfEnemy)
{
    // kindOfEnemy goes from 1 to 3 so tehre will be 3 different sprites
    // the enemies in the spriteSheet are 50 * 40
    al_draw_bitmap_region(spriteSheet, 0, (kindOfEnemy*playerHeight), playerWidth, playerHeight, xCoord, yCoord, NULL);
}

/**
* @fn canPlayerShoot
* @brief Is kind of a timer, so the Player won't be able to shoot all the bullets at the same time.
* @brief The player will be able to shoot only whenever the function returns is true.
* @author Victor Adad.
*/
bool ACTOR::canPlayerShoot(){
    BulletControlCounter++;
    if (BulletControlCounter == 5){
        BulletControlCounter = 0;
        return true;
    }
    return false;
}

bool ACTOR::moveEnemy(bool leftright)
{
    if (xCoord < 700 && leftright==true)  /**< enemy goes right */
    {
        xCoord += 3;
        return true;
    }
    else if (xCoord > 100 && leftright==false)    /**< enemy goes left */
    {
        xCoord -= 3;
        return false;
    }
    if(xCoord >= 700 && yCoord < 700 && leftright==true)  /**< enemy goes down once, then moves right */
    {
        yCoord += 50;
        leftright = false;
        return false;
    }
    if(xCoord <= 100 && yCoord < 700 && leftright==false)  /**< enemy goes down once, then moves left */
    {
        yCoord += 50;
        leftright = true;
        return true;
    }
}

#endif //actor.h
