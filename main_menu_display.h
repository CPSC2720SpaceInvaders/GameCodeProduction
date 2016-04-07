#ifndef MAIN_MENU_H__
#define MAIN_MENU_H__

    if(blinking++ < 20){
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

    }else{
        al_draw_bitmap_region(menu, 1200, menuY, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, NULL);
        al_flip_display();
        al_clear_to_color(backgroundColor); /**< cleans screen so it looks like moving */
    }

    if(blinking > 40){
        blinking = 0;
    }

    if(al_key_down(&keyboardState1, ALLEGRO_KEY_ENTER))  /**< pressing ENTER key */
    {
        menuY = 800;
        loadingGame = true;
    }

    if(loadingGame == true){ /**< stops displaying "main menu" and starts displaying "loading" */
        loadingTimer++;
    }

    if (loadingTimer > 80){ /**< miliseconds the LOADING screen will be displayed */
        draw = true;
    }

#endif
