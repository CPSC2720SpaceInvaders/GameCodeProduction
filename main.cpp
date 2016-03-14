#include <allegro.h>
// we need to be able to compile, everyone of us, this file on our own computer

int main(){
 
    allegro_init();
    install_keyboard();
    set_gfx_mode( GFX_AUTODETECT, 640, 480, 0, 0);
    
    readkey();
    
    return 0;
    
}   
END_OF_MAIN(); 