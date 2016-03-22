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

//#define ScreenWidth 800
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

const int maxBullets = 5;
const int ScreenWidth = 800;
const int ScreenHeight = 800;
const int moveSpeed = 10;

struct Bullets{
    float bulletX, bulletY;
    float destinyX, destinyY;

}BulletsArray[maxBullets];

/*void drawBullet(float destinyX, float destinyY){
    al_draw_line(bulletX, bulletY, bulletX, bulletY+10, al_map_rgb(255,255,255), 5.0);
}*/

void drawBullet(float bulletX, float bulletY){
    al_draw_line(bulletX, bulletY, bulletX, bulletY+10, al_map_rgb(255,255,255), 5.0);
}

struct ACTOR{
    float playerX=ScreenWidth/2, playerY=ScreenHeight-100.0; /**< represent the original position of the spaceship */
    float playerWidth=60.0, playerHeight=40.0;
    int currBullets = 0;

}player2;

void drawSpaceship(ALLEGRO_BITMAP *player, struct ACTOR player2){
    al_draw_bitmap_region(player, 0, 0, player2.playerWidth, player2.playerHeight, player2.playerX, player2.playerY, NULL);
}



bool Collision(float playerX, float playerY, float enemyX, float enemyY, int playerWidth, int playerHeight, int enemyWidth, int enemyHeight){
  // enemy is     50 * 40 px
  // spaceship is 60 * 40 px
  if (player2.playerX+playerWidth < enemyX || player2.playerX>enemyX+enemyWidth || player2.playerY+playerHeight<enemyY || player2.playerY>enemyY+enemyHeight){
    return false; /**< There is no collision! */
  } else {
    return true; // There is collision
  }
}



