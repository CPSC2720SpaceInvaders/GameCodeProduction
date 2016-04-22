/**
* @file		main.cpp
*
* @brief	Initialization of the display and the protagonist.
*			C++ Allegro game for CPSC 2720 project:
*			"Space Invaders -like- game"
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

bool enemyRemovePred( const ActorEnemyBasic target) {
	if (target.isDead) {
		return true;
	}
	else {
		return false;
	}
}

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
	const float			SCREEN_WIDTH = 1200.0, SCREEN_HEIGHT = 800.0;
	const float			SCREEN_LEFTEDGE = 0.0, SCREEN_RIGHTEDGE = SCREEN_WIDTH;
	const float			SCREEN_TOPEDGE = 0.0, SCREEN_BOTTOMEDGE = SCREEN_HEIGHT;
	const float			FPS = 60.0;														/**< Frames per second variable */
	bool				done = false;													/**< If done == true, the game ends. */
	bool				draw = true;													/**< If draw == true, the gamestate will be drawn to the display. */
	bool				active = false;													/**< Determines if a key is being pressed. */
	bool				moveUp = false; bool moveDown = false; 
	bool				moveRight = false; bool moveLeft = false;						/**< Passed to the player object to control movement.*/
	const int			MOVERATE_PROJECTILES = 5;										/**< if positive, the bullet goes down, if negative, it goes up */
	const int			MOVERATE_ENEMY_PROJECTILES = 3;									/**< if positive, the bullet goes down, if negative, it goes up */
	const int			MOVERATE_ACTORS = 5;
	int					randomNumber = rand() % 55;										/**< generates random numbers between 0 and 55 */
	int					randomNumber2;
	int					animateEnemy = 0;
	int					blinking = 0;													/**< makes the main menu and the "loading" screen to blink */
	int					menuY = 0;
	int					enemyNumber = -1;
	int					totalStages = 3;
	bool				loadingGame = false;											/**< if false, then displays main menu, if true, the "loading" screen will be shown */
	int					loadingTimer = 0;												/**< sums amount of ftime that the "loading screen will be displayed */
	int					leftOrRight = 3;												/**< positive number means right, negative means left */
	int					enemyMovement = 0;
	int					gameSpeed = 10;
	int					currStage = 1;
	bool				setupStage = true;

	ALLEGRO_DISPLAY		*display = NULL;

	if ( !al_init() )																	/**< do NOT initialice anything before al_init(); */
	{
		al_show_native_message_box( NULL, "Error", "Allegro Settings", "Failed to initialize allegro 5!", NULL, NULL );
		//return -1;
	}
	
	al_set_new_display_flags(ALLEGRO_WINDOWED);											/**< Screen without frames */
						display = al_create_display( SCREEN_WIDTH, SCREEN_HEIGHT );
	
	if ( !display )
	{
		al_show_native_message_box( display, "Error", "Display Settings", "Display window was unsuccessfull", NULL, NULL );
		//return -1; /**< error message in case display couldn't be created */
	}
	al_set_window_position( display, 0, 0 );
	al_set_window_title( display, "2720 Project" );

	//Initialize universal allegro aspects required for the game
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();															/**< intializes primitives to draw figures */
	al_install_audio();																	/**< intializes the hability play audio */
	al_init_acodec_addon();
	al_init_image_addon();
	al_install_keyboard();																/**< intializes the hability to recieve commands from keyboard */

						   // ALLEGRO_COLOR NEEDS TO BE USED AFTER INITIALZE THE PRIMITIVES_ADDON
	ALLEGRO_COLOR		backgroundColor = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR		textColor = al_map_rgb(254, 1, 64);
	ALLEGRO_COLOR		titleColor = al_map_rgb(118, 180, 255);
	ALLEGRO_COLOR		electricBlue = al_map_rgb(118, 180, 255);
	ALLEGRO_COLOR		electricYellow = al_map_rgb(255, 250, 44);
	ALLEGRO_COLOR		electricRed = al_map_rgb(254, 1, 64);

	ALLEGRO_FONT		*font = al_load_font("Resources/Ubuntu-regular.ttf", 36, NULL);
	ALLEGRO_KEYBOARD_STATE	keyboardState1;
	ALLEGRO_SAMPLE		*sfxShoot = al_load_sample("Resources/spaceship_shoot.wav");	/**< loads audio file */
	ALLEGRO_SAMPLE		*sfxEnemyShoot = al_load_sample("Resources/enemy_shoot.wav");	/**< loads bullet firing sound file */
	ALLEGRO_SAMPLE		*musicBGTheme = al_load_sample("Resources/Underclocked.wav");	/**< ALLEGRO_SAMPLE doesn't support mp3 or mid files */
	al_reserve_samples( 3 );															/**< indicate how many samples (songs) we are using */
	ALLEGRO_TIMER		*timer1 = al_create_timer(1.0 / FPS); 
	ALLEGRO_EVENT_QUEUE *event_queue1 = al_create_event_queue();

	//Syntax for spriteIndex keys:
	//x yz
	//x:	0: abstract object, for instance buttons or menu elements;
	//		1: actor sprites, for instance the player's ship
	//		2+: misc indices, unlikely to be used
	//yz:	order of loading. For instance, 000 is the first menu object loaded.
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

	/** @fn al_play_sample
	* @brief Starts playing the given audio
	* @param "musicBGTheme" is the ALLEGRO_SAMPLE variable wich includes the mp3 file
	* @param 1.0 is a float number corresponding the volume of the audio
	* @param 0.0 is a float number that shows from which side-speaker the audio should come out
	* @param 1.0 is the speed of the audio
	* @param ALLEGRO_PLAYMODE will decide the way the sound is played (once, loop, etc)
	*/
	al_play_sample( musicBGTheme, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0 );		/**< plays the main theme */

	srand(time( NULL ));
	ActorPlayer			playerShip( ( SCREEN_WIDTH / 2 ), ( SCREEN_BOTTOMEDGE - 100.0 ), 1, 20, 101 );
	std::vector<ProjectileBullet>	friendlyBulletIndex;
	std::vector<ProjectileBullet>	hostileBulletIndex;
	std::vector<ActorEnemyBasic>	basicEnemyIndex;
	//vector<ActorEnemySprinter>	sprinterEnemyIndex;
	//vector<ActorEnemyBoss>		bossEnemyIndex;

    // GAME MAIN LOOP
    al_start_timer( timer1 );														/**< don't do anything nor initialize variables, NOTHING, after starting the timer */
	while (!done)																	/**< the only thing that must be after the timer is the game loop (while) */
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue1, &events);									/**< waits for something to happen */
		al_get_keyboard_state(&keyboardState1);									/**< IMPORTANT: gets the imput from the keyboard */


		if (draw == true)													/**< Updates and draws all elements on screen */
		{
			if (al_key_down(&keyboardState1, ALLEGRO_KEY_ESCAPE))				/**< pressing escape key ends the game */
			{
				done = true;
			}
			
			if (currStage == -1) {
				al_clear_to_color(backgroundColor);
				al_draw_text(font, textColor, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2 - 40), ALLEGRO_ALIGN_CENTRE, "You died!");
				al_draw_text(font, textColor, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), ALLEGRO_ALIGN_CENTRE, "Enter to return to menu.");
				al_draw_text(font, textColor, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2 + 40), ALLEGRO_ALIGN_CENTRE, "Esc to exit.");
				al_flip_display();

				if (al_key_down(&keyboardState1, ALLEGRO_KEY_ENTER)) {
					al_rest(0.5);
					currStage = 1;
					setupStage = true;
					loadingTimer = 0;
					menuY = 0;
					loadingGame = false;
				}
			}

			else if (currStage == 0) {
				al_clear_to_color(backgroundColor);
				al_draw_text(font, textColor, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2 - 40), ALLEGRO_ALIGN_CENTRE, "You've won!");
				al_draw_text(font, textColor, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), ALLEGRO_ALIGN_CENTRE, "Enter to return to menu.");
				al_draw_text(font, textColor, (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2 + 40), ALLEGRO_ALIGN_CENTRE, "Esc to exit.");
				al_flip_display();

				if (al_key_down(&keyboardState1, ALLEGRO_KEY_ENTER)) {
					al_rest(0.5);
					currStage = 1;
					setupStage = true;
					loadingTimer = 0;
					menuY = 0;
					loadingGame = false;
				}
			}

			else if (currStage == 1) /**< Menu handling. */
			{
				if (blinking++ < 20) {
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
					al_draw_bitmap_region(spriteIndex[000], 0, menuY, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, NULL);
					al_flip_display();
					al_clear_to_color(backgroundColor);								/**< cleans screen so it looks like moving */

				}
				else {
					al_draw_bitmap_region(spriteIndex[000], 1200, menuY, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, NULL);
					al_flip_display();
					al_clear_to_color(backgroundColor);								/**< cleans screen so it looks like moving */
				}

				if (blinking > 40) {
					blinking = 0;
				}

				if (al_key_down(&keyboardState1, ALLEGRO_KEY_ENTER))				/**< pressing ENTER key */
				{
					menuY = 800;
					loadingGame = true;
				}

				if (loadingGame == true) {											/**< stops displaying "main menu" and starts displaying "loading" */
					loadingTimer++;
				}

				if (loadingTimer > 80) {												/**< miliseconds the LOADING screen will be displayed. */
					currStage++;
				}

			}
			else
			{

				//############################################### STAGE SPAWNING ###########################
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

				//############################################### PREVIOUS UPDATE CLEANUP ##################


				for (int i = 1; i < basicEnemyIndex.size(); i++) {
					if (basicEnemyIndex[i].GetYCoord() > SCREEN_HEIGHT) {
						basicEnemyIndex[i].isDead = true;
					}
				}

				basicEnemyIndex.erase(std::remove_if(basicEnemyIndex.begin(), basicEnemyIndex.end(), enemyRemovePred), basicEnemyIndex.end());


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

				//############################################### UPDATE PLAYER ############################

				//Check if the player is dead, and also if the player has exhausted all their allotted lives.
				if (playerShip.CheckDead()) {
					playerShip.KillPlayer(101, 40, 50, 600, 700);
				}

				if (playerShip.GetLives() < 0) {
					currStage = -1; /**< Changes to the game over screen. */
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
					if (playerShip.actorHitbox.CheckForCollision(basicEnemyIndex[i].actorHitbox)) {
						playerShip.ModifyHealth(playerShip.GetHealth());
						playerShip.KillPlayer(101, 40, 50, 600, 700);

						basicEnemyIndex[i].isDead = true;
						basicEnemyIndex[i].ChangeActorSprite(107);
					}
				}

				//Control firing of friendly bullets.
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

				//############################################### UPDATE ENEMIES ############################

				//Move all elements of each enemy index.
				for (int i = 0; i < basicEnemyIndex.size(); i++) {
					basicEnemyIndex[i].MoveActor(MOVERATE_ACTORS, SCREEN_WIDTH);
				}

				//Check to see if any of the enemy objects have collided with the player.
				for (int i = 0; i < basicEnemyIndex.size(); i++) {
					if (playerShip.actorHitbox.CheckForCollision(basicEnemyIndex.at(i).actorHitbox) && !(basicEnemyIndex.at(i).isDead)) {
						playerShip.ModifyHealth(playerShip.GetHealth());
						playerShip.KillPlayer(101, 40, 50, 600, 700);

						basicEnemyIndex[i].isDead = true;
						basicEnemyIndex[i].ChangeActorSprite(107);
					}
				}

				//Check to see if any enemy should fire a bullet, and if so, generate it.
				//One or no basic enemies will fire a bullet each update phase, depending on a certain percentile chance.
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

				//####################### UPDATE PROJECTILES ###############################

				//Move all bullets.
				for (int i = 0; i < friendlyBulletIndex.size(); i++) {
					friendlyBulletIndex[i].MoveProjectile(MOVERATE_PROJECTILES);
				}
				for (int i = 0; i < hostileBulletIndex.size(); i++) {
					hostileBulletIndex[i].MoveProjectile(MOVERATE_PROJECTILES);
				}

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

				//####################### DRAW ALL OBJECTS #################################

				//playerShip.DrawActor();
				al_draw_bitmap(spriteIndex[playerShip.GetSpriteKey()], playerShip.GetXCoord(), playerShip.GetYCoord(), NULL);

				for (int i = 0; i < basicEnemyIndex.size(); i++) {
					//basicEnemyIndex[i].DrawActor();
					al_draw_bitmap(spriteIndex[basicEnemyIndex[i].GetSpriteKey()], basicEnemyIndex[i].GetXCoord(), basicEnemyIndex[i].GetYCoord(), NULL);
				}
				for (int i = 0; i < friendlyBulletIndex.size(); i++) {
					friendlyBulletIndex[i].DrawProjectile();
				}
				for (int i = 0; i < hostileBulletIndex.size(); i++) {
					hostileBulletIndex[i].DrawProjectile();
				}
				al_flip_display();
				al_clear_to_color(backgroundColor);
			}
		}
	}

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

    al_destroy_sample(sfxShoot);
    al_destroy_sample(sfxEnemyShoot);
    al_destroy_sample(musicBGTheme);
    al_destroy_timer(timer1);
    al_destroy_event_queue(event_queue1);
    return 0;
}
