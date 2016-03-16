#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

#define ScreenWidth 800
#define ScreenHeight 800

int main(){

   if(!al_init()) {
      al_show_native_message_box(NULL, "Error", NULL, "Failed to initialize allegro 5!", NULL, NULL);
      return -1;
   }
   const float fps = 60.0; //frames per second variable
   enum Direction1 { UP, DOWN, LEFT, RIGHT };

   al_set_new_display_flags(ALLEGRO_NOFRAME); //screen without frames
   ALLEGRO_DISPLAY *display = al_create_display(ScreenWidth, ScreenHeight); //creates main display
   if(!display) {
      al_show_native_message_box(display, "Error", "Display Settings", "Display window was unsuccessfull", NULL, NULL);
      return -1; //error message in case display couldn't be created
   }
   al_set_window_position(display, 100, 100);
   al_set_window_title(display, "2720's Project");

   al_init_font_addon(); //intializes fonts so we can write on the display
   al_init_ttf_addon();
   ALLEGRO_FONT *font = al_load_font("Custom Font.ttf", 36, NULL);
   al_draw_text(font, al_map_rgb(44,117,255), ScreenWidth/2, ScreenHeight/2, ALLEGRO_ALIGN_CENTRE, "Little Space Circle Shooting to Triangles!");

   al_init_primitives_addon();  //intializes primitives to draw figures
   ALLEGRO_COLOR electricBlue = al_map_rgb(44,117,255);
   //float points[8] = {0, 0, 400, 100, 50, 200, ScreenWidth, ScreenHeight};
   //al_draw_spline(points, electricBlue, 1.0);
   al_draw_filled_triangle(10, 10, 40, 10, 25, 40, al_map_rgb(200,0,0)); // draws like: X1,Y1, X2,Y2, X3,Y3
   al_draw_rectangle(100, 100, 150, 130, al_map_rgb(0,200,0), 6.0);
   //al_draw_filled_circle(ScreenWidth/2, ScreenHeight-100, 10, electricBlue);
   al_draw_arc(10, ScreenHeight-100, 10, 0, 4.0, al_map_rgb(255,0,240), 3.0);
   al_draw_line(100, 500, 300, 500, electricBlue, 6.0);
   al_draw_pixel(500, 500, electricBlue);

   al_install_keyboard();  //intializes the hability to recieve commands from keyboard
   ALLEGRO_KEYBOARD_STATE keyboardState1;
   bool done=false; // if it is true, the game ends
   bool draw=true;
   int x=100, y=100; //circle's position
   int moveSpeed = 10;
   int dir = DOWN;
   ALLEGRO_TIMER *timer1 = al_create_timer(1.0/fps); //60 frames per second
   ALLEGRO_EVENT_QUEUE *event_queue1 = al_create_event_queue();
   al_register_event_source(event_queue1, al_get_keyboard_event_source());
   al_register_event_source(event_queue1, al_get_timer_event_source(timer1));
   al_register_event_source(event_queue1, al_get_display_event_source(display));

   al_start_timer(timer1); //don't do anything nor initialize variables, NOTHING, after starting the timer
   while(!done){ //the only thing that must be after the timer is the game loop (while)
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue1, &events); //waits for something to happen

        if (events.type == ALLEGRO_EVENT_KEY_UP){
            switch(events.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    done = true; //ends the game

            }
        }
        else if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            done = true; //ends the game (closes the window)
        }

        if (events.type == ALLEGRO_EVENT_TIMER){
            al_get_keyboard_state(&keyboardState1);
            if(al_key_down(&keyboardState1, ALLEGRO_KEY_DOWN)){
                y = y + moveSpeed;
            } else if (al_key_down(&keyboardState1, ALLEGRO_KEY_UP)){
                y = y - moveSpeed;
            } else if (al_key_down(&keyboardState1, ALLEGRO_KEY_RIGHT)){
                x = x + moveSpeed;
            } else if (al_key_down(&keyboardState1, ALLEGRO_KEY_LEFT)){
                x = x - moveSpeed;
            }
            draw = true;
        }

        if(draw == true){
            draw = false;
            al_draw_filled_circle(x, y, 10, electricBlue); //draws a circle everytime a key is pressed
            al_flip_display();
            al_clear_to_color(al_map_rgb(0,0,0)); //cleans screen so it looks like moving
        }
   }

   //al_rest(5.0); //number of seconds the program waits before closing itself
   al_destroy_display(display);
   al_destroy_timer(timer1);
   al_destroy_event_queue(event_queue1);
   return 0;
}

//al_show_native_message_box(display, "Message Title", "Display Settings", "Display window is done", NULL, NULL);