int main(){
	if(!al_init()) { /**< do NOT initialice anything before al_init(); */
      al_show_native_message_box(NULL, "Error", "Allegro Settings", "Failed to initialize allegro 5!", NULL, NULL);
      return -1;
   }
   al_set_new_display_flags(ALLEGRO_NOFRAME); /**< Screen without frames */
   ALLEGRO_DISPLAY *display = al_create_display(ScreenWidth, ScreenHeight); /**< Creates main display */
   if(!display) {
      al_show_native_message_box(display, "Error", "Display Settings", "Display window was unsuccessfull", NULL, NULL);
      return -1; /**< error message in case display couldn't be created */
   }
   al_set_window_position(display, 100, 100);
   al_set_window_title(display, "2720's Project");

   //######################### HERE FINISHES THE INITIALIZATION OF THE DISPLAY ###########################

   enum Direction1 { UP, DOWN, LEFT, RIGHT };

   al_init_font_addon(); /**< intializes fonts so we can write on the display */
   al_init_ttf_addon();
   ALLEGRO_FONT *font = al_load_font("Resources/Custom Font.ttf", 36, NULL);

   al_init_primitives_addon();  /**< intializes primitives to draw figures */
   ALLEGRO_COLOR electricBlue = al_map_rgb(118,180,255);
   ALLEGRO_COLOR electricYellow = al_map_rgb(255,250,44);
   ALLEGRO_COLOR electricRed = al_map_rgb(254,1,64);
   ALLEGRO_COLOR playerColor = electricBlue; /**< original color of the circle */

   al_install_keyboard(); /**< intializes the hability to recieve commands from keyboard */
   ALLEGRO_KEYBOARD_STATE keyboardState1;

   al_install_audio(); /**< intializes the hability play audio */
   al_init_acodec_addon();
   ALLEGRO_SAMPLE *spaceship_shoot = al_load_sample("Resources/spaceship_shoot.wav"); /**< loads audio file */
   ALLEGRO_SAMPLE *main_song = al_load_sample("Resources/Underclocked.wav"); /**< ALLEGRO_SAMPLE doesn't support mp3 or mid files */
   al_reserve_samples(2); /**< indicate how many samples (songs) we are using */
   al_play_sample(main_song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0); /**< plays the main theme */

   bool done=false; /**< if it is true, the game ends */
   bool draw=false; /**< if it is true, the items will continue being drawed on the display */
   bool active=false; /**< makes sure a key is being pressed */
   int playerWidth = 60;
   int playerHeight = 40; /**< represent the width and height of the spaceship inside the PNG file */
   float enemyX = 10.0;
   float enemyY = 100.0;
   int enemyWidth = 60;
   int enemyHeight = 40; /**< represent the width and height of the spaceship inside the PNG file */
   int enemyMaxHealth = 1;
   int leftright = 1; //left = 0, right = 1
   bool CanPlayerShoot = true;
   int BulletControlCounter = 0;

   /**
    * @class classEnemy
    * @brief All stuff related to the alien
    * @author Victor Adad.
    */
   class classEnemy{
        public:
        int enemyX = 10;
        int enemyY = 100;
        int enemyMaxHealth = 1;
        ALLEGRO_BITMAP *enemy;
        int enemieWidth, enemieHeight;    //width and height of character
        int animation;
        void initialize_enemy(int _ememyX, int _enemyY, int _life);

        int moveEnemy(int enemyX, int enemyY);
    };

   const float fps = 60.0; /**< frames per second variable */
   ALLEGRO_TIMER *timer1 = al_create_timer(1.0/fps); /**< 60 frames per second */
   ALLEGRO_EVENT_QUEUE *event_queue1 = al_create_event_queue();
   al_register_event_source(event_queue1, al_get_timer_event_source(timer1));
   al_register_event_source(event_queue1, al_get_keyboard_event_source());
   al_register_event_source(event_queue1, al_get_display_event_source(display));

   al_install_mouse(); /**< initializes the use of the cursor */
   al_register_event_source(event_queue1, al_get_mouse_event_source());

   al_init_image_addon();
   ALLEGRO_BITMAP *player = al_load_bitmap("Resources/spaceship_large.png"); /**< loads player sprite */
   ALLEGRO_BITMAP *enemy1 = al_load_bitmap("Resources/enemy1.png");
   al_convert_mask_to_alpha(player, al_map_rgb(255,0,255));
   if(!player){
        al_show_native_message_box(display, "Message Title", "Bitmap Settings", "Could not load Player", NULL, NULL);
   }

   al_start_timer(timer1); /**< don't do anything nor initialize variables, NOTHING, after starting the timer */
   while(!done){ /**< the only thing that must be after the timer is the game loop (while) */
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue1, &events); /**< waits for something to happen */

        if(draw == false){ /**< shows HOME SCREEN and detects mouse clic, so the game starts */
            al_draw_text(font, playerColor, (ScreenWidth/2)+2, ScreenHeight/2, ALLEGRO_ALIGN_CENTRE, "PRESS START");
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0)); /**< cleans screen so it looks like moving */

            while (draw == false){
                al_get_keyboard_state(&keyboardState1); /**< gets the imput from the keyboard */
                if(al_key_down(&keyboardState1, ALLEGRO_KEY_ENTER)){ /**< pressing ENTER key */
                    playerColor = electricYellow;
                    al_draw_text(font, playerColor, (ScreenWidth/2)+2, ScreenHeight/2, ALLEGRO_ALIGN_CENTRE, "PRESS START");
                    al_flip_display();
                    al_rest(0.5);
                    draw = true; /**< ends the game */
                }
            }
        }

        if (events.type == ALLEGRO_EVENT_TIMER){ /**< movement of the spaceship */

            al_get_keyboard_state(&keyboardState1); /**< gets the imput from the keyboard */
            active = true;

            if(al_key_down(&keyboardState1, ALLEGRO_KEY_ESCAPE)){ /**< pressing scape key */
                al_draw_text(font, al_map_rgb(254,117,200), ScreenWidth/2, ScreenHeight/3, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
                al_rest(1.0);
                done = true; /**< ends the game */
            }

            if(al_key_down(&keyboardState1, ALLEGRO_KEY_DOWN)){
                player2.playerY += moveSpeed;
                //dir = DOWN;

            } else if (al_key_down(&keyboardState1, ALLEGRO_KEY_UP)){
                player2.playerY -= moveSpeed;
                //dir = UP;

            } else if (al_key_down(&keyboardState1, ALLEGRO_KEY_RIGHT)){
                player2.playerX += moveSpeed;
                //dir = RIGHT;

            } else if (al_key_down(&keyboardState1, ALLEGRO_KEY_LEFT)){
                player2.playerX -= moveSpeed;
                //dir = LEFT;

            } else if (al_key_down(&keyboardState1, ALLEGRO_KEY_SPACE) && CanPlayerShoot==true){

                if(player2.currBullets < maxBullets-1){ //initializes bullet
                    player2.currBullets++;
                    /** @fn al_play_sample(spaceship_shoot, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    * @brief Starts playing the given audio
                    * @param "spaceship_shoot" is the ALLEGRO_SAMPLE variable wich includes the mp3 file
                    * @param 1.0 is a float number corresponding the volume of the audio
                    * @param 0.0 is a float number that shows from which side-speaker the audio should come out
                    * @param 1.0 is the speed of the audio
                    * @param ALLEGRO_PLAYMODE will decide the way the sound is played (once, loop, etc)
                    */
                    al_play_sample(spaceship_shoot, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); /**< plays sound */
                    BulletsArray[player2.currBullets].bulletX = player2.playerX+30;
                    BulletsArray[player2.currBullets].bulletY = player2.playerY;
                    BulletsArray[player2.currBullets].destinyX = 0.0; /** because the bullet will go straight*/
                    BulletsArray[player2.currBullets].destinyY = -5.0;
                    CanPlayerShoot = false;
                }

                al_draw_text(font, electricYellow, (ScreenWidth/2)-2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!");
                al_draw_text(font, al_map_rgb(254,50,200), (ScreenWidth/2)+2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!");

            } else{
                active = false; /**< the spaceship is not moving */
            }

            if(BulletControlCounter++ > 20){ //time before the player is able to shoot again
                CanPlayerShoot = true;
                BulletControlCounter = 0;
            }

            if(player2.currBullets > 0){ //draws bullet
                    for (int i=1; i<=player2.currBullets; i++){ //looks for all the current bullents in the array
                        BulletsArray[i].bulletX += BulletsArray[i].destinyX; // in this case, it's 0=0+0 because the bullet goes straight
                        BulletsArray[i].bulletY += BulletsArray[i].destinyY; //increases vertical position of the bullet

                        drawBullet(BulletsArray[i].bulletX, BulletsArray[i].bulletY); /**< Draws the bullets*/

                        if(BulletsArray[i].bulletY > ScreenHeight || BulletsArray[i].bulletY < 0 || BulletsArray[i].bulletX > ScreenWidth || BulletsArray[i].bulletX < 0 ){ //is the bullet inside the screen?

                                BulletsArray[i] = BulletsArray[player2.currBullets]; // overwrite the values of BulletsArray[i]
                                player2.currBullets--; //disappears a bullet
                                if(player2.currBullets < 0){
                                    player2.currBullets = 0; //We use this in case the number goes under 0, to avoid errors
                                }
                        }
                    }
                }

            if(Collision(player2.playerX, player2.playerY, enemyX, enemyY, playerWidth, playerHeight, enemyWidth, enemyHeight)){
                al_draw_text(font, al_map_rgb(254,117,200), ScreenWidth/2, ScreenHeight/3, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
                al_rest(1.0);
                playerWidth += al_get_bitmap_width(player)/3; /**< simulates animation of spaceship */
                //al_rest(1.0);
                done = true; /**< ends the game */
            }

            draw = true;
        }

        if(draw == true){
            //draw = false;
            //al_draw_filled_circle(x, y, 10, playerColor); /**< draws a circle everytime a key is pressed */
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
            drawSpaceship(player, player2);
            //al_draw_bitmap_region(player, 0, 0, playerWidth, playerHeight, player2.playerX, player2.playerY, NULL); //0 should be player2.playerY * al_get_bitmap_heght(player)/numberofframesvertically
            al_draw_text(font, al_map_rgb(44,117,255), ScreenWidth/2, 50, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!");
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0)); /**< cleans screen so it looks like moving */
            al_draw_bitmap_region(enemy1, 0, 0, 50, 40, enemyX, enemyY, NULL);

            if (enemyX < 700 && leftright==1){ /**< enemy goes right */
                enemyX += 3;

            } else if (enemyX > 100 && leftright==0){ /**< enemy goes right */
                enemyX -= 3;
            }

            if(enemyX >= 700 && enemyY < 700 && leftright==1){ /**< enemy goes down once, then moves right */
                enemyY += 50;
                leftright = 0;
            }

            if(enemyX <= 100 && enemyY < 700 && leftright==0){ /**< enemy goes down once, then moves left */
                enemyY += 50;
                leftright = 1;
            }
        }
   }
   al_destroy_bitmap(player);
   al_destroy_sample(spaceship_shoot);
   al_destroy_sample(main_song);
   al_destroy_display(display);
   al_destroy_timer(timer1);
   al_destroy_event_queue(event_queue1);
   return 0;
}

   //float points[8] = {0, 0, 400, 100, 50, 200, ScreenWidth, ScreenHeight};
   //al_draw_spline(points, electricBlue, 1.0);
   //al_draw_rectangle(100, 100, 150, 130, al_map_rgb(0,200,0), 6.0);
   //al_draw_filled_circle(ScreenWidth/2, ScreenHeight-100, 10, electricBlue);
   //al_draw_arc(10, ScreenHeight-100, 10, 0, 4.0, al_map_rgb(255,0,240), 3.0);
   //al_draw_line(100, 500, 300, 500, electricBlue, 6.0);
   //al_draw_pixel(500, 500, electricBlue);
   //int trianX1=10, trianY1=10, trianX2=40, trianY2=10, trianX3=25, trianY3=40;
   //al_draw_filled_triangle(trianX1, trianY1, trianX2, trianY2, trianX3, trianY3, al_map_rgb(200,0,0)); /**< draws like: X1,Y1, X2,Y2, X3,Y3 */

/**
* @fn initialize_allegro_and_display()
* @brief Is the first and most important function.
* Creates and makes sure Allegro, the display, and the window containing the display, work.
* Still doesn't have nothing inside, because the *display is required later in the main.
* @param No parameters required.
* @return I'm gessuing it should return the *display, but I haven't figurerd out how to do that yet.
*/
