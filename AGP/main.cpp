#include "Game.h"


//////////////////////////////////////////////////////////////////////////////////////
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	Game* game = new Game(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	game->init();

	while (game->running)
	{
		game->Update();
		game->RenderFrame();
	}

	delete game;
	return 0;
}

