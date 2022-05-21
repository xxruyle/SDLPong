debug:
	g++ -I src/include -I src/personal -L src/lib -L src/lib/x64 -L src/lib/x86 -o bin/debug/main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image