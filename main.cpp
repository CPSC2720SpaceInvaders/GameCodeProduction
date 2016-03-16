#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>

#define ScreenWidth 800
#define ScreenHeight 800

/**
* @file main.cpp
* @brief Initialization of the display and the protagonist.
* C++ Allegro game for CPSC 2720 project:
* "Space Invaders -like- game"
* @author Adad, Bertram, Jiaying & Okingo.
* @bug No known bugs.
*/

int main(){
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
   ALLEGRO_FONT *font = al_load_font("Custom Font.ttf", 36, NULL);
   al_draw_text(font, al_map_rgb(44,117,255), ScreenWidth/2, ScreenHeight/2, ALLEGRO_ALIGN_CENTRE, "Little Space Circle Shooting to Triangles!");

   al_init_primitives_addon();  /**< intializes primitives to draw figures */
   ALLEGRO_COLOR electricBlue = al_map_rgb(118,180,255);
   ALLEGRO_COLOR electricYellow = al_map_rgb(255,250,44);
   ALLEGRO_COLOR electricRed = al_map_rgb(254,1,64);
   ALLEGRO_COLOR playerColor = electricBlue; /**< original color of the circle */

   //float points[8] = {0, 0, 400, 100, 50, 200, ScreenWidth, ScreenHeight};
   //al_draw_spline(points, electricBlue, 1.0);

   al_draw_filled_triangle(10, 10, 40, 10, 25, 40, al_map_rgb(200,0,0)); /**< draws like: X1,Y1, X2,Y2, X3,Y3 */
   al_draw_rectangle(100, 100, 150, 130, al_map_rgb(0,200,0), 6.0);
   //al_draw_filled_circle(ScreenWidth/2, ScreenHeight-100, 10, electricBlue);
   al_draw_arc(10, ScreenHeight-100, 10, 0, 4.0, al_map_rgb(255,0,240), 3.0);
   al_draw_line(100, 500, 300, 500, electricBlue, 6.0);
   al_draw_pixel(500, 500, electricBlue);

   al_install_keyboard(); /**< intializes the hability to recieve commands from keyboard */
   ALLEGRO_KEYBOARD_STATE keyboardState1;
   bool done=false; /**< if it is true, the game ends */
   bool draw=true;
   float x = ScreenWidth/2; /**< plauyer's initial position */
   float y = ScreenHeight-100;
   int moveSpeed = 10;
   int dir = DOWN;

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
   ALLEGRO_BITMAP *player;
   player = al_load_bitmap("/home/victor/Dropbox/git/GameCodeProduction/Resources/spaceship.png"); /**< loads player sprite */
   if(!player){
        al_show_native_message_box(display, "Message Title", "Bitmap Settings", "Could not load Player", NULL, NULL);
   }

   al_start_timer(timer1); /**< don't do anything nor initialize variables, NOTHING, after starting the timer */
   while(!done){ /**< the only thing that must be after the timer is the game loop (while) */
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue1, &events); /**< waits for something to happen */

        if (events.type == ALLEGRO_EVENT_KEY_UP){
            switch(events.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    done = true; /**< ends the game */
            }
        } else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            done = true; /**<ends the game (closes the window) */

//        } else if(events.type == ALLEGRO_EVENT_MOUSE_AXES){ /**< player detects/follows movement of mouse */
//            x = events.mouse.x;
//            y = events.mouse.y;

        } else if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(events.mouse.button & 1){
                playerColor = electricYellow;
            } else if (events.mouse.button & 2){
                playerColor = electricRed;
            }
        }

        if (events.type == ALLEGRO_EVENT_TIMER){ /**< movement of the spaceship */
            al_get_keyboard_state(&keyboardState1);
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
            }
            draw = true;
        }

        if(draw == true){
            draw = false;
            //al_draw_filled_circle(x, y, 10, playerColor); /**< draws a circle everytime a key is pressed */
            al_draw_bitmap(player, x, y, NULL); /**< draws the player */
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0)); /**< cleans screen so it looks like moving */
        }
   }

   al_rest(5.0);  /**< number of seconds the program waits before closing itself */
   al_destroy_bitmap(player);
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
