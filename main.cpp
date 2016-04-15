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
#include "objectSpawners.h"

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
	const float     SCREEN_WIDTH = 1200.0, SCREEN_HEIGHT = 800.0;
	const float     SCREEN_LEFTEDGE = 0.0, SCREEN_RIGHTEDGE = SCREEN_WIDTH;
	const float     SCREEN_TOPEDGE = 0.0, SCREEN_BOTTOMEDGE = SCREEN_HEIGHT;
	const float FPS = 30.0; /**< Frames per second variable */
	bool done = false; /**< If done == true, the game ends. */
	bool draw = false; /**< If draw == true, the gamestate will be drawn to the display. */
	bool active = false; /**< Determines if a key is being pressed. */
	bool moveUp = false; bool moveDown = false; bool moveRight = false; bool moveLeft = false; /**< Passed to the player object to control movement.*/
	const int MOVERATE_PROJECTILES = 3; /**< if positive, the bullet goes down, if negative, it goes up */
	const int MOVERATE_ENEMY_PROJECTILES = 3; /**< if positive, the bullet goes down, if negative, it goes up */
	const int MOVERATE_ACTORS = 5;
	int randomNumber = rand() % 55; /**< generates random numbers between 0 and 55 */
	int randomNumber2;
	int animateEnemy = 0;
	int blinking = 0; /**< makes the main menu and the "loading" screen to blink */
	int menuY = 0;
	int enemyNumber = -1;
	bool loadingGame = false; /**< if false, then displays main menu, if true, the "loading" screen will be shown */
	int loadingTimer = 0; /**< sums amount of ftime that the "loading screen will be displayed */
	int leftOrRight = 3; /**< positive number means right, negative means left */
	int enemyMovement = 0;
	int gameSpeed = 10;
	int currStage = 1;
	bool setupStage = true;

	if (!al_init())   /**< do NOT initialice anything before al_init(); */
	{
		al_show_native_message_box(NULL, "Error", "Allegro Settings", "Failed to initialize allegro 5!", NULL, NULL);
		//return -1;
	}
	al_set_new_display_flags(ALLEGRO_NOFRAME); /**< Screen without frames */
	ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT); /**< Creates main display */
	if (!display)
	{
		al_show_native_message_box(display, "Error", "Display Settings", "Display window was unsuccessfull", NULL, NULL);
		//return -1; /**< error message in case display couldn't be created */
	}
	al_set_window_position(display, 100, 100);
	al_set_window_title(display, "2720's Project");

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
	ALLEGRO_COLOR electricBlue = al_map_rgb(118, 180, 255);
	ALLEGRO_COLOR electricYellow = al_map_rgb(255, 250, 44);
	ALLEGRO_COLOR electricRed = al_map_rgb(254, 1, 64);

	ALLEGRO_FONT *font = al_load_font("Resources/Custom Font.ttf", 36, NULL);
	ALLEGRO_KEYBOARD_STATE keyboardState1;
	ALLEGRO_SAMPLE *sfxShoot = al_load_sample("Resources/spaceship_shoot.wav"); /**< loads audio file */
	ALLEGRO_SAMPLE *sfxEnemyShoot = al_load_sample("Resources/enemy_shoot.wav"); /**< loads bullet firing sound file */
	ALLEGRO_SAMPLE *musicBGTheme = al_load_sample("Resources/Underclocked.wav"); /**< ALLEGRO_SAMPLE doesn't support mp3 or mid files */
																				 //ALLEGRO_SAMPLE *sfxMenuSelect = al_load_sample("Resources/file");
	al_reserve_samples(3); /**< indicate how many samples (songs) we are using */
	ALLEGRO_TIMER *timer1 = al_create_timer(1.0 / FPS); /**< 60 frames per second */
	ALLEGRO_EVENT_QUEUE *event_queue1 = al_create_event_queue();

	ALLEGRO_BITMAP *menu = al_load_bitmap("Resources/STARTMENU.png");
	ALLEGRO_BITMAP *playerSprite = al_load_bitmap("Resources/newspaceship.png");
	ALLEGRO_BITMAP *basicEnemySprite1 = al_load_bitmap("Resources/basicenemy1.png");
	ALLEGRO_BITMAP *basicEnemySprite2 = al_load_bitmap("Resources/basicenemy2.png");
	ALLEGRO_BITMAP *basicEnemySprite3 = al_load_bitmap("Resources/basicenemy3.png");
	ALLEGRO_BITMAP *sprinterEnemySprite = al_load_bitmap("Resources/enemysprinter.png");
	ALLEGRO_BITMAP *bulletSprite = al_load_bitmap("Resources/bullet.png");
	ALLEGRO_BITMAP *playerDeathSprite = al_load_bitmap("Resources/blackpatch.png");
	ALLEGRO_BITMAP *enemyDeathSprite = al_load_bitmap("Resources/enemyexplosion.png");

	al_register_event_source(event_queue1, al_get_timer_event_source(timer1));
	al_register_event_source(event_queue1, al_get_keyboard_event_source());

	/** @fn al_play_sample
	* @brief Starts playing the given audio
	* @param "musicBGTheme" is the ALLEGRO_SAMPLE variable wich includes the mp3 file
	* @param 1.0 is a float number corresponding the volume of the audio
	* @param 0.0 is a float number that shows from which side-speaker the audio should come out
	* @param 1.0 is the speed of the audio
	* @param ALLEGRO_PLAYMODE will decide the way the sound is played (once, loop, etc)
	*/
	al_play_sample(musicBGTheme, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0); /**< plays the main theme */

	srand(time(NULL));
	ActorPlayer playerShip((SCREEN_WIDTH / 2), (SCREEN_BOTTOMEDGE - 100.0), 1, 20, "Resources/newspaceship.png");
	std::vector<ProjectileBullet> friendlyBulletIndex;
	std::vector<ProjectileBullet> hostileBulletIndex;
	std::vector<ActorEnemyBasic> basicEnemyIndex;
	//vector<ActorEnemySprinter> sprinterEnemyIndex;
	//vector<ActorEnemyBoss> bossEnemyIndex;

    // GAME MAIN LOOP
    al_start_timer(timer1); /**< don't do anything nor initialize variables, NOTHING, after starting the timer */
	while (!done)  /**< the only thing that must be after the timer is the game loop (while) */
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue1, &events); /**< waits for something to happen */
		al_get_keyboard_state(&keyboardState1); /**< IMPORTANT: gets the imput from the keyboard */

			if (draw == false) // main menu
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
					al_draw_bitmap_region(menu, 0, menuY, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, NULL);
					al_flip_display();
					al_clear_to_color(backgroundColor); /**< cleans screen so it looks like moving */

				}
				else {
					al_draw_bitmap_region(menu, 1200, menuY, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, NULL);
					al_flip_display();
					al_clear_to_color(backgroundColor); /**< cleans screen so it looks like moving */
				}

				if (blinking > 40) {
					blinking = 0;
				}

				if (al_key_down(&keyboardState1, ALLEGRO_KEY_ENTER))  /**< pressing ENTER key */
				{
					menuY = 800;
					loadingGame = true;
				}

				if (loadingGame == true) { /**< stops displaying "main menu" and starts displaying "loading" */
					loadingTimer++;
				}

				if (loadingTimer > 80) { /**< miliseconds the LOADING screen will be displayed. */
					draw = true;
				}

			}
			else if (draw == true) /**< Updates and draws all elements on screen */
			{
				if (currStage = 1 && setupStage) {
					SpawnBasicRow(basicEnemyIndex, 50, 40, 1, 100, "Resources/basicenemy1.png", true, 5, 10);
					SpawnBasicRow(basicEnemyIndex, 50, 90, 2, 200, "Resources/basicenemy2.png", false, 5, 10);
					SpawnBasicRow(basicEnemyIndex, 50, 140, 3, 300, "Resources/basicenemy3.png", true, 5, 10);
					setupStage = false;
				}
				
				if (al_key_down(&keyboardState1, ALLEGRO_KEY_ESCAPE))  /**< pressing scape key ends the game */
				{
					done = true;
				}

				//############################################### PREVIOUS UPDATE CLEANUP ##################
				for (int i = 0; i < basicEnemyIndex.size(); i++) {
					if (basicEnemyIndex.at(i).isDead) {
						basicEnemyIndex.erase((basicEnemyIndex.begin() + (i)));
					}
					if (basicEnemyIndex.at(i).GetXCoord() > SCREEN_HEIGHT) {
						basicEnemyIndex.erase((basicEnemyIndex.begin() + (i)));
					}
				}

				for (int i = 0; i < friendlyBulletIndex.size(); i++) {
					if (friendlyBulletIndex.at(i).GetYCoord() < SCREEN_TOPEDGE) {
						friendlyBulletIndex.erase((friendlyBulletIndex.begin() + i));
					}
				}

				for (int i = 0; i < hostileBulletIndex.size(); i++) {
					if (hostileBulletIndex[i].GetYCoord() > SCREEN_HEIGHT) {
						hostileBulletIndex.erase((hostileBulletIndex.begin() + 1));
					}
				}

				//############################################### UPDATE PLAYER ############################

				//Check if the player is dead, and also if the player has exhausted all their allotted lives.
				if (playerShip.CheckDead()) {
					playerShip.KillPlayer("Resources/blackpatch.png", 40, 50, 600, 700);
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
						playerShip.KillPlayer("Resources/blackpatch.png", 40, 50, 600, 700);

						basicEnemyIndex.at(i).isDead = true;
						basicEnemyIndex.at(i).ChangeActorSprite("Resources/enemyexplosion.png");
					}
				}

				//Control firing of friendly bullets.
				if (al_key_down(&keyboardState1, ALLEGRO_KEY_SPACE)) {
					if (!(friendlyBulletIndex.size() == playerShip.GetMaxBullets()) /*&& playerShip.bulletControlCounter == 5*/) {
						al_play_sample(sfxShoot, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						SpawnBullet(friendlyBulletIndex, playerShip.GetXCoord(), playerShip.GetYCoord(), 1, 1, "Resources/bullet.png");
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
					basicEnemyIndex.at(i).MoveActor(MOVERATE_ACTORS, SCREEN_WIDTH);
				}

				//Check to see if any of the enemy objects have collided with the player.
				for (int i = 0; i < basicEnemyIndex.size(); i++) {
					if (playerShip.actorHitbox.CheckForCollision(basicEnemyIndex.at(i).actorHitbox) && !(basicEnemyIndex.at(i).isDead)) {
						playerShip.ModifyHealth(playerShip.GetHealth());
						playerShip.KillPlayer("Resources/blackpatch.png", 40, 50, 600, 700);

						basicEnemyIndex.at(i).isDead = true;
						basicEnemyIndex.at(i).ChangeActorSprite("Resources/enemyexplosion.png");
					}
				}

				//Check to see if any enemy should fire a bullet, and if so, generate it.
				//One or no basic enemies will fire a bullet each update phase, depending on a certain percentile chance.
				randomNumber = rand() % basicEnemyIndex.size();
				randomNumber2 = rand() % 100;
				if (randomNumber2 >= 80) {
					//hostileBulletIndex.emplace_back(basicEnemyIndex.at(randomNumber).GetXCoord, basicEnemyIndex.at(randomNumber).GetYCoord, DOWN);
					/* TODO: Completely rewrite the stuff related with "emplace_back" */
				}

				//####################### UPDATE PROJECTILES ###############################

				//Move all bullets.
				for (int i = 0; i < friendlyBulletIndex.size(); i++) {
					friendlyBulletIndex.at(i).MoveProjectile(MOVERATE_PROJECTILES); //TODO: Take an integer value and convert it inside the method
				}
				for (int i = 0; i < hostileBulletIndex.size(); i++) {
					hostileBulletIndex.at(i).MoveProjectile(MOVERATE_PROJECTILES); //TODO: Take an integer value and convert it inside the method
				}

				for (int i = 0; i < friendlyBulletIndex.size(); i++) {
					for (int j = 0; j < basicEnemyIndex.size(); j++) {
						if (friendlyBulletIndex.at(i).projectileHitbox.CheckForCollision(basicEnemyIndex.at(j).actorHitbox) && !(basicEnemyIndex.at(j).isDead)) {
							basicEnemyIndex.at(j).ModifyHealth(friendlyBulletIndex.at(i).GetBulletDamage());
							if (basicEnemyIndex.at(j).CheckDead()) {
								basicEnemyIndex.at(j).isDead = true;
								basicEnemyIndex.at(i).ChangeActorSprite("Resources/blackpatch.png");
							}

							friendlyBulletIndex.erase(friendlyBulletIndex.begin() + i);
						}
					}
				}

				for (int i = 0; i < hostileBulletIndex.size(); i++) {
					if (hostileBulletIndex.at(i).projectileHitbox.CheckForCollision(playerShip.actorHitbox)) {
						playerShip.ModifyHealth(hostileBulletIndex.at(i).GetBulletDamage());
						if (playerShip.CheckDead()) {
							playerShip.ChangeActorSprite("Resources/blackpatch.png");
						}

						hostileBulletIndex.erase(hostileBulletIndex.begin() + i);
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
				for (int i = 0; i < hostileBulletIndex.size(); i++) {
					hostileBulletIndex.at(i).DrawProjectile();
				}
				al_flip_display();
				al_clear_to_color(backgroundColor);
			}
		}

	al_destroy_bitmap(menu);
	al_destroy_bitmap(playerSprite);
	al_destroy_bitmap(basicEnemySprite1);
	al_destroy_bitmap(basicEnemySprite2);
	al_destroy_bitmap(basicEnemySprite3);
	al_destroy_bitmap(sprinterEnemySprite);
	al_destroy_bitmap(bulletSprite);
	al_destroy_bitmap(playerDeathSprite);
	al_destroy_bitmap(enemyDeathSprite);
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
