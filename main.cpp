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
    #include "initialize_components.h"

    /** @fn al_play_sample
    * @brief Starts playing the given audio
    * @param "musicBGTheme" is the ALLEGRO_SAMPLE variable wich includes the mp3 file
    * @param 1.0 is a float number corresponding the volume of the audio
    * @param 0.0 is a float number that shows from which side-speaker the audio should come out
    * @param 1.0 is the speed of the audio
    * @param ALLEGRO_PLAYMODE will decide the way the sound is played (once, loop, etc)
    */
    al_play_sample(musicBGTheme, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0); /**< plays the main theme */

    ACTOR playerShip;
    playerShip.initializeActor("Resources/spaceship.png", SCREEN_WIDTH/2, SCREEN_HEIGHT-100, 60, 40, 0);
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
    while(!done || playerShip.maxHealth<1)  /**< the only thing that must be after the timer is the game loop (while) */
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue1, &events); /**< waits for something to happen */

        al_get_keyboard_state(&keyboardState1); /**< IMPORTANT: gets the imput from the keyboard */



        if (events.type == ALLEGRO_EVENT_TIMER)  /**< movement of the things on screen */
        {
            if(al_key_down(&keyboardState1, ALLEGRO_KEY_ESCAPE))  /**< pressing scape key ends the game */
            {
                draw = false;
                done = true;
            }

            playerShip.moveSpaceship(keyboardState1, MOVERATE_ACTORS); /**< Moves the spaceship */
            if(createBullet(playerShip, BulletsArray, MOVERATE_PROJECTILES, keyboardState1, sfxShoot, playerShip.canPlayerShoot(5))){ /**< can player shoot is a boolean that controls the time between bullets */
                playerShip.currBullets++;
            }

            //############## HERE STARTS THE RANDOM ENEMY'S SHOOTING ############################
            if(enemyIndex[randomNumber].currBullets == 0){ /**< Enemies shoot randomly */
                randomNumber = rand()%55; /**< generates random numbers between 0 and 55 */
                if(createEnemyBullet(enemyIndex[randomNumber], enemyBullets, MOVERATE_ENEMY_PROJECTILES, sfxEnemyShoot)){ /** Random shoot without using the space key */
                    enemyIndex[randomNumber].currBullets++;
                }
            }

            //############## HERE STARTS THE BULLET - ENEMY COLLISION ############################
            for (int i=1; i <= playerShip.currBullets; i++)
            {
                if (BulletsArray[i].enemyBulletCollision(enemyIndex, playerShip)){ /**< Enemy colisions with bullet */
                    BulletsArray[i] = BulletsArray[playerShip .currBullets]; /**< this is necessary because bullets dissapear all at once if not implemented */
                    playerShip.currBullets--; /**< deletes bullet */
                }
            }

            //############# HERE STARTS THE SPACESHIP - BULLET COLLISION ############
            for (int i=0; i <= enemyIndex[randomNumber].currBullets; i++)
            {
                if(enemyBullets[i].collision(playerShip.xCoord, playerShip.yCoord, playerShip.playerWidth, playerShip.playerHeight)){
                    enemyBullets[i] = enemyBullets[enemyIndex[randomNumber].currBullets]; /**< this is necessary because bullets dissapear all at once if not implemented */
                    enemyIndex[randomNumber].currBullets--;
                    playerShip.spaceshipExplotes();
                }
            }

            //############# HERE STARTS THE SPACESHIP - ENEMY COLLISION ############
            for (int i=0; i <= 60; i++)
            {
                if(CheckForCollision(playerShip.xCoord, playerShip.yCoord, enemyIndex[i].xCoord, enemyIndex[i].yCoord, playerShip.playerWidth, playerShip.playerHeight, enemyIndex[i].playerWidth, enemyIndex[i].playerHeight))
                {
                    playerShip.spaceshipExplotes();
                    al_rest(0.5);
                    al_draw_text(font, al_map_rgb(254,117,200), SCREEN_WIDTH/2, SCREEN_HEIGHT/3, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
                    al_flip_display();
                    al_clear_to_color(backgroundColor); /**< cleans screen and only shows GAME OVER */
                    al_rest(1.0);

                    draw = false;
                    done = true; /**< ends the game */
                }
            }

            //############## HERE STARTS THE BLINKING TITLE ############################
            al_draw_text(font, electricYellow, (SCREEN_WIDTH/2)-2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!"); /**< blinks in pink and yellow */
            al_draw_text(font, al_map_rgb(254,50,200), (SCREEN_WIDTH/2)+2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!");
        }


        if(draw == false) // main menu
        {
            if(blinking++ < 20){
                /** @fn al_draw_bitmap_region
                * @brief Draws the MENU on the display from a PNG file.
                * @param player is and ALLEGRO_BITMAP variable that contains a PNG reference.
                * @param sx is a float that indiques where the sprite starts in the PNG file (usually x=0)
                * @param sy is a float that indiques where the sprite starts in the PNG file (usually y=0) so (X,Y) = (0,0)
                * @param sw is a float that indiques the actual width of the sprite
                * @param sh is a float that indiques the actual height of the sprite
                * @param x is the position on display where the sprite will be drawed
                * @param y is the position on display where the sprite will be drawed
                * @param the last parameter is a flag of the bitmap
                */
                al_draw_bitmap_region(menu, 0, menuY, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, NULL);
                al_flip_display();
                al_clear_to_color(backgroundColor); /**< cleans screen so it looks like moving */

            }else{
                al_draw_bitmap_region(menu, 1200, menuY, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, NULL);
                al_flip_display();
                al_clear_to_color(backgroundColor); /**< cleans screen so it looks like moving */
            }

            if(blinking > 40){
                blinking = 0;
            }

            if(al_key_down(&keyboardState1, ALLEGRO_KEY_ENTER))  /**< pressing ENTER key */
            {
                menuY = 800;
                loadingGame = true;
            }

            if(loadingGame == true){ /**< stops displaying "main menu" and starts displaying "loading" */
                loadingTimer++;
            }

            if (loadingTimer > 80){ /**< miliseconds the LOADING screen will be displayed */
                draw = true;
            }
        }
        else if(draw == true) /**< Draws and refreshes all elements on screen */
        {
            //############## ENEMY'S BEHAVIOR #####################
            if(enemyIndex[0].canPlayerShoot(10)){ /**< Enemies' individual sprite animation */
                moveAllEnemies(leftOrRight, enemyIndex, enemyMovement); /**< enemy's grupal movement left/right */
                if (++animateEnemy == 2){
                    animateEnemy = 0;
                }
            }
            if(enemyIndex[1].canPlayerShoot(500)){ /**< this will move the enemies faster and faster every time */
                if(gameSpeed >=  2){
                    gameSpeed -=1;
                    if (enemyMovement < 0){
                        leftOrRight += -1;
                    }else{
                        leftOrRight += 1;
                    }
                }
            }
            draw_all_enemies(enemyIndex, animateEnemy); /**< draws the enemies */

            //############## PLAYER'S BEHAVIOR ####################
            playerShip.drawActor(playerShip.spritePlayer); /**< draws the Spaceship */
            if(drawBullet(playerShip, BulletsArray)){ /**< animates PLAYER's bullets */
                playerShip.currBullets--;  /**< destroys PLAYER's bullets */
                playerShip.BulletControlCounter = 0;
            }

            //############# BULLET BEHAVIOR #################
            if(drawBullet(enemyIndex[randomNumber], enemyBullets)){ /**< animates a random ENEMY's bullets */
                enemyIndex[randomNumber].currBullets--; /**< destroys that bullets */
                enemyIndex[randomNumber].BulletControlCounter = 0;
            }

            al_draw_text(font, al_map_rgb(44,117,255), SCREEN_WIDTH/2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!"); /**< draws the title */
            al_flip_display();
            al_clear_to_color(backgroundColor); /**< cleans screen so it looks like moving */
        }
    }

    al_destroy_bitmap(playerShip.spritePlayer);
    al_destroy_sample(sfxShoot);
    al_destroy_sample(sfxEnemyShoot);
    al_destroy_sample(musicBGTheme);
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
