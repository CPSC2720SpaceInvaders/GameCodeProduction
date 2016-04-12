#ifndef COMPONENTS_H_INCLUDED
#define COMPONENTS_H_INCLUDED

    const float     SCREEN_WIDTH = 1200.0, SCREEN_HEIGHT = 800.0;
    const float     SCREEN_LEFTEDGE = 0.0, SCREEN_RIGHTEDGE = SCREEN_WIDTH;
    const float     SCREEN_TOPEDGE = 0.0, SCREEN_BOTTOMEDGE = SCREEN_HEIGHT;
    const float FPS = 60.0; /**< Frames per second variable */
    bool done = false; /**< If done == true, the game ends. */
    bool draw = false; /**< If draw == true, the gamestate will be drawn to the display. */
    bool active = false; /**< Determines if a key is being pressed. */
	bool moveUp = false; bool moveDown = false; bool moveRight = false; bool moveLeft = false; /**< Passed to the player object to control movement.*/
    const int MOVERATE_PROJECTILES = -5; /**< if positive, the bullet goes down, if negative, it goes up */
    const int MOVERATE_ENEMY_PROJECTILES = 3; /**< if positive, the bullet goes down, if negative, it goes up */
    const int MOVERATE_ACTORS = 10;
    srand(time(NULL));
    int randomNumber = rand()%55; /**< generates random numbers between 0 and 55 */
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

    if(!al_init())   /**< do NOT initialice anything before al_init(); */
    {
        al_show_native_message_box(NULL, "Error", "Allegro Settings", "Failed to initialize allegro 5!", NULL, NULL);
        //return -1;
    }
    al_set_new_display_flags(ALLEGRO_NOFRAME); /**< Screen without frames */
    ALLEGRO_DISPLAY *display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT); /**< Creates main display */
    if(!display)
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
    ALLEGRO_COLOR electricBlue = al_map_rgb(118,180,255);
    ALLEGRO_COLOR electricYellow = al_map_rgb(255,250,44);
    ALLEGRO_COLOR electricRed = al_map_rgb(254,1,64);

    ALLEGRO_FONT *font = al_load_font("Resources/Custom Font.ttf", 36, NULL);
    ALLEGRO_KEYBOARD_STATE keyboardState1;
    ALLEGRO_SAMPLE *sfxShoot = al_load_sample("Resources/spaceship_shoot.wav"); /**< loads audio file */
    ALLEGRO_SAMPLE *sfxEnemyShoot = al_load_sample("Resources/enemy_shoot.wav"); /**< loads bullet firing sound file */
    ALLEGRO_SAMPLE *musicBGTheme = al_load_sample("Resources/Underclocked.wav"); /**< ALLEGRO_SAMPLE doesn't support mp3 or mid files */
    //ALLEGRO_SAMPLE *sfxMenuSelect = al_load_sample("Resources/file");
    al_reserve_samples(3); /**< indicate how many samples (songs) we are using */
    ALLEGRO_TIMER *timer1 = al_create_timer(1.0/FPS); /**< 60 frames per second */
    ALLEGRO_EVENT_QUEUE *event_queue1 = al_create_event_queue();
    ALLEGRO_BITMAP *menu = al_load_bitmap("Resources/STARTMENU.png");
	ALLEGRO_BITMAP *playerSprite = al_load_bitmap("Resources/spaceship.png");
	ALLEGRO_BITMAP *enemySprites = al_load_bitmap("Resources/enemies.png");
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


#endif // INICIA_H_INCLUDED
