all:
	g++ -Iinclude/sdl -Llib -o main source/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf