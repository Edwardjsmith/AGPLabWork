#pragma once
//The #include order is important
#define DIK_W               0x11
#define DIK_A               0x1E
#define DIK_S               0x1F
#define DIK_D               0x20
#define DIK_SPACE			0x39

#define DIK_UP              0xC8    /* UpArrow on arrow keypad */
#define DIK_LEFT            0xCB    /* LeftArrow on arrow keypad */
#define DIK_RIGHT           0xCD    /* RightArrow on arrow keypad */
#define DIK_DOWN            0xD0    /* DownArrow on arrow keypad */

#define DIK_ESCAPE          0x01


#include <d3d11.h>
#include <dxgi.h>
#include <d3dx11.h>
#include <windows.h>
#include <dxerr.h>
#include <xnamath.h>
#include <fstream>


#include "text2D.h"
#include "CubeMap.h"
#include "enemy.h"
#include "Player.h"
#include "timer.h"
#include "input.h"
#include "particleGenerator.h"
#include "thirdPersonCamera.h"
#include "Physics.h"
#include "soundManager.h"
#include "Pickup.h"


#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT

class Game
{
public:
	Game(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	~Game();

	HRESULT initD3D();
	HRESULT init();
	HRESULT createWindow();
	void Update();
	void RenderFrame();

	int mCmdShow;
	HINSTANCE mInstance, mPrevInstance;

	void Cleanup();

	bool running;
private:
	//////////////////////////////////////////////////////////////////////////////////////
//	Global Variables
//////////////////////////////////////////////////////////////////////////////////////

	HWND		g_hWnd = NULL;
	ID3D11RenderTargetView* g_pBackBufferRTView = NULL;
	D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           g_pD3DDevice = NULL;
	ID3D11DeviceContext*    g_pImmediateContext = NULL;
	IDXGISwapChain*         g_pSwapChain = NULL;
	// Clear the back buffer - choose a colour you like


	ID3D11DepthStencilView* g_pZBuffer;



	timer* Timer;
	Text2D* mScore;
	Player* player;
	enemy* Enemy;
	CubeMap* g_cubeMap;
	input* Input;
	particleGenerator* particleFountain;
	particleGenerator* rain;
	thirdPersonCamera* mainCamera;
	Camera* miniMap;
	Model* floor;
	XMVECTOR g_directional_light_shines_from;
	XMVECTOR g_directional_light_colour;
	XMVECTOR g_ambient_light_colour;

	//entity* pickup;

	int mScreenWidth = 640;
	int mScreenHeight = 480;

	int mMouseX, mMouseY;

	char mWindowName[100] = "Fetch the booty";

	float r = 0.1f;
	float g = 0.2f;
	float b = 0.6f;
	int score = 0;
	float gClearColour[4] = { r, g, b, 1.0f };
	float gravityScale = 1.0f;

	std::vector<entity*> pickups;
	std::vector<entity*> staticObstacle;
	
};

