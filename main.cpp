#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <vector>
#include "projectile.h"
//#define SCREEN_WIDTH 800
//#define ScreenHeight 800

/**
* @file main.cpp
* @brief Initialization of the display and the protagonist.
* C++ Allegro game for CPSC 2720 project:
* "Space Invaders -like- game"
* Credits to Erick Skiff for the music: http://ericskiff.com/music
* @author Adad, Bertram, Jiaying & Okingo.
* @bug No known bugs.
*/

const int ScreenWidth = 800;
const int ScreenHeight = 800;
const int moveSpeed = 10;

#include "actor.h"
#include "bullet.h"

int main()
{
    const float		SCREEN_WIDTH = 800.0, SCREEN_HEIGHT = 800.0;
	const float		SCREEN_LEFTEDGE = 0.0, SCREEN_RIGHTEDGE = SCREEN_WIDTH;
	const float		SCREEN_TOPEDGE = 0.0, SCREEN_BOTTOMEDGE = SCREEN_HEIGHT;
	const float FPS = 60.0; /**< Frames per second variable */
	bool done = false; /**< If done == true, the game ends. */
	bool draw = false; /**< If draw == true, the gamestate will be drawn to the display. */
	bool active = false; /**< Determines if a key is being pressed. */
	const int MOVERATE_PROJECTILES = 10;
	const int MOVERATE_ACTORS = 10;
    const int maxBullets = 5;

	int playerWidth = 60;
    int playerHeight = 40; /**< represent the width and height of the spaceship inside the PNG file */
    float enemyX = 10.0;
    float enemyY = 100.0;
    int enemyWidth = 60;
    int enemyHeight = 40; /**< represent the width and height of the spaceship inside the PNG file */
    int enemyMaxHealth = 1;
    int leftright = 1; /**< Makes the enemy go left = 0, right = 1 */
    bool CanPlayerShoot = true;
    int BulletControlCounter = 0;



	std::vector<Actor> playerIndex;
	std::vector<Actor> enemyIndex;
	std::vector<ProjectileBullet> bulletIndexFriendly;
	std::vector<ProjectileBullet> bulletIndexHostile;
	//std::list<powerups> powerupIndex /** Create an index for each powerup type we choose to use.

    if(!al_init())   /**< do NOT initialice anything before al_init(); */
    {
        al_show_native_message_box(NULL, "Error", "Allegro Settings", "Failed to initialize allegro 5!", NULL, NULL);
        return -1;
    }
    al_set_new_display_flags(ALLEGRO_NOFRAME); /**< Screen without frames */
    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT); /**< Creates main display */
    if(!display)
    {
        al_show_native_message_box(display, "Error", "Display Settings", "Display window was unsuccessfull", NULL, NULL);
        return -1; /**< error message in case display couldn't be created */
    }
    al_set_window_position(display, 100, 100);
    al_set_window_title(display, "2720's Project");

    //######################### HERE FINISHES THE INITIALIZATION OF THE DISPLAY ###########################

    //Initialize universal allegro aspects required for the game
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon(); /**< intializes primitives to draw figures */
	al_install_audio(); /**< intializes the hability play audio */
	al_init_acodec_addon();
	al_init_image_addon();
	al_install_mouse(); /**< initializes the use of the cursor */
	al_install_keyboard(); /**< intializes the hability to recieve commands from keyboard */

	// ALLEGRO_COLOR NEEDS TO BE USED AFTER INITIALZE THE PRIMITIVES_ADDON
    ALLEGRO_COLOR backgroundColor = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR textColor = al_map_rgb(254, 1, 64);
	ALLEGRO_COLOR titleColor = al_map_rgb(118, 180, 255);
    ALLEGRO_COLOR electricBlue = al_map_rgb(118,180,255);
    ALLEGRO_COLOR electricYellow = al_map_rgb(255,250,44);
    ALLEGRO_COLOR electricRed = al_map_rgb(254,1,64);
    ALLEGRO_COLOR playerColor = electricBlue; /**< original color of the circle */

    ALLEGRO_FONT *font = al_load_font("Resources/Custom Font.ttf", 36, NULL);
    ALLEGRO_KEYBOARD_STATE keyboardState1;
    ALLEGRO_SAMPLE *sfxShoot = al_load_sample("Resources/spaceship_shoot.wav"); /**< loads audio file */
    ALLEGRO_SAMPLE *main_song = al_load_sample("Resources/Underclocked.wav"); /**< ALLEGRO_SAMPLE doesn't support mp3 or mid files */
    al_reserve_samples(2); /**< indicate how many samples (songs) we are using */
    al_play_sample(main_song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0); /**< plays the main theme */
    ALLEGRO_TIMER *timer1 = al_create_timer(1.0/FPS); /**< 60 frames per second */
    ALLEGRO_EVENT_QUEUE *event_queue1 = al_create_event_queue();
    al_register_event_source(event_queue1, al_get_timer_event_source(timer1));
    al_register_event_source(event_queue1, al_get_keyboard_event_source());
    al_register_event_source(event_queue1, al_get_display_event_source(display));
    al_register_event_source(event_queue1, al_get_mouse_event_source());
    ALLEGRO_BITMAP *player = al_load_bitmap("Resources/spaceship_large.png"); /**< loads player sprite */
    ALLEGRO_BITMAP *enemy1 = al_load_bitmap("Resources/enemy1.png");
