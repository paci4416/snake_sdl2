#include <stdio.h>
#include "game.h"

int main( int argc, char* args[]) {
	Game game;
	
	if (!game.init()) 
	{
		printf("Error in game init\n");
		return 1;
	}

	while (game.isRunning())
	{
		game.handleEvents();
		game.update();
		game.draw();
	}
}
