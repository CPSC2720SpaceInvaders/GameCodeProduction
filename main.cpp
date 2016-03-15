#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

int main(){

   if(!al_init()) {
      al_show_native_message_box(NULL, NULL, NULL, "Failed to initialize allegro 5!", NULL, NULL);
      return -1;
   }

   //al_set_new_display_flags();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   al_set_window_position(display, 200, 100);
   al_set_window_title(display, "2720");

   if(!display) {
      al_show_native_message_box(display, "Error Title", "Display Settings", "Display window was unsuccessfull", NULL, NULL);
      return -1;
   }

   //al_show_native_message_box(display, "Message Title", "Display Settings", "Display window is done", NULL, NULL);

   al_rest(5.0);
   al_destroy_display(display);
   return 0;
}