//    if(!player)
//    {
//        al_show_native_message_box(display, "Message Title", "Bitmap Settings", "Could not load Player", NULL, NULL);
//    }
    Bullets BulletsArray[maxBullets]; //creates Array

    // GAME MAIN LOOP
    al_start_timer(timer1); /**< don't do anything nor initialize variables, NOTHING, after starting the timer */
    while(!done)  /**< the only thing that must be after the timer is the game loop (while) */
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue1, &events); /**< waits for something to happen */

        if(draw == false)  /**< shows HOME SCREEN and detects mouse clic, so the game starts */
        {
            al_draw_text(font, playerColor, (SCREEN_WIDTH/2)+2, ScreenHeight/2, ALLEGRO_ALIGN_CENTRE, "PRESS START");
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0)); /**< cleans screen so it looks like moving */

            while (draw == false)
            {
                al_get_keyboard_state(&keyboardState1); /**< gets the imput from the keyboard */
                if(al_key_down(&keyboardState1, ALLEGRO_KEY_ENTER))  /**< pressing ENTER key */
                {
                    playerColor = electricYellow;
                    al_draw_text(font, playerColor, (SCREEN_WIDTH/2)+2, ScreenHeight/2, ALLEGRO_ALIGN_CENTRE, "PRESS START");
                    al_flip_display();
                    al_rest(0.5);
                    draw = true; /**< ends the game */
                }
            }
        }

        if (events.type == ALLEGRO_EVENT_TIMER)  /**< movement of the spaceship */
        {

            al_get_keyboard_state(&keyboardState1); /**< gets the imput from the keyboard */
            active = true;

            if(al_key_down(&keyboardState1, ALLEGRO_KEY_ESCAPE))  /**< pressing scape key */
            {
                al_draw_text(font, al_map_rgb(254,117,200), SCREEN_WIDTH/2, ScreenHeight/3, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
                al_rest(1.0);
                done = true; /**< ends the game */
            }

            if(al_key_down(&keyboardState1, ALLEGRO_KEY_DOWN))
            {
                playerShip.playerY += moveSpeed;

            }
            else if (al_key_down(&keyboardState1, ALLEGRO_KEY_UP))
            {
                playerShip.playerY -= moveSpeed;

            }
            else if (al_key_down(&keyboardState1, ALLEGRO_KEY_RIGHT))
            {
                playerShip.playerX += moveSpeed;

            }
            else if (al_key_down(&keyboardState1, ALLEGRO_KEY_LEFT))
            {
                playerShip.playerX -= moveSpeed;

            }
            else if (al_key_down(&keyboardState1, ALLEGRO_KEY_SPACE) && CanPlayerShoot==true)
            {
                if(createBullet(playerShip, maxBullets, BulletsArray)){
                    /** @fn al_play_sample(sfxShoot, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    * @brief Starts playing the given audio
                    * @param "sfxShoot" is the ALLEGRO_SAMPLE variable wich includes the mp3 file
                    * @param 1.0 is a float number corresponding the volume of the audio
                    * @param 0.0 is a float number that shows from which side-speaker the audio should come out
                    * @param 1.0 is the speed of the audio
                    * @param ALLEGRO_PLAYMODE will decide the way the sound is played (once, loop, etc)
                    */
                    al_play_sample(sfxShoot, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); /**< plays sound */
                    playerShip.currBullets++;
                    CanPlayerShoot=false;
                }

                al_draw_text(font, electricYellow, (SCREEN_WIDTH/2)-2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!");
                al_draw_text(font, al_map_rgb(254,50,200), (SCREEN_WIDTH/2)+2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!");

            }

            if(BulletControlCounter++ > 20)  //time before the player is able to shoot again
            {
                CanPlayerShoot = true;
                BulletControlCounter = 0;
            }

            drawBullet(playerShip, maxBullets, BulletsArray);
            if(deleteBullet(playerShip, maxBullets, BulletsArray)){
                playerShip.currBullets--;
                CanPlayerShoot=true;
            }

            if(Collision(playerShip.playerX, playerShip.playerY, enemyX, enemyY, playerWidth, playerHeight, enemyWidth, enemyHeight))
            {
                al_draw_text(font, al_map_rgb(254,117,200), SCREEN_WIDTH/2, ScreenHeight/3, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
                al_rest(1.0);
                playerWidth += al_get_bitmap_width(player)/3; /**< simulates animation of spaceship */
                //al_rest(1.0);
                done = true; /**< ends the game */
            }

            draw = true;
        }

        if(draw == true)
        {
            //draw = false;
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
            drawSpaceship(player, playerShip);
            //al_draw_bitmap_region(player, 0, 0, playerWidth, playerHeight, playerShip.playerX, playerShip.playerY, NULL); //0 should be playerShip.playerY * al_get_bitmap_heght(player)/numberofframesvertically
            al_draw_text(font, al_map_rgb(44,117,255), SCREEN_WIDTH/2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!");
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0)); /**< cleans screen so it looks like moving */
            al_draw_bitmap_region(enemy1, 0, 0, 50, 40, enemyX, enemyY, NULL);

            if (enemyX < 700 && leftright==1)  /**< enemy goes right */
            {
                enemyX += 3;

            }
            else if (enemyX > 100 && leftright==0)    /**< enemy goes right */
            {
                enemyX -= 3;
            }

            if(enemyX >= 700 && enemyY < 700 && leftright==1)  /**< enemy goes down once, then moves right */
            {
                enemyY += 50;
                leftright = 0;
            }

            if(enemyX <= 100 && enemyY < 700 && leftright==0)  /**< enemy goes down once, then moves left */
            {
                enemyY += 50;
                leftright = 1;
            }
        }
    }
    al_destroy_bitmap(player);
    al_destroy_sample(sfxShoot);
    al_destroy_sample(main_song);
    al_destroy_display(display);
    al_destroy_timer(timer1);
    al_destroy_event_queue(event_queue1);
    return 0;
}


/**
* @fn initialize_allegro_and_display()
* @brief Is the first and most important function.
* Creates and makes sure Allegro, the display, and the window containing the display, work.
* Still doesn't have nothing inside, because the *display is required later in the main.
* @param No parameters required.
* @return I'm gessuing it should return the *display, but I haven't figurerd out how to do that yet.
*/
