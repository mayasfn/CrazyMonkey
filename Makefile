OBJ = obj/Jungle.o obj/Arbre.o obj/Singe.o   obj/Vec2.o 

COMPILER = g++

CFLAGS = -g -Wall

INCLUDE_DIR_SDL = -I/usr/include/SDL2
INCLUDE_DIR			= -Isrc -Isrc/core -Isrc/sdl2 -Itxt
LIBS_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lGL

all: folders  bin/Txt bin/Sdl2 bin/testR docs

folders:
	mkdir -p obj bin data

bin/testR : $(OBJ) obj/mainRegression.o 
	$(COMPILER) $(OBJ) obj/mainRegression.o -o bin/testR

bin/Txt : $(OBJ) obj/AffichageTxt.o obj/winTxt.o obj/main_txt.o
	$(COMPILER) $(OBJ) obj/AffichageTxt.o obj/winTxt.o obj/main_txt.o -o bin/Txt

bin/Sdl2 : $(OBJ) obj/AffichageSDL2.o obj/mainSDL2.o
	$(COMPILER) $(OBJ) obj/AffichageSDL2.o obj/mainSDL2.o -o bin/Sdl2 $(LIBS_SDL) 

obj/mainSDL2.o: src/sdl2/mainSDL2.cpp src/sdl2/AffichageSDL2.h 
	$(COMPILER) $(CFLAGS) -c src/sdl2/mainSDL2.cpp -o obj/mainSDL2.o

obj/AffichageSDL2.o: src/sdl2/AffichageSDL2.h src/sdl2/AffichageSDL2.cpp src/core/Jungle.h 
	$(COMPILER) $(CFLAGS) -c src/sdl2/AffichageSDL2.cpp -o obj/AffichageSDL2.o

obj/main_txt.o : src/txt/main_txt.cpp src/txt/AffichageTxt.h
	$(COMPILER) $(CFLAGS) -c src/txt/main_txt.cpp  -o obj/main_txt.o

obj/winTxt.o : src/txt/winTxt.cpp src/txt/winTxt.h
	$(COMPILER) $(CFLAGS) -c src/txt/winTxt.cpp -o obj/winTxt.o

obj/AffichageTxt.o: src/txt/AffichageTxt.cpp src/txt/AffichageTxt.h src/txt/winTxt.h src/core/Jungle.h 
	$(COMPILER) $(CFLAGS) -c src/txt/AffichageTxt.cpp -o obj/AffichageTxt.o

obj/mainRegression.o: src/core/mainRegression.cpp src/core/Jungle.h
	$(COMPILER) $(CFLAGS) -c src/core/mainRegression.cpp -o obj/mainRegression.o

obj/Jungle.o: src/core/Jungle.cpp src/core/Jungle.h src/core/Arbre.h src/core/Singe.h src/core/Vec2.h
	$(COMPILER) $(CFLAGS) -c src/core/Jungle.cpp -o obj/Jungle.o

obj/Arbre.o: src/core/Arbre.cpp src/core/Arbre.h src/core/Vec2.h
	$(COMPILER) $(CFLAGS) -c src/core/Arbre.cpp -o obj/Arbre.o

obj/Singe.o: src/core/Singe.cpp src/core/Singe.h src/core/Vec2.h
	$(COMPILER) $(CFLAGS) -c src/core/Singe.cpp -o obj/Singe.o

obj/Vec2.o: src/core/Vec2.cpp src/core/Vec2.h
	$(COMPILER) $(CFLAGS) -c src/core/Vec2.cpp -o obj/Vec2.o


docs: doc/image.doxy
	doxygen doc/image.doxy

clean:
	rm -rf obj/* bin/* doc/html callgrind.out.*
