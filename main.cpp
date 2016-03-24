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
#include <stdlib.h>
#include <time.h> /**< we add this library so we can generate (better) random numbers */
#include "projectile.h"
#include "actor.h"
#include "bullet.h"

void initialize_all_enemies(struct ACTOR enemyIndex[]){
    int enemyNumber = -1;
    for(int row=0; row<5; row++){
        for (int column=0; column<11; column++){
            enemyNumber++;
            enemyIndex[enemyNumber].initializeActor("Resources/enemies.png", 50+(column*60), 100+(row*40), 50, 40, 1); /**< we add column*60 and row*40 so the enemies will be separated */
            // the first two numbers is the position where the actor will appear (x, y)
            // the last two numbers are the Widht and Height of the actor
            // last number is 1 so we know is an enemy
        }
    }
}

void draw_all_enemies(struct ACTOR enemyIndex[]){
    int enemyNumber = -1;
    int kindOfEnemy = -1; /**< This decides the sprite that each enemy will use */
    for(int row=0; row<5; row++){
        kindOfEnemy++;
        if(kindOfEnemy>2){ /**< kindOfEnemy goes from 0 to 2, because there are 3 total different sprites */
            kindOfEnemy = 0; /**< this condition resets the kindOfEnemy to 0 */
        }
        for (int column=0; column<11; column++){
            enemyNumber++;
            enemyIndex[enemyNumber].drawOneEnemy(enemyIndex[enemyNumber].spritePlayer, kindOfEnemy); /**< draws all the enemies */
            // the very last number is the kindOfEnemy, because it helps to change the sprites of the enemies
        }
    }
}

