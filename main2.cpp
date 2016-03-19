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
#include "actor.h"
#include "actorPlayer.h"
#include "actorEnemy.h"
#include "projectile.h"
#include "bullet.h"

/**
* @file main2.cpp
* @brief Initialization of the display and the protagonist.
* C++ Allegro game for CPSC 2720 project:
* "Space Invaders -like- game"
* Credits to Erick Skiff for the music: http://ericskiff.com/music
* @author Adad, Bertram, Jiaying & Okingo.
* @bug No known bugs.
*/

int main() {
	const float		SCREEN_WIDTH = 800.0, SCREEN_HEIGHT = 800.0;
	const float		SCREEN_LEFTEDGE = 0.0, SCREEN_RIGHTEDGE = SCREEN_WIDTH; 
	const float		SCREEN_TOPEDGE = 0.0, SCREEN_BOTTOMEDGE = SCREEN_HEIGHT;
	const float FPS = 60.0;
	bool done = false; /**< If done == true, the game ends. */
	bool draw = false; /**< If draw == true, the gamestate will be drawn to the display. */
	bool active = false; /**< Determines if a key is being pressed. */
	const int MOVERATE_PROJECTILES = 10;
	const int MOVERATE_ACTORS = 10;

	enum			controlDirection_t { UP, DOWN, LEFT, RIGHT };
	ALLEGRO_COLOR backgroundColor = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR textColor = al_map_rgb(254, 1, 64);
	ALLEGRO_COLOR titleColor = al_map_rgb(118, 180, 255);

	std::vector<Actor> playerIndex;
	std::vector<Actor> enemyIndex;
	std::vector<ProjectileBullet> bulletIndexFriendly;
	std::vector<ProjectileBullet> bulletIndexHostile;
	//std::list<powerups> powerupIndex /** Create an index for each powerup type we choose to use.
	
	if (!al_init()) {
		al_show_native_message_box(NULL, "Error", NULL, "Failed to initialize Allegro 5!", NULL, NULL);
		return -1;
	}

	al_set_new_display_flags(ALLEGRO_NOFRAME); /**< Screen without frames. */
	ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display) {
		al_show_native_message_box(display, "Error", "Display Settings", "Display window was unsuccessful.", NULL, NULL);
		return -1; /**< Error message in case display couldn't be created. */
	}
	al_set_window_position(display, 100, 100);
	al_set_window_title(display, "2720 Term Project");

	//Initialize universal allegro aspects.
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	al_install_mouse(); /**< initializes the use of the cursor */

	//Initialize universal sounds
	ALLEGRO_SAMPLE *sfxShoot = al_load_sample("Resources/spaceship_shoot.wav"); /**< loads bullet firing sound file */
	//ALLEGRO_SAMPLE *sfxMenuSelect = al_load_sample("Resources/file"); /**<
	ALLEGRO_SAMPLE *musicBGTheme = al_load_sample("Resources/Underclocked.wav"); /**< loads background music file */

	//Initialize keyboard state for player input
	ALLEGRO_KEYBOARD_STATE playerInput;

	ALLEGRO_TIMER *gameLoopTimer = al_create_timer(1.0/FPS);
	ALLEGRO_EVENT_QUEUE *eventQueue = al_create_event_queue();

	al_register_event_source(eventQueue, al_get_timer_event_source(gameLoopTimer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	
	//ALLEGRO_BITMAP *cursor = al_load_bitmap("Resources/cursor.png"); /**< Loads cursor image for menu. */
	
      	//menu display goes here, prior to gamestate
	/* MENU




        */

	/* STAGE 1 FILE LOADING */
	/* Use as template for constructing future stages. */

	//*musicBGTheme = al_load_sample("Resources/file");
	ALLEGRO_BITMAP *spritePlayer = al_load_bitmap("Resources/spaceship_large.png"); /**< loads player sprite */
	ALLEGRO_BITMAP *spriteEnemy = al_load_bitmap("Resources/enemy1.png");
	al_convert_mask_to_alpha(player, al_map_rgb(255, 0, 255));
	if(!player){
	   al_show_native_message_box(display, "Message Title", "Bitmap Settings", "Could not load Player image.", NULL, NULL);
	}

	//Construct player and enemy objects at given locations.
	Actor playerShip (400, 760, 1, 1, *spritePlayer);
	Actor enemyShip (400, 40, 1, 1, *spriteEnemy);

	/*Construct lists of players and enemies. Due to each enemy needing
	  a unique initial coordinate, this must be done manually for each
	  enemy object, unless someone can come up with a handy way
	  to assign things to the index (we could define a formula
	  for each stage in order to place enemies, and then use Emplace?). */
	playerIndex.push_back(playerShip);
	enemyIndex.push_back(enemyShip);
	
	al_start_timer(gameLoopTimer);
	while(!done){
}
