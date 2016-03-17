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

struct ENEMY{
    int enemyX, enemyY;
    ALLEGRO_BITMAP *enemy;
    //int enemieWidth, enemieHeight;    //width and height of character
    //int animation;
    //int life;
    void initialize_enemy(int _ememyX, int _enemyY, int _life);
};

void ENEMY::initialize_enemy(int _ememyX, int _enemyY, int _life){
        enemyX = _ememyX;
//        enemyY = _ememyY;
        //life = _life;
}

int main(){
	int ScreenWidth = 800;
	int ScreenHeight = 800;
	if(!al_init()) { /**< do NOT initialice anything before al_init(); */
      al_show_native_message_box(NULL, "Error", NULL, "Failed to initialize allegro 5!", NULL, NULL);
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

   enum Direction1 { UP, DOWN, LEFT, RIGHT };

   al_init_font_addon(); /**< intializes fonts so we can write on the display */
   al_init_ttf_addon();
   ALLEGRO_FONT *font = al_load_font("Resources/Custom Font.ttf", 36, NULL);
   //al_draw_text(font, al_map_rgb(44,117,255), ScreenWidth/2, ScreenHeight/2, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!");

   al_init_primitives_addon();  /**< intializes primitives to draw figures */
   ALLEGRO_COLOR electricBlue = al_map_rgb(118,180,255);
   ALLEGRO_COLOR electricYellow = al_map_rgb(255,250,44);
   ALLEGRO_COLOR electricRed = al_map_rgb(254,1,64);
   ALLEGRO_COLOR playerColor = electricBlue; /**< original color of the circle */

   //float points[8] = {0, 0, 400, 100, 50, 200, ScreenWidth, ScreenHeight};
   //al_draw_spline(points, electricBlue, 1.0);
   //al_draw_rectangle(100, 100, 150, 130, al_map_rgb(0,200,0), 6.0);
   //al_draw_filled_circle(ScreenWidth/2, ScreenHeight-100, 10, electricBlue);
   //al_draw_arc(10, ScreenHeight-100, 10, 0, 4.0, al_map_rgb(255,0,240), 3.0);
   //al_draw_line(100, 500, 300, 500, electricBlue, 6.0);
   //al_draw_pixel(500, 500, electricBlue);
   //int trianX1=10, trianY1=10, trianX2=40, trianY2=10, trianX3=25, trianY3=40;
   //al_draw_filled_triangle(trianX1, trianY1, trianX2, trianY2, trianX3, trianY3, al_map_rgb(200,0,0)); /**< draws like: X1,Y1, X2,Y2, X3,Y3 */

   al_install_keyboard(); /**< intializes the hability to recieve commands from keyboard */
   ALLEGRO_KEYBOARD_STATE keyboardState1;

   al_install_audio(); /**< intializes the hability play audio */
   al_init_acodec_addon();
   ALLEGRO_SAMPLE *spaceship_shoot = al_load_sample("Resources/spaceship_shoot.wav"); /**< loads audio file */
   ALLEGRO_SAMPLE *main_song = al_load_sample("Resources/Underclocked.wav"); /**< ALLEGRO_SAMPLE doesn't support mp3 or mid files */
   al_reserve_samples(2); /**< indicate how many samples (songs) we are using */
   al_play_sample(main_song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0); /**< plays the main theme */

   bool done=false; /**< if it is true, the game ends */
   bool draw=true; /**< if it is true, the items will continue being drawed on the display */
   bool active=false; /**< makes sure a key is being pressed */
   float x = ScreenWidth/2, y = ScreenHeight-100; /**< player's initial position */
   int moveSpeed = 10;
   int dir = DOWN;
   int sourceX = 0, sourceY = 0; /**< represent the width and height of the spaceship inside the PNG file */

   const float fps = 60.0; /**< frames per second variable */
   ALLEGRO_TIMER *timer1 = al_create_timer(1.0/fps); /**< 60 frames per second */
   ALLEGRO_EVENT_QUEUE *event_queue1 = al_create_event_queue();
   al_register_event_source(event_queue1, al_get_timer_event_source(timer1));
   al_register_event_source(event_queue1, al_get_keyboard_event_source());
   al_register_event_source(event_queue1, al_get_display_event_source(display));

   al_install_mouse();
   al_register_event_source(event_queue1, al_get_mouse_event_source());
   al_hide_mouse_cursor(display); /**< hides the cursor */

   al_init_image_addon();
   ALLEGRO_BITMAP *player = al_load_bitmap("Resources/spaceship_large.png"); /**< loads player sprite */
   ALLEGRO_BITMAP *enemy1 = al_load_bitmap("Resources/enemy1.png");
   //al_convert_mask_to_alpha(player, al_map_rgb(255,0,255));
   if(!player){
        al_show_native_message_box(display, "Message Title", "Bitmap Settings", "Could not load Player", NULL, NULL);
   }

   al_start_timer(timer1); /**< don't do anything nor initialize variables, NOTHING, after starting the timer */
   while(!done){ /**< the only thing that must be after the timer is the game loop (while) */
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue1, &events); /**< waits for something to happen */

//        if (events.type == ALLEGRO_EVENT_KEY_UP){
//            switch(events.keyboard.keycode){
//                case ALLEGRO_KEY_ESCAPE: /**< pressing scape key */
//                    al_draw_text(font, al_map_rgb(254,117,200), ScreenWidth/2, ScreenHeight/3, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
//                    al_rest(1.0);
//                    done = true; /**< ends the game */
//            }
//        } else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
//            done = true; /**<ends the game (closes the window) */
//
//        } else if(events.type == ALLEGRO_EVENT_MOUSE_AXES){ /**< player detects/follows movement of mouse */
//            x = events.mouse.x;
//            y = events.mouse.y;
//        } else if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
//            if(events.mouse.button & 1){
//                playerColor = electricYellow;
//            } else if (events.mouse.button & 2){
//                playerColor = electricRed;
//            }
//        }

        if (events.type == ALLEGRO_EVENT_TIMER){ /**< movement of the spaceship */

            al_get_keyboard_state(&keyboardState1); /**< gets the imput from the keyboard */
            active = true;

            if(al_key_down(&keyboardState1, ALLEGRO_KEY_ESCAPE)){ /**< pressing scape key */
                al_draw_text(font, al_map_rgb(254,117,200), ScreenWidth/2, ScreenHeight/3, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
                al_rest(1.0);
                done = true; /**< ends the game */
            }

            if(al_key_down(&keyboardState1, ALLEGRO_KEY_DOWN)){
                y = y + moveSpeed;
                dir = DOWN;

            } else if (al_key_down(&keyboardState1, ALLEGRO_KEY_UP)){
                y = y - moveSpeed;
                dir = UP;

            } else if (al_key_down(&keyboardState1, ALLEGRO_KEY_RIGHT)){
                x = x + moveSpeed;
                dir = RIGHT;

            } else if (al_key_down(&keyboardState1, ALLEGRO_KEY_LEFT)){
                x = x - moveSpeed;
                dir = LEFT;

            } else if (al_key_down(&keyboardState1, ALLEGRO_KEY_SPACE)){
                /** @fn al_play_sample(spaceship_shoot, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                * @brief Starts playing the given audio
                * @param "spaceship_shoot" is the ALLEGRO_SAMPLE variable wich includes the mp3 file
                * @param 1.0 is a float number corresponding the volume of the audio
                * @param 0.0 is a float number that shows from which side-speaker the audio should come out
                * @param 1.0 is the speed of the audio
                * @param ALLEGRO_PLAYMODE will decide the way the sound is played (once, loop, etc)
                */
                al_play_sample(spaceship_shoot, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

            } else{
                active = false; /**< the spaceship is not moving */
            }

            draw = true;

            if (active == true){
                sourceX += al_get_bitmap_width(player)/3; /**< simulates animation of spaceship */
            } else {
                sourceX = 0; /**< everytime active is "true", increase the origin of the sprite */
            }
            if(sourceX >= al_get_bitmap_width(player)){
                sourceX = 0; /**< if we reach the end of the PNG file, start over */
            }
            sourceY = dir; /**< if we have sprites heading left or rigth, etc. this will help to crop them */
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
            al_draw_bitmap_region(player, sourceX, 0, 60, 40, x, y, NULL); //0 should be sourceY * al_get_bitmap_heght(player)/numberofframesvertically
            al_draw_text(font, al_map_rgb(44,117,255), ScreenWidth/2, ScreenHeight/5, ALLEGRO_ALIGN_CENTRE, "2720 Invaders!");
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0)); /**< cleans screen so it looks like moving */
        }

        al_draw_bitmap_region(enemy1, sourceX, 0, 60, 40, x, y, NULL);
   }

   //al_restal_rest(5.0);  /**< number of seconds the program waits before closing itself */
   al_destroy_bitmap(player);
   al_destroy_sample(spaceship_shoot);
   al_destroy_sample(main_song);
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
//public void initialize_allegro_and_display(){}

/*

void place_enemies(struct ENEMIES E[]){
    int indice = -1;
    int _tipo = 0;

    for(int i=0; i<5; i++){
        _tipo++;

        if (_tipo == 4) {
            _tipo = 1;
        }

        for(int j=0; j<11; j++){
            indice++;
            E[indice].initialice_pictures(int _enemyWidth, int _enemyHeight, int _life);
        }
    }
}

void draw_enemies(struct ENEMIES E[], int mov){
    int indice = -1;

    for(int i=0; i<5; i++){

        for(int j=0; j<11; j++){
            indice++;

            if(E[indice].vida > 0){
                E[indice].pinta(buffer, mov, E[indice].tipo-1);
                //para escojer enemigo es de 0 a 2 y la pose de 0 a 1
            }
        }
    }
}

void move_enemies(struct NAVE E[], int& mov, int& dir){
    for(int i = 0; i < 55; i++) E[i].x += dir;

    if(++mov == 2) mov = 0;

    if(limites(E, dir) == true){
        for(int j = 0; j < 55; j++){
            E[j].y += 10;
        }
    }
}

*/
