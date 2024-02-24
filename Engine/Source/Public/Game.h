#pragma once
#include "EngineTypes.h"

//foward declaration
//dont need to know what it does just that it exists as a struct
struct SDL_Window;
struct SDL_Renderer;
class Texture;

//DEBUG
class Animation;

class Game {
public:
	// Get game singleton or create one if it doesnt exist
	static Game* GetGame();

	static void DestroyGame();

	void Run() { Initialise(); };

	void QuitApp() { m_IsGameOpen = false; }

	// Import texture into game
	Texture* ImportTexture(const char* PathToFile);

	// Safe destory texture
	void DestroyTexture(Texture* TextureToDestroy);

private:
	Game();
	~Game();

	// flag for ending game loop
	bool m_IsGameOpen;

	//stores the window and renderer for the game
	SDL_Window* m_WindowRef;
	SDL_Renderer* m_RendererRef;

	// gsjfg
	TArray<Texture*> m_TextureStack;

	//Debug Testing Vars
	Animation* m_TestAnim1;
	Animation* m_TestAnim2;
	Animation* m_TestAnim3;
	Animation* m_TestAnim4;
	Animation* m_TestAnim5;
	Animation* m_TestAnim6;
	Animation* m_TestAnim7;
	Animation* m_TestAnim8;
	Animation* m_TestAnim9;
	Animation* m_TestAnim10;
	// Core Game Funcs
	// init dependencies / libs, exit game on fail
	void Initialise();
	
	// run post-init funcs, load window / game startup funcs that rely on dependencies
	void Start();

	// Run game loop untill application is closed
	void GameLoop();

	// dealocate memory when game is exited
	void CleanUp();

	// Game Loop
	// looks for user input and process
	void ProcessInput();

	// update game logic before rendering based on input
	void Update();

	// displays results and render graphics based on update
	void Render();

	// Objects marked for deletion will be removed from memory
	void CollectGarbage();
};