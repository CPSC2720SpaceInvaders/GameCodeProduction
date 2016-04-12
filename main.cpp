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
#include "actorPlayer.h"
#include "actorEnemyBasic.h"
//#include "actorEnemySprinter.h"
//#include "actorEnemyBosses.h"

using namespace std;

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

    ActorPlayer playerShip;
	vector<ProjectileBullet> friendlyBulletIndex;
	vector<ProjectileBullet> hostileBulletIndex;
	vector<ActorEnemyBasic> basicEnemyIndex;
	//vector<ActorEnemySprinter> sprinterEnemyIndex;
	//vector<ActorEnemyBoss> bossEnemyIndex;
	

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

		if (currStage = 1) // main menu
        {
            #include "main_menu_display.h"
        }
		else /**< Updates and draws all elements on screen */
		{
			if (al_key_down(&keyboardState1, ALLEGRO_KEY_ESCAPE))  /**< pressing scape key ends the game */
			{
				done = true;
			}

			//############################################### PREVIOUS UPDATE CLEANUP ##################
			for (int i = 0; i < basicEnemyIndex.size(); i++) {
				if (basicEnemyIndex.at(i).isDead) {
					basicEnemyIndex.erase(i);
				}
			}


			//############################################### UPDATE PLAYER ############################

			//playerShip.moveSpaceship(keyboardState1, MOVERATE_ACTORS); /**< Moves the spaceship */
			//if (createBullet(playerShip, BulletsArray, MOVERATE_PROJECTILES, keyboardState1, sfxShoot, playerShip.canPlayerShoot(5))) { /**< can player shoot is a boolean that controls the time between bullets */
			//	playerShip.currBullets++;
			//}


			//Check if the player is dead, and also if the player has exhausted all their allotted lives.
			if (playerShip.CheckDead()) {
				playerShip.KillPlayer(*playerSprite, 40.0, 50.0, 600.0, 700.0);
			}

			if (playerShip.GetLives() < 0) {
				//currStage = 0; /**< Changes to the game over screen. */
				done = true;
			}

			//Get input and move the player accordingly.
			if (al_key_down(&keyboardState1, ALLEGRO_KEY_UP)) {
				moveUp = true;
			}if (al_key_down(&keyboardState1, ALLEGRO_KEY_DOWN)) {
				moveDown = true;
			}if (al_key_down(&keyboardState1, ALLEGRO_KEY_RIGHT)) {
				moveRight = true;
			}if (al_key_down(&keyboardState1, ALLEGRO_KEY_LEFT)) {
				moveLeft = true;
			}

			playerShip.MoveActor(moveUp, moveDown, moveRight, moveLeft, MOVERATE_ACTORS);
			moveUp = false; moveDown = false; moveRight = false; moveLeft = false;

			//Check if the player has flown into any of the enemy objects. Death resolution is handled elsewhere.
			for (int i = 0; i < basicEnemyIndex.size(); i++) {
				if (playerShip.actorHitbox.CheckForCollision(basicEnemyIndex.at(i).actorHitbox)) {
					playerShip.ModifyHealth(playerShip.GetHealth());
					playerShip.ChangeActorSprite(playerDeathSprite, 82, 68);

					basicEnemyIndex.at(i).isDead = true;
					basicEnemyIndex.at(i).ChangeActorSprite(enemyDeathSprite, 82, 68);
				}
			}

			//Control firing of friendly bullets.
			if (al_key_down(&keyboardState1, ALLEGRO_KEY_SPACE)) {
				if (!(friendlyBulletIndex.size() == playerShip.maxBullets) && bulletControlCounter == 5) {
					friendlyBulletIndex.emplace_back(playerShip.GetXCoord(), playerShip.GetYCoord(), UP);
					bulletControlCounter = 0;
				}
				else {
					bulletControlCounter++;
				}
			}
			else {
				bulletControlCounter++;
			}


            //for (int i=0; i <= 60; i++) /**< Spaceship & enemy collision */
            //{
            //   if(CheckForCollision(playerShip.xCoord, playerShip.yCoord, enemyIndex[i].xCoord, enemyIndex[i].yCoord, playerShip.playerWidth, playerShip.playerHeight, enemyIndex[i].playerWidth, enemyIndex[i].playerHeight))
            //    {
            //        playerShip.spaceshipExplotes();
            //        gameOverScreen(draw, done, font);
            //    }
            //}

            //for (int i=0; i <= enemyIndex[randomNumber].currBullets; i++) /**< Spaceship & bullet colision */
            //{
            //    if(enemyBullets[i].collision(playerShip.xCoord, playerShip.yCoord, playerShip.playerWidth, playerShip.playerHeight)){
            //        enemyBullets[i] = enemyBullets[enemyIndex[randomNumber].currBullets]; /**< this is necessary because bullets dissapear all at once if not implemented */
            //        enemyIndex[randomNumber].currBullets--;
            //        playerShip.maxHealth--;
            //        playerShip.spaceshipExplotes();
            //        if (playerShip.maxHealth<1){
            //            gameOverScreen(draw, done, font);
            //        }
            //    }
            //}

            //playerShip.drawActor(playerShip.spritePlayer); /**< draws the Spaceship */
            //if(drawBullet(playerShip, BulletsArray)){ /**< animates PLAYER's bullets */
            //    playerShip.currBullets--;  /**< destroys PLAYER's bullets */
            //    playerShip.BulletControlCounter = 0;
            //}

            //############################################### UPDATE ENEMIES ############################

			//Move all elements of each enemy index.
			for (int i = 0; i < basicEnemyIndex.size(); i++) {
				basicEnemyIndex.at(i).MoveActor(MOVERATE_ACTORS, SCREEN_WIDTH);
			}

			//Check to see if any of the enemy objects have collided with the player.
			for (int i = 0; i < basicEnemyIndex.size(); i++) {
				if (playerShip.actorHitbox.CheckForCollision(basicEnemyIndex.at(i).actorHitbox) && !(basicEnemyIndex.at(i).isDead)) {
					playerShip.ModifyHealth(playerShip.GetHealth());
					playerShip.ChangeActorSprite(playerDeathSprite, 82, 68);

					basicEnemyIndex.at(i).isDead = true;
					basicEnemyIndex.at(i).ChangeActorSprite(enemyDeathSprite, 82, 68);
				}
			}

			//Check to see if any enemy should fire a bullet, and if so, generate it.
			//One or no basic enemies will fire a bullet each update phase, depending on a certain percentile chance.
			randomNumber = rand() % basicEnemyIndex.size();
			randomNumber2 = rand() % 100;
			if (randomNumber2 >= 80) {
				hostileBulletIndex.emplace_back(basicEnemyIndex.at(randomNumber).GetXCoord, basicEnemyIndex.at(randomNumber).GetYCoord, DOWN);
			}


            //if(enemyIndex[randomNumber].currBullets == 0){ /**< Enemies shoot randomly */
            //    randomNumber = rand()%55; /**< generates random numbers between 0 and 55 */
            //    if(createEnemyBullet(enemyIndex[randomNumber], enemyBullets, MOVERATE_ENEMY_PROJECTILES, sfxEnemyShoot)){ /** Random shoot without using the space key */
            //        enemyIndex[randomNumber].currBullets++;
            //    }
            //}

            //for (int i=1; i <= playerShip.currBullets; i++) /**< Enemies & bullet colision */
            //{
            //    if (BulletsArray[i].enemyBulletCollision(enemyIndex, playerShip)){ /**< Enemy colisions with bullet */
            //        BulletsArray[i] = BulletsArray[playerShip .currBullets]; /**< this is necessary because bullets dissapear all at once if not implemented */
            //        playerShip.currBullets--; /**< deletes bullet */
            //    }
            //}

            //if(enemyIndex[0].canPlayerShoot(10)){ /**< Enemies' individual sprite animation */
            //    moveAllEnemies(leftOrRight, enemyIndex, enemyMovement); /**< enemy's grupal movement left/right */
            //    if (++animateEnemy == 2){
            //        animateEnemy = 0;
            //    }
            //}
            //if(enemyIndex[1].canPlayerShoot(500)){ /**< this will move the enemies faster and faster every time */
            //    if(gameSpeed >=  2){
            //        gameSpeed -=1;
            //        if (enemyMovement < 0){
			//
            //            leftOrRight += -1;
            //        }else{
            //            leftOrRight += 1;
            //        }
            //    }
            //}

            //if(drawBullet(enemyIndex[randomNumber], enemyBullets)){ /**< animates a random ENEMY's bullets */
            //    enemyIndex[randomNumber].currBullets--; /**< destroys that bullets */
            //    enemyIndex[randomNumber].BulletControlCounter = 0;
            //}

            //draw_all_enemies(enemyIndex, animateEnemy); /**< draws the enemies */

			//####################### UPDATE PROJECTILES ###############################

			//Move all bullets.
			for (int i = 0; i < friendlyBulletIndex.size(); i++) {
				friendlyBulletIndex.at(i).MoveProjectile(MOVERATE_PROJECTILES, UP);
			}
			for (int i = 0; i < hostileBulletIndex.size(); i++) {
				hostileBulletIndex.at(i).MoveProjectile(MOVERATE_PROJECTILES, DOWN);
			}

			//Check for collisions with valid objects.
			for (int i = 0; i < friendlyBulletIndex.size(); i++) {
				for (int j = 0; j < basicEnemyIndex.size(); j++) {
					if (friendlyBulletIndex.at(i).projectileHitbox.CheckForCollision(basicEnemyIndex.at(j).actorHitbox) && !(basicEnemyIndex.at(j).isDead)) {
						basicEnemyIndex.at(j).ModifyHealth(friendlyBulletIndex.at(i).GetDamage());
						if (basicEnemyIndex.at(j).CheckDead()) {
							basicEnemyIndex.at(j).isDead = true;
							basicEnemyIndex.at(i).ChangeActorSprite(enemyDeathSprite, 82, 68);
						}

						friendlyBulletIndex.erase(i);
					}
				}
			}

			for (int i = 0; i < hostileBulletIndex.size(); i++) {
				if (hostileBulletIndex.at(i).projectileHitbox.CheckForCollision(playerShip.actorHitbox)) {
					playerShip.ModifyHealth(hostileBulletIndex.at(i).GetDamage());
					if (playerShip.CheckDead()) {
						playerShip.ChangeActorSprite(playerDeathSprite, 82, 68);
					}

					hostileBulletIndex.erase(i);
				}
			}

			//####################### DRAW ALL OBJECTS #################################

			playerShip.DrawActor();
			for (int i = 0; i < basicEnemyIndex.size(); i++) {
				basicEnemyIndex.at(i).DrawActor();
			}
			for (int i = 0; i < friendlyBulletIndex.size(); i++) {
				friendlyBulletIndex.at(i).DrawProjectile();
			}
			for (int i = 0; i < hostileBulletIndex; i++) {
				hostileBulletIndex.at(i).DrawProjectile();
			}
			al_flip_display();
			al_clear_to_color(backgroundColor);

            //####################### TITLE ANND DRAWING  ##############################

            //al_draw_text(font, electricYellow, (SCREEN_WIDTH/2)-2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!"); /**< blinks in pink and yellow */
            //al_draw_text(font, al_map_rgb(254,50,200), (SCREEN_WIDTH/2)+2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!");
            //al_draw_text(font, al_map_rgb(44,117,255), SCREEN_WIDTH/2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!"); /**< draws the title */
            //al_flip_display();
            //al_clear_to_color(backgroundColor); /**< cleans screen so it looks like moving */
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
