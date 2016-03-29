//includes
#include <allegro5/allegro.h>
#define SCREENWIDTH 1200
#define SCREENHEIGHT 800
//Header comments
#ifndef ACTOR_H__
#define ACTOR_H__

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
    int BulletControlCounter; /**< controls the time between shoots */
    int kindOfActor; /**< 0=Player, 1=Blue Enemy, 2=Red Enemy, 3=Green Enemy */
    int maxHealth;

    ALLEGRO_BITMAP *spritePlayer;

    void initializeActor(char* sprite_source, int x, int y, int _playerWidth, int _playerHeight, int _kindOfActor);
    void drawActor(ALLEGRO_BITMAP *spritePlayer);
    void moveSpaceship(ALLEGRO_KEYBOARD_STATE keyboardState1, const int MOVERATE_ACTORS);
    bool canPlayerShoot(int timerForAnimation); /**< timerForAnimation modifies the speed of the sprite animation */
    bool moveEnemy(bool leftright);
    void drawOneEnemy(ALLEGRO_BITMAP *spriteSheet, int kindOfEnemy, int animateEnemy);
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

    if(_kindOfActor == 0){ //< 0=Player, 1=Enemy */
        maxHealth = 3; /**< the player has an amount of health = 3 */
    }else if(_kindOfActor == 1){ //blue alien
        maxHealth = 1;
    }else if(_kindOfActor == 2){ // red alien
        maxHealth = 2;
    }else if(_kindOfActor == 3){ // green alien
        maxHealth = 3;
    }

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

/** @fn drawOneEnemy
* @brief SpriteSheet is a png file with all the sprites of all the possible enemies
* @param kindOfEnemy is a int between 0 and 2, which multiplied by playerHeight, creates 3 vertical sections of the spritesheet
* @param animateEnemy is a number (0 or 1) that will create 2 horizontal sections of the spritesheep, and will look like the enemy has animation
*/
void ACTOR::drawOneEnemy(ALLEGRO_BITMAP *spriteSheet, int _kindOfActor, int animateEnemy)
{
    // kindOfEnemy goes from 1 to 3 so tehre will be 3 different sprites
    // the enemies in the spriteSheet are 50 * 40
    al_draw_bitmap_region(spriteSheet, (animateEnemy*playerWidth), (_kindOfActor*playerHeight), playerWidth, playerHeight, xCoord, yCoord, NULL);
    // we multiply kindOfEnemy*playerHeight
}

/**
* @fn canPlayerShoot
* @brief Is kind of a timer, so the Player won't be able to shoot all the bullets at the same time.
* @brief The player will be able to shoot only whenever the function returns is true.
* @author Victor Adad.
*/
bool ACTOR::canPlayerShoot(int timeForAnimation){
    BulletControlCounter++;
    if (BulletControlCounter == timeForAnimation){ /** loop for a certain amount of miliseconds */
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
    return true;
}

void initialize_all_enemies(struct ACTOR enemyIndex[]){
    int enemyNumber = -1;
    int _kindOfActor = 0;
    for(int row=0; row<5; row++){
        _kindOfActor++;
        if(_kindOfActor>3){
            _kindOfActor=1;
        }
        for (int column=0; column<11; column++){
            enemyNumber++;
            enemyIndex[enemyNumber].initializeActor("Resources/enemies.png", 50+(column*60), 100+(row*40), 50, 40, _kindOfActor); /**< we add column*60 and row*40 so the enemies will be separated */
            // the first two numbers is the position where the actor will appear (x, y)
            // the last two numbers are the Widht and Height of the actor
            // last number is 1 so we know is an enemy
        }
    }
}

void draw_all_enemies(struct ACTOR enemyIndex[], int animateEnemy){
    int enemyNumber = -1;
    int kindOfEnemy = -1; /**< This decides the sprite that each enemy will use */

    for(int row=0; row<5; row++){
        kindOfEnemy++;
        if(kindOfEnemy>2){ /**< kindOfEnemy goes from 0 to 2, because there are 3 total different sprites */
            kindOfEnemy = 0; /**< this condition resets the kindOfEnemy to 0 */
        }
        for (int column=0; column<11; column++){
            enemyNumber++;
            if(enemyIndex[enemyNumber].maxHealth > 0){ /**< if the enemy still has health left, draws it */
                enemyIndex[enemyNumber].drawOneEnemy(enemyIndex[enemyNumber].spritePlayer, kindOfEnemy, animateEnemy); /**< draws all the enemies */
                // the very last number is the kindOfEnemy, because it helps to change the sprites of the enemies
                // animateEnemy will go from 0-1 many times so it looks like they have animation
            }
        }
    }
}

#endif //actor.h
