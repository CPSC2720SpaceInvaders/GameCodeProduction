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

    ACTOR playerShip; /**< Initialize a new ACTOR called playerShip to be our main character */
    playerShip.initializeActor("Resources/spaceship.png", SCREEN_WIDTH/2, SCREEN_HEIGHT-100, 60, 40, 0); /**< given values to the new actor */
    BULLETS BulletsArray[playerShip.maxBullets]; //creates Array

    ACTOR enemyIndex[60]; /**< Creates enemies array */
    initialize_all_enemies(enemyIndex); /** fills the array */
    BULLETS enemyBullets[5]; //creates Array of 5 bullets

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
        al_get_keyboard_state(&keyboardState1); /**< IMPORTANT: gets the imput from the keyboard */

        if(draw == false) // main menu
        {
            #include "main_menu_display.h"
        }
        else if(draw == true) /**< Draws and refreshes all elements on screen */
        {
             if(al_key_down(&keyboardState1, ALLEGRO_KEY_ESCAPE))  /**< pressing scape key ends the game */
            {
                draw = false;
                done = true;
            }

            //############################################### SPACESHIP ############################

            playerShip.moveSpaceship(keyboardState1, MOVERATE_ACTORS); /**< Moves the spaceship */
            if(createBullet(playerShip, BulletsArray, MOVERATE_PROJECTILES, keyboardState1, sfxShoot, playerShip.canPlayerShoot(5))){ /**< can player shoot is a boolean that controls the time between bullets */
                playerShip.currBullets++;
            }

            for (int i=0; i <= 60; i++) /**< Spaceship & enemy collision */
            {
                if(CheckForCollision(playerShip.xCoord, playerShip.yCoord, enemyIndex[i].xCoord, enemyIndex[i].yCoord, playerShip.playerWidth, playerShip.playerHeight, enemyIndex[i].playerWidth, enemyIndex[i].playerHeight))
                {
                    playerShip.spaceshipExplotes();
                    gameOverScreen(draw, done, font);
                }
            }

            for (int i=0; i <= enemyIndex[randomNumber].currBullets; i++) /**< Spaceship & bullet colision */
            {
                if(enemyBullets[i].collision(playerShip.xCoord, playerShip.yCoord, playerShip.playerWidth, playerShip.playerHeight)){
                    enemyBullets[i] = enemyBullets[enemyIndex[randomNumber].currBullets]; /**< this is necessary because bullets dissapear all at once if not implemented */
                    enemyIndex[randomNumber].currBullets--; /**< bullet gets deleted */
                    playerShip.maxHealth--; /**< the player's health is reduced */
                    playerShip.spaceshipExplotes(); /**< animation of the spaceship exploting */
                    if (playerShip.maxHealth<1){
                        gameOverScreen(draw, done, font); /**< calls the game over function */
                    }
                }
            }

            playerShip.drawActor(playerShip.spritePlayer); /**< draws the Spaceship */
            if(drawBullet(playerShip, BulletsArray)){ /**< animates PLAYER's bullets */
                playerShip.currBullets--;  /**< destroys PLAYER's bullets */
                playerShip.BulletControlCounter = 0;
            }

            //############################################### ENEMIES ############################

            if(enemyIndex[randomNumber].currBullets == 0){ /**< Enemies shoot randomly */
                randomNumber = rand()%55; /**< generates random numbers between 0 and 55 */
                if(createEnemyBullet(enemyIndex[randomNumber], enemyBullets, MOVERATE_ENEMY_PROJECTILES, sfxEnemyShoot)){ /** Random shoot without using the space key */
                    enemyIndex[randomNumber].currBullets++;
                }
            }

            for (int i=1; i <= playerShip.currBullets; i++) /**< Enemies & bullet colision */
            {
                if (BulletsArray[i].enemyBulletCollision(enemyIndex, playerShip)){ /**< Enemy colisions with bullet */
                    BulletsArray[i] = BulletsArray[playerShip .currBullets]; /**< this is necessary because bullets dissapear all at once if not implemented */
                    playerShip.currBullets--; /**< deletes bullet */
                }
            }

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

            if(drawBullet(enemyIndex[randomNumber], enemyBullets)){ /**< animates a random ENEMY's bullets */
                enemyIndex[randomNumber].currBullets--; /**< destroys that bullets */
                enemyIndex[randomNumber].BulletControlCounter = 0;
            }

            draw_all_enemies(enemyIndex, animateEnemy); /**< draws the enemies */

            //####################### TITLE ANND DRAWING  ##############################

            al_draw_text(font, electricYellow, (SCREEN_WIDTH/2)-2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!"); /**< blinks in pink and yellow */
            al_draw_text(font, al_map_rgb(254,50,200), (SCREEN_WIDTH/2)+2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!");
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
