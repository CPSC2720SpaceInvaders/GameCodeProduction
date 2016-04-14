GPP = g++11
CFLAGS = -std=c++98 -Wall -I /usr/include/allegro5
# LIBDIR = /home/lib2720/allegro/lib/
LNFLAGS = -lallegro -lallegro_primitives -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_font -lallegro_ttf
OBJECTS = main.o 


main: $(OBJECTS)
	g++ $(CFLAGS) -c main.cpp -o $(OBJECTS)

%.o : %.cc
	$(GPP) $(CFLAGS) -c $^

clean:
	rm -rf *.o main
