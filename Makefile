GPP = g++11
CFLAGS = -Wall -I /home/lib2720/allegro/include
LIBDIR = /home/lib2720/allegro/lib/
LNFLAGS = -lallegro_primitives -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_font -lallegro_ttf -lallegro
OBJECTS = main.o actor.o actorEnemyBasic.o actorPlayer.o bullet.o Hitbox.o objectSpawners.o projectile.o
LD_LIBRARY_PATH=/home/lib2720/allegro/lib/
export LD_LIBRARY_PATH

main: $(OBJECTS)
	$(GPP) -o main $(OBJECTS) -L $(LIBDIR) $(LNFLAGS)
	
%.o : %.cpp
	$(GPP) $(CFLAGS) -c $^

clean:
	rm -rf *.o main