/**
* @file main.cpp
* @brief Initialization of the display and the protagonist.
* C++ Allegro game for CPSC 2720 project:
* "Space Invaders -like- game"
* Credits to Erick Skiff for the music: http://ericskiff.com/music
* @author Adad, Bertram, Jiaying & Okingo.
* @bug No known bugs.
*/
int main()
{
    const float     SCREEN_WIDTH = 800.0, SCREEN_HEIGHT = 800.0;
    const float     SCREEN_LEFTEDGE = 0.0, SCREEN_RIGHTEDGE = SCREEN_WIDTH;
    const float     SCREEN_TOPEDGE = 0.0, SCREEN_BOTTOMEDGE = SCREEN_HEIGHT;
    const float FPS = 60.0; /**< Frames per second variable */
    bool done = false; /**< If done == true, the game ends. */
    bool draw = false; /**< If draw == true, the gamestate will be drawn to the display. */
    bool active = false; /**< Determines if a key is being pressed. */
    const int MOVERATE_PROJECTILES = -5; /**< if positive, the bullet goes down, if negative, it goes up */
    const int MOVERATE_ENEMY_PROJECTILES = 3; /**< if positive, the bullet goes down, if negative, it goes up */
    const int MOVERATE_ACTORS = 10;
    bool leftright = true; /**< Makes the enemy move: right = true, left = false */
    srand(time(NULL));
    int randomNumber = rand()%55; /**< generates random numbers between 0 and 55 */

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
    al_install_keyboard(); /**< intializes the hability to recieve commands from keyboard */

    // ALLEGRO_COLOR NEEDS TO BE USED AFTER INITIALZE THE PRIMITIVES_ADDON
    ALLEGRO_COLOR backgroundColor = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR textColor = al_map_rgb(254, 1, 64);
    ALLEGRO_COLOR titleColor = al_map_rgb(118, 180, 255);
    ALLEGRO_COLOR electricBlue = al_map_rgb(118,180,255);
    ALLEGRO_COLOR electricYellow = al_map_rgb(255,250,44);
    ALLEGRO_COLOR electricRed = al_map_rgb(254,1,64);

    ALLEGRO_FONT *font = al_load_font("Resources/Custom Font.ttf", 36, NULL);
    ALLEGRO_KEYBOARD_STATE keyboardState1;
    ALLEGRO_SAMPLE *sfxShoot = al_load_sample("Resources/spaceship_shoot.wav"); /**< loads audio file */
    ALLEGRO_SAMPLE *musicBGTheme = al_load_sample("Resources/Underclocked.wav"); /**< ALLEGRO_SAMPLE doesn't support mp3 or mid files */
    //ALLEGRO_SAMPLE *sfxMenuSelect = al_load_sample("Resources/file");
    al_reserve_samples(2); /**< indicate how many samples (songs) we are using */
    ALLEGRO_TIMER *timer1 = al_create_timer(1.0/FPS); /**< 60 frames per second */
    ALLEGRO_EVENT_QUEUE *event_queue1 = al_create_event_queue();
    al_register_event_source(event_queue1, al_get_timer_event_source(timer1));
    al_register_event_source(event_queue1, al_get_keyboard_event_source());
    al_register_event_source(event_queue1, al_get_display_event_source(display));
    /** @fn al_play_sample
    * @brief Starts playing the given audio
    * @param "musicBGTheme" is the ALLEGRO_SAMPLE variable wich includes the mp3 file
    * @param 1.0 is a float number corresponding the volume of the audio
    * @param 0.0 is a float number that shows from which side-speaker the audio should come out
    * @param 1.0 is the speed of the audio
    * @param ALLEGRO_PLAYMODE will decide the way the sound is played (once, loop, etc)
    */
    al_play_sample(musicBGTheme, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0); /**< plays the main theme */

    //std::vector<ProjectileBullet> bulletIndexFriendly;
    //std::vector<BULLETS> bulletsIndexHostile;
    //std::list<powerups> powerupIndex /** Create an index for each powerup type we choose to use.

    ACTOR playerShip;
    playerShip.initializeActor("Resources/spaceship_large.png", SCREEN_WIDTH/2, SCREEN_HEIGHT-100, 60, 40, 0);
    BULLETS BulletsArray[playerShip.maxBullets]; //creates Array

    ACTOR enemyIndex[60]; /**< Creates enemies VECTOR */
    initialize_all_enemies(enemyIndex);
    BULLETS enemyBullets[5]; //creates Array of 5 bullets

    // MENU display goes here, prior to gamestate
    /* MENU
    *
    *
    *
    */
    /* STAGE 1 FILE LOADING */
    /* Use as template for constructing future stages. */

    // GAME MAIN LOOP
    al_start_timer(timer1); /**< don't do anything nor initialize variables, NOTHING, after starting the timer */
    while(!done)  /**< the only thing that must be after the timer is the game loop (while) */
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue1, &events); /**< waits for something to happen */

        if(draw == false)  /**< shows HOME SCREEN and detects mouse clic, so the game starts */
        {
            al_draw_text(font, electricBlue, (SCREEN_WIDTH/2)+2, ScreenHeight/2, ALLEGRO_ALIGN_CENTRE, "PRESS START");
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0)); /**< cleans screen so it looks like moving */
            while (draw == false)
            {
                al_get_keyboard_state(&keyboardState1); /**< gets the imput from the keyboard */
                if(al_key_down(&keyboardState1, ALLEGRO_KEY_ENTER))  /**< pressing ENTER key */
                {
                    al_draw_text(font, electricYellow, (SCREEN_WIDTH/2)+2, ScreenHeight/2, ALLEGRO_ALIGN_CENTRE, "PRESS START");
                    al_flip_display();
                    al_rest(0.5);
                    draw = true; /**< starts the game */
                }
            }
        }

        if (events.type == ALLEGRO_EVENT_TIMER)  /**< movement of the things on screen */
        {
            al_get_keyboard_state(&keyboardState1); /**< IMPORTANT: gets the imput from the keyboard */

            playerShip.moveSpaceship(keyboardState1, MOVERATE_ACTORS); /**< Moves the spaceship */
            if(createBullet(playerShip, BulletsArray, MOVERATE_PROJECTILES, keyboardState1, sfxShoot) && playerShip.canPlayerShoot()){ /**< can player shoot is a boolean that controls the time between bullets */
                playerShip.currBullets++;
            }

            if(enemyIndex[randomNumber].currBullets == 0){ /**< Enemies shoot randomly */
                randomNumber = rand()%55; /**< generates random numbers between 0 and 55 */
                if(createEnemyBullet(enemyIndex[randomNumber], enemyBullets, MOVERATE_ENEMY_PROJECTILES, sfxShoot)){ /** Random shoot without using the space key */
                    enemyIndex[randomNumber].currBullets++;
                }
            }

            al_draw_text(font, electricYellow, (SCREEN_WIDTH/2)-2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!"); /**< blinks in pink and yellow */
            al_draw_text(font, al_map_rgb(254,50,200), (SCREEN_WIDTH/2)+2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!");


            /**< TODO: UNCOMMENT AFTER INITIALIZE SUCCESFULLY THE ARRAY OF ENEMIES */
//            if(CheckForCollision(playerShip.xCoord, playerShip.yCoord, enemyShip[0].xCoord, enemyShip[0].yCoord, playerShip.playerWidth, playerShip.playerHeight, enemyShip[0].playerWidth, enemyShip[0].playerHeight))
//            {
//                al_draw_text(font, al_map_rgb(254,117,200), SCREEN_WIDTH/2, ScreenHeight/3, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
//                al_flip_display();
//                al_clear_to_color(al_map_rgb(0,0,0)); /**< cleans screen and only shows GAME OVER */
//                al_rest(1.0);
//                playerShip.playerWidth += al_get_bitmap_width(playerShip.spritePlayer)/3; /**< simulates animation of spaceship */
//                //al_rest(1.0);
//                done = true; /**< ends the game */
//            }

            draw = true;

            if(al_key_down(&keyboardState1, ALLEGRO_KEY_ESCAPE))  /**< pressing scape key pauses the game */
            {
                al_draw_text(font, electricBlue, (SCREEN_WIDTH/2)+2, ScreenHeight/2, ALLEGRO_ALIGN_CENTRE, "PRESS START");
                al_flip_display();
                al_clear_to_color(al_map_rgb(0,0,0)); /**< cleans screen so it looks like moving */
                while (draw == false)
                {
                    al_get_keyboard_state(&keyboardState1); /**< gets the imput from the keyboard */
                    if(al_key_down(&keyboardState1, ALLEGRO_KEY_ENTER))  /**< pressing ENTER key */
                    {
                        al_draw_text(font, electricYellow, (SCREEN_WIDTH/2)+2, ScreenHeight/2, ALLEGRO_ALIGN_CENTRE, "PRESS START");
                        al_flip_display();
                        al_rest(0.5);
                        draw = true; /**< starts the game */
                    }
                }
                draw = false; /**< returns to main menu */
            }
        }

        if(draw == true) /**< Draws and refreshes all elements on screen */
        {
            // PLAYER'S BEHAVIOR
            playerShip.drawActor(playerShip.spritePlayer); /**< draws the Spaceship */
            if(drawBullet(playerShip, BulletsArray)){ /**< animates PLAYER's bullets */
                playerShip.currBullets--;  /**< destroys PLAYER's bullets */
                playerShip.BulletControlCounter = 0;
            }
            //ENEMY'S BEHAVIOR
//            bool temporal = enemyShip[0].moveEnemy(leftright);
//            leftright = temporal;
            draw_all_enemies(enemyIndex); /**< draws the enemy */
            if(drawBullet(enemyIndex[randomNumber], enemyBullets)){ /**< animates a random ENEMY's bullets */
                enemyIndex[randomNumber].currBullets--; /**< destroys that bullets */
                enemyIndex[randomNumber].BulletControlCounter = 0;
            }

            al_draw_text(font, al_map_rgb(44,117,255), SCREEN_WIDTH/2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!"); /**< draws the title */

            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0)); /**< cleans screen so it looks like moving */
        }
    }

    al_destroy_bitmap(playerShip.spritePlayer);
    al_destroy_sample(sfxShoot);
    al_destroy_sample(musicBGTheme);
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
