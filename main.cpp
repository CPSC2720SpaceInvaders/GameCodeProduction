/**
* @file		main.cpp
*
* @brief	An imitation of early SHMUP games like Galaga or Space Invaders.
*			A C++ Allegro game for CPSC 2720 term project.
*
*			--Resource Credits--
*			Eric Skiff ( http://ericskiff.com/music ) for the
*			music track Underclocked.
*			Dalton Maag (http://www.daltonmaag.com ) for the
*			Ubuntu font.
*			
* 
* @author	Victor Adad, Tyler Bertram
* @bug		No known bugs.
*/

#include <stdio.h>
#include <allegro5/allegro.h>
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
#include <time.h>
#include <map>
#include <algorithm>
#include "projectile.h"
#include "actor.h"
#include "bullet.h"
#include "actorPlayer.h"
#include "actorEnemyBasic.h"
//#include "actorEnemySprinter.h"
//#include "actorEnemyBosses.h"
#include "objectSpawners.h"

/**
*	@fn			enemyRemovePred( const ActorEnemyBasic target )
*	@brief		Predicate for remove_if call on the basic enemy index.
*
*	@param		target		ActorEnemyBasic type object. We check the isDead boolian member and return its value.
*
*	@return		Boolian value.
*/
bool enemyRemovePred(const ActorEnemyBasic target) {
	if (target.isDead) {
		return true;
	}
	else {
		return false;
	}
}

/**
*	@fn			bulletRemovePred( const ProjectileBullet target )
*	@brief		Predicate for remove_if call on the bullet indices.
*
*	@param		target		ProjectileBullet type object. We check the projInactive boolian member and return its value.
*
*	@return		Boolian value.
*/
bool bulletRemovePred(const ProjectileBullet target) {
	if (target.projInactive) {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	const float			SCREEN_WIDTH = 1200.0, SCREEN_HEIGHT = 800.0;					/**< Screen dimension constants. */
	const float			SCREEN_LEFTEDGE = 0.0, SCREEN_RIGHTEDGE = SCREEN_WIDTH;			/**< Screen dimension constants. */
	const float			SCREEN_TOPEDGE = 0.0, SCREEN_BOTTOMEDGE = SCREEN_HEIGHT;		/**< Screen dimension constants. */
	const float			FPS = 60.0;														/**< Frames per second variable */
	bool				done = false;													/**< If done == true, the game ends. */
	bool				draw = true;													/**< If draw == true, the gamestate will be drawn to the display. */
	bool				moveUp = false; bool moveDown = false;							/**< Passed to the player object to control movement. */
	bool				moveRight = false; bool moveLeft = false;						/**< Passed to the player object to control movement. */
	const int			MOVERATE_PROJECTILES = 5;										/**< If set to a negative value, the bullet will move in the opposite direction intended. This is undesirable behaviour. */
	const int			MOVERATE_ENEMY_PROJECTILES = 3;									/**< If set to a negative value, the bullet will move in the opposite direction intended. This is undesirable behaviour. */
	const int			MOVERATE_ACTORS = 5;											/**< Controls movement both of the player and enemies. */
	int					randomNumber = rand() % 55;										/**< Random number storage variable for misc usage. */
	int					randomNumber2;													/**< Random number storage variable for misc usage. */
	int					blinking = 0;													/**< Used in animating the main menu/loading screen. */
	int					menuY = 0;														/**< Vertical location in the menu bitmap to start drawing from. */
	int					totalStages = 3;												/**< Used to end the game when the player has completed all available stages. Note, the menu is considered stage 1, as the victory screen is stage 0 and death is stage -1. */
	bool				loadingGame = false;											/**< If false, then displays main menu, if true, the "loading" screen will be shown. */
	int					loadingTimer = 0;												/**< Sums amount of time that the "loading" screen will be displayed. */
	int					currStage = 1;													/**< Defines the current stage, which controls execution of certain code in the game loop. Initialized to 1 for the menu. */
	bool				setupStage = true;												/**< If true, the first-time enemy set-up for a stage will be performed. Initialized to true for this reason, so that the first stage sets up correctly. */

	ALLEGRO_DISPLAY		*display = NULL;												/**< Until allegro is initialized, this must be a null pointers. */

	/** Exception handling in the case that allegro does not initialize. This function MUST be called first. */
	if ( !al_init() )
	{
		al_show_native_message_box( NULL, "Error", "Allegro Settings", "Failed to initialize allegro 5!", NULL, NULL );
		//return -1;
	}
	
	al_set_new_display_flags(ALLEGRO_WINDOWED);
						display = al_create_display( SCREEN_WIDTH, SCREEN_HEIGHT );		/**< Sets up the previously declared display. */
	/** Exception handling in case the display fails to set up. */
	if ( !display )
	{
		al_show_native_message_box( display, "Error", "Display Settings", "Display window was unsuccessfull", NULL, NULL );
		//return -1; /**< error message in case display couldn't be created */
	}

	al_set_window_position( display, 0, 0 );
	al_set_window_title( display, "2720 Project" );

	/** Initialize various allegro modules. */
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	al_install_keyboard();

	/** Initialization of Allegro-specific types that required the init funcs above in order to be declared. */
	ALLEGRO_COLOR		backgroundColor = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR		textColor = al_map_rgb(254, 1, 64);
	ALLEGRO_COLOR		titleColor = al_map_rgb(118, 180, 255);
	ALLEGRO_COLOR		electricBlue = al_map_rgb(118, 180, 255);
	ALLEGRO_COLOR		electricYellow = al_map_rgb(255, 250, 44);
	ALLEGRO_COLOR		electricRed = al_map_rgb(254, 1, 64);
	ALLEGRO_FONT		*font = al_load_font("Resources/Ubuntu-regular.ttf", 36, NULL);
	ALLEGRO_KEYBOARD_STATE	keyboardState1;
	ALLEGRO_SAMPLE		*sfxShoot = al_load_sample("Resources/spaceship_shoot.wav");
	ALLEGRO_SAMPLE		*sfxEnemyShoot = al_load_sample("Resources/enemy_shoot.wav");
	ALLEGRO_SAMPLE		*musicBGTheme = al_load_sample("Resources/Underclocked.wav");	/**< ALLEGRO_SAMPLE doesn't support mp3 or midi files. */
	al_reserve_samples( 3 );															/**< Indicate how many samples (sound files) we are using. */
	ALLEGRO_TIMER		*timer1 = al_create_timer(1.0 / FPS); 
	ALLEGRO_EVENT_QUEUE *event_queue1 = al_create_event_queue();

	/** 
	*	Syntax for spriteIndex keys:
	*	x yz
	*	x:		0: abstract object, for instance buttons or menu elements;
	*			1: actor sprites, for instance the player's ship
	*			2+:	misc indices, unlikely to be used
	*	yz:		order of loading. For instance, 000 is the first menu object loaded.
	*/
	std::map<int, ALLEGRO_BITMAP*> spriteIndex;
						spriteIndex[000] = al_load_bitmap( "Resources/STARTMENU.png" );
						spriteIndex[101] = al_load_bitmap( "Resources/newspaceship.png" );
						spriteIndex[102] = al_load_bitmap( "Resources/basicenemy1.png" );
						spriteIndex[103] = al_load_bitmap( "Resources/basicenemy2.png" );
						spriteIndex[104] = al_load_bitmap( "Resources/basicenemy3.png" );
						spriteIndex[105] = al_load_bitmap( "Resources/enemysprinter.png" );
						spriteIndex[106] = al_load_bitmap( "Resources/blackpatch.png" );
						spriteIndex[107] = al_load_bitmap( "Resources/enemyexplosion.png" );


	al_register_event_source( event_queue1, al_get_timer_event_source( timer1 ) );
	al_register_event_source( event_queue1, al_get_keyboard_event_source() );

	al_play_sample( musicBGTheme, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0 );			/**< Plays the main theme. */

	srand(time( NULL ));

	/** Create the Player actor, and all required indices for game functions. */
	ActorPlayer						playerShip( ( SCREEN_WIDTH / 2 ), ( SCREEN_BOTTOMEDGE - 100.0 ), 1, 20, 101 );
	std::vector<ProjectileBullet>	friendlyBulletIndex;
	std::vector<ProjectileBullet>	hostileBulletIndex;
	std::vector<ActorEnemyBasic>	basicEnemyIndex;
	//vector<ActorEnemySprinter>	sprinterEnemyIndex;
	//vector<ActorEnemyBoss>		bossEnemyIndex;

    /** GAME MAIN LOOP */
    al_start_timer( timer1 );															/**< After starting the timer, the only thing that should be done is the game loop, and subsequent object cleanup. */
	while (!done)																		/**< This is the game loop, right here. */
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue1, &events);										/**< waits for something to happen */
		al_get_keyboard_state(&keyboardState1);											/**< IMPORTANT: gets the input from the keyboard */


		if (draw == true)																/**< Updates and draws all elements in the game space. */
		{
			if (al_key_down(&keyboardState1, ALLEGRO_KEY_ESCAPE))						/**< Pressing escape key ends the program. */
			{
				done = true;
			}
			
			/** 
			* Game over screen, stage designate -1.
			*/
			if (currStage == -1) {
				
				for (int i = 0; i < basicEnemyIndex.size(); i++) {
					basicEnemyIndex[i].isDead = true;
				}
				
				for (int i = 0; i < friendlyBulletIndex.size(); i++) {
					friendlyBulletIndex[i].projInactive = true;
				}

				for (int i = 0; i < hostileBulletIndex.size(); i++) {
					hostileBulletIndex[i].projInactive = true;
				}

				basicEnemyIndex.erase(std::remove_if(basicEnemyIndex.begin(), basicEnemyIndex.end(), enemyRemovePred), basicEnemyIndex.end());
				friendlyBulletIndex.erase(std::remove_if(friendlyBulletIndex.begin(), friendlyBulletIndex.end(), bulletRemovePred), friendlyBulletIndex.end());
				hostileBulletIndex.erase(std::remove_if(hostileBulletIndex.begin(), hostileBulletIndex.end(), bulletRemovePred), hostileBulletIndex.end());
				
				al_clear_to_color(backgroundColor);
				al_draw_text(font, textColor, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2 - 40), ALLEGRO_ALIGN_CENTRE, "You died!");
				al_draw_text(font, textColor, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), ALLEGRO_ALIGN_CENTRE, "Enter to return to menu.");
				al_draw_text(font, textColor, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2 + 40), ALLEGRO_ALIGN_CENTRE, "Esc to exit.");
				al_flip_display();

				if (al_key_down(&keyboardState1, ALLEGRO_KEY_ENTER)) {
					playerShip.SetLives(3);
					al_rest(0.5);
					currStage = 1;
					setupStage = true;
					loadingTimer = 0;
					menuY = 0;
					loadingGame = false;
				}
			}

			/**
			* Victory screen, stage designate 0.
			*/
			else if (currStage == 0) {
				
				for (int i = 0; i < hostileBulletIndex.size(); i++) {
					hostileBulletIndex[i].projInactive = true;
				}

				basicEnemyIndex.erase(std::remove_if(basicEnemyIndex.begin(), basicEnemyIndex.end(), enemyRemovePred), basicEnemyIndex.end());

				al_clear_to_color(backgroundColor);
				al_draw_text(font, textColor, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2 - 40), ALLEGRO_ALIGN_CENTRE, "You've won!");
				al_draw_text(font, textColor, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), ALLEGRO_ALIGN_CENTRE, "Enter to return to menu.");
				al_draw_text(font, textColor, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2 + 40), ALLEGRO_ALIGN_CENTRE, "Esc to exit.");
				al_flip_display();

				if (al_key_down(&keyboardState1, ALLEGRO_KEY_ENTER)) {
					playerShip.SetLives(3);
					al_rest(0.5);
					currStage = 1;
					setupStage = true;
					loadingTimer = 0;
					menuY = 0;
					loadingGame = false;
				}
			}

			/** Menu screen, stage designate 1. */
			else if (currStage == 1)
			{
				/** The following three conditional statements simply animate the menu screen, moving between two static images between update cycles. */
				if (blinking++ < 20) {
					al_draw_bitmap_region(spriteIndex[000], 0, menuY, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, NULL);
					al_flip_display();
					al_clear_to_color(backgroundColor);

				}

				else {
					al_draw_bitmap_region(spriteIndex[000], 1200, menuY, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, NULL);
					al_flip_display();
					al_clear_to_color(backgroundColor);
				}

				if (blinking > 40) {
					blinking = 0;
				}

				/** 
				* Once the player presses enter, we begin the "loading" screen. Full disclosure: nothing is loading. 
				* However, the delay allows a player to prepare to play the game, rather than commencing play in the same second they press enter.
				*/
				if (al_key_down(&keyboardState1, ALLEGRO_KEY_ENTER))
				{
					menuY = 800;
					loadingGame = true;
				}

				if (loadingGame == true) {
					loadingTimer++;
				}

				if (loadingTimer > 80) {
					currStage++;
				}

			}
			else
			{

				/** STAGE SET-UP */
				/** Stage Designate 2: Stage 1 */
				if (currStage == 2 && setupStage) {
					al_clear_to_color(backgroundColor);
					al_draw_text(font, textColor, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Stage 1");
					al_flip_display();
					al_rest(1.0);

					SpawnBasicRow(basicEnemyIndex, 50, 40, 1, 100, 102, true, 23, 19);
					SpawnBasicRow(basicEnemyIndex, 50, 90, 2, 200, 103, false, 23, 19);
					SpawnBasicRow(basicEnemyIndex, 50, 140, 3, 300, 104, true, 23, 19);
					setupStage = false;

				}

				/** Stage Designate 3: Stage 2 */
				if (currStage == 3 && setupStage) {
					al_clear_to_color(backgroundColor);
					al_draw_text(font, textColor, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Stage 2");
					al_flip_display();
					al_rest(1.0);

					SpawnBasicRow(basicEnemyIndex, 50, 40, 1, 100, 102, true, 23, 19);
					SpawnBasicRow(basicEnemyIndex, 50, 90, 2, 200, 103, false, 23, 19);
					SpawnBasicRow(basicEnemyIndex, 50, 140, 3, 300, 104, true, 23, 19);
					setupStage = false;
				}

				/** 
				* The stage is defeated when all basic enemies have been defeated, largely because the other non-boss enemy class
				* we had wanted to implement would run off the screen and destruct itself automatically well before the player cleared out
				* all of the basics.
				*/
				if (basicEnemyIndex.size() == 0 /*&& bossEnemyIndex.size() == 0*/) {
					
					for (int i = 0; i < friendlyBulletIndex.size(); i++) {
						friendlyBulletIndex[i].projInactive = true;
					}

					for (int i = 0; i < hostileBulletIndex.size(); i++) {
						hostileBulletIndex[i].projInactive = true;
					}

					friendlyBulletIndex.erase(std::remove_if(friendlyBulletIndex.begin(), friendlyBulletIndex.end(), bulletRemovePred), friendlyBulletIndex.end());
					hostileBulletIndex.erase(std::remove_if(hostileBulletIndex.begin(), hostileBulletIndex.end(), bulletRemovePred), hostileBulletIndex.end());

					playerShip.SetXCoord(SCREEN_WIDTH / 2);
					playerShip.SetYCoord(SCREEN_BOTTOMEDGE - 100.0);

					if (currStage == totalStages) {
						currStage = 0;
					}
					else {
						currStage++;
						setupStage = true;
					}
				}

				/** PREVIOUS UPDATE CLEANUP */

				/** Any enemy which has moved off the bottom of the screen is no longer interesting/useful and can be safely deleted. */
				for (int i = 1; i < basicEnemyIndex.size(); i++) {
					if (basicEnemyIndex[i].GetYCoord() > SCREEN_HEIGHT) {
						basicEnemyIndex[i].isDead = true;
					}
				}

				basicEnemyIndex.erase(std::remove_if(basicEnemyIndex.begin(), basicEnemyIndex.end(), enemyRemovePred), basicEnemyIndex.end());

				/** 
				* We only care if friendly bullets move off the top of the screen or hostile bullets move off the bottom. 
				* If friendly bullets are moving off the bottom or hostile bullets off the top, that's incorrect behaviour.
				*/
				for (int i = 0; i < friendlyBulletIndex.size(); ) {
					if (friendlyBulletIndex[i].GetYCoord() < SCREEN_TOPEDGE) {
						friendlyBulletIndex.erase((friendlyBulletIndex.begin() + i));
					}
					else {
						i++;
					}
				}

				for (int i = 0; i < hostileBulletIndex.size(); ) {
					if (hostileBulletIndex[i].GetYCoord() > SCREEN_HEIGHT) {
						hostileBulletIndex.erase((hostileBulletIndex.begin() + i));
					}
					else {
						i++;
					}
				}

				/** UPDATE PLAYER */

				/** Check if the player is dead, and also if the player has exhausted all their allotted lives. */
				if (playerShip.CheckDead()) {
					playerShip.KillPlayer(101, 600, 700);
				}

				if (playerShip.GetLives() < 0) {
					currStage = -1; /**< Changes to the game over screen. */
				}

				/** Get input and move the player accordingly. */
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

				/** Check if the player has flown into any of the enemy objects.*/
				for (int i = 0; i < basicEnemyIndex.size(); i++) {
					if (playerShip.actorHitbox.CheckForCollision(basicEnemyIndex[i].actorHitbox)) {
						playerShip.ModifyHealth(playerShip.GetHealth());
						playerShip.KillPlayer(101, 600, 700);

						basicEnemyIndex[i].isDead = true;
						basicEnemyIndex[i].ChangeActorSprite(107);
					}
				}

				/** Control firing of friendly bullets. */
				if (al_key_down(&keyboardState1, ALLEGRO_KEY_SPACE)) {
					if ( playerShip.bulletControlCounter >= 5) {
						al_play_sample(sfxShoot, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						SpawnBullet(friendlyBulletIndex, playerShip.GetXCoord(), playerShip.GetYCoord(), 1, 1);
						playerShip.bulletControlCounter = 0;
					}
					else {
						playerShip.bulletControlCounter++;
					}
				}
				else {
					playerShip.bulletControlCounter++;
				}

				/** UPDATE ENEMIES */

				/** Move all elements of each enemy index. */
				for (int i = 0; i < basicEnemyIndex.size(); i++) {
					basicEnemyIndex[i].MoveActor(MOVERATE_ACTORS, SCREEN_WIDTH);
				}

				/** Check to see if any of the enemy objects have collided with the player. */
				for (int i = 0; i < basicEnemyIndex.size(); i++) {
					if (playerShip.actorHitbox.CheckForCollision(basicEnemyIndex.at(i).actorHitbox) && !(basicEnemyIndex.at(i).isDead)) {
						playerShip.ModifyHealth(playerShip.GetHealth());
						playerShip.KillPlayer(101, 600, 700);

						basicEnemyIndex[i].isDead = true;
						basicEnemyIndex[i].ChangeActorSprite(107);
					}
				}

				/** Check to see if any enemy should fire a bullet, and if so, generate it. */
				/** One or no basic enemies will fire a bullet each update phase, depending on a certain percentile chance. */
				if (!(basicEnemyIndex.size() == 0)) {
					randomNumber = rand() % (basicEnemyIndex.size());
				}
				else {
					randomNumber = 0;
				}
				randomNumber2 = rand() % 100;
				if (randomNumber2 >= 99) {
					SpawnBullet(hostileBulletIndex, basicEnemyIndex[randomNumber].GetXCoord(), basicEnemyIndex[randomNumber].GetYCoord(), 1, 0);
				}

				/** UPDATE PROJECTILES */

				/** Move all bullets. */
				for (int i = 0; i < friendlyBulletIndex.size(); i++) {
					friendlyBulletIndex[i].MoveProjectile(MOVERATE_PROJECTILES);
				}
				for (int i = 0; i < hostileBulletIndex.size(); i++) {
					hostileBulletIndex[i].MoveProjectile(MOVERATE_PROJECTILES);
				}

				/** Check for collision between bullets and valid targets. */
				for (int i = 0; i < friendlyBulletIndex.size(); i++) {
					for (int j = 0; j < basicEnemyIndex.size(); j++) {
						if (friendlyBulletIndex[i].projectileHitbox.CheckForCollision(basicEnemyIndex.at(j).actorHitbox) && !(basicEnemyIndex.at(j).isDead)) {
							basicEnemyIndex[j].ModifyHealth(friendlyBulletIndex.at(i).GetBulletDamage());
							if (basicEnemyIndex[j].CheckDead()) {
								basicEnemyIndex[j].isDead = true;
								basicEnemyIndex[i].ChangeActorSprite(107);
							}

							friendlyBulletIndex.erase(friendlyBulletIndex.begin() + i);
						}
					}
				}

				for (int i = 0; i < hostileBulletIndex.size(); i++) {
					if (hostileBulletIndex[i].projectileHitbox.CheckForCollision(playerShip.actorHitbox)) {
						playerShip.ModifyHealth(hostileBulletIndex[i].GetBulletDamage());
						if (playerShip.CheckDead()) {
							playerShip.ChangeActorSprite(106);
						}

						hostileBulletIndex.erase(hostileBulletIndex.begin() + i);
					}
				}

				/** DRAW ALL OBJECTS */

				/** Draw the player. */
				al_draw_bitmap(spriteIndex[playerShip.GetSpriteKey()], playerShip.GetXCoord(), playerShip.GetYCoord(), NULL);

				/** Draw the enemies. */
				for (int i = 0; i < basicEnemyIndex.size(); i++) {
					//basicEnemyIndex[i].DrawActor();
					al_draw_bitmap(spriteIndex[basicEnemyIndex[i].GetSpriteKey()], basicEnemyIndex[i].GetXCoord(), basicEnemyIndex[i].GetYCoord(), NULL);
				}

				/** Draw the bullets. */
				for (int i = 0; i < friendlyBulletIndex.size(); i++) {
					friendlyBulletIndex[i].DrawProjectile();
				}
				for (int i = 0; i < hostileBulletIndex.size(); i++) {
					hostileBulletIndex[i].DrawProjectile();
				}

				al_flip_display(); /**< Updates the display. */
				al_clear_to_color(backgroundColor); /**< Clear the display to the bg color in preparation for the next draw. */
			}
		}
	}

	/** Clean up spriteIndex. */
	al_destroy_bitmap(spriteIndex[000]);
	al_destroy_bitmap(spriteIndex[101]);
	al_destroy_bitmap(spriteIndex[102]);
	al_destroy_bitmap(spriteIndex[103]);
	al_destroy_bitmap(spriteIndex[104]);
	al_destroy_bitmap(spriteIndex[105]);
	al_destroy_bitmap(spriteIndex[106]);
	al_destroy_bitmap(spriteIndex[107]);
	spriteIndex.erase(107);
	spriteIndex.erase(106);
	spriteIndex.erase(105);
	spriteIndex.erase(104);
	spriteIndex.erase(103);
	spriteIndex.erase(102);
	spriteIndex.erase(101);
	spriteIndex.erase(000);

	/** Clean up unwrapped allegro objects. */
    al_destroy_sample(sfxShoot);
    al_destroy_sample(sfxEnemyShoot);
    al_destroy_sample(musicBGTheme);
    al_destroy_timer(timer1);
    al_destroy_event_queue(event_queue1);

	/** End the program. */

    return 0;
}