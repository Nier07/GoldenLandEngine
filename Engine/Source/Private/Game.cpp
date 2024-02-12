#include "Game.h"
#include <iostream>
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Graphics/Texture.h"

Game* Game::GetGame()
{
	//static only runs initalisation once
	//only runs once, thread safe
	static Game* GameSingleton = new Game();

	return GameSingleton;
}

void Game::DestroyGame()
{
	delete GetGame();
}

Game::Game()
{
	printf("Game Created.\n");

	m_IsGameOpen = true;
	m_WindowRef = nullptr;
	m_RendererRef = nullptr;

	//Debug Vars
	m_TestTexture1 = nullptr;
}

Game::~Game()
{
	printf("Game Destroyed\n");
}

void Game::Initialise()
{
	//init dependencies
	//init SDL end game on fail
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		GL_LOG("Game", "SDL failed to init: " << SDL_GetError());
		return;
	}

	GL_LOG("Game", "Game sucessfully initialised all libraries");

	Start();
}

void Game::Start()
{
	//launch game window

	//create window and check if it failed
	m_WindowRef = SDL_CreateWindow("Golden Land", // title
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // start pos
		1280, 720, // res
		0); // flags

	// check if window failed to create
	if(m_WindowRef == nullptr){
		GL_LOG("Game", "SDL Window failed to create" << SDL_GetError());

		//deallocate all stuff allocated prior to this point
		CleanUp();
		return;
	}

	//create renderer and check if it failed
	m_RendererRef = SDL_CreateRenderer(m_WindowRef, -1, 0);

	if (m_RendererRef == nullptr) {
		GL_LOG("Game", "SDL Renderer failed to create" << SDL_GetError());

		CleanUp();
		return;
	}

	//Debug
	m_TestTexture1 = new Texture(m_RendererRef);
	if (!m_TestTexture1->ImportTexture("Content/Letters/HRed.png")) {
		m_TestTexture1->CleanUp();
		delete m_TestTexture1;
		m_TestTexture1 = nullptr;
	}
	else {
		m_TestTexture1->m_PosX = 100.0f;
		m_TestTexture1->m_PosY = 200.0f;
		m_TestTexture1->m_Angle = 69.0f;
	}

	GameLoop();
}

void Game::GameLoop()
{
	while (m_IsGameOpen) {
		ProcessInput();

		Update();

		Render();

		CollectGarbage();
	}

	CleanUp();
}

void Game::CleanUp()
{
	if (m_TestTexture1 != nullptr) {
		m_TestTexture1->CleanUp();
		delete m_TestTexture1;
	}

	//does renderer exist
	if (m_RendererRef != nullptr) {
		SDL_DestroyRenderer(m_RendererRef);
	}

	//does window exist
	if (m_WindowRef != nullptr) {
		SDL_DestroyWindow(m_WindowRef);
	}

	SDL_Quit();

	GL_LOG("Game", "Game has deallocated all memory");
}

void Game::ProcessInput()
{
	// Data type to read STL input events for the window
	SDL_Event InputEvent;

	//run through each input in the frame
	while (SDL_PollEvent(&InputEvent)) {
		//when x is pressed close the app
		if (InputEvent.type == SDL_QUIT) {
			QuitApp();
		}
	}
}

void Game::Update()
{
	//TODO: update game logic
	static float Angle = 0.0f;

	if (m_TestTexture1 != nullptr) {
		m_TestTexture1->m_Angle = Angle;
	}

	Angle += 0.1f;
}

void Game::Render()
{
	//telling renderer what color to use next
	SDL_SetRenderDrawColor(m_RendererRef, 40, 40, 40, 255);

	//Use stored color to clear previous frame and refill with stored color
	SDL_RenderClear(m_RendererRef);

	//Render Custom Graphics
	if (m_TestTexture1 != nullptr) {
		m_TestTexture1->Draw();
	}
	//Present graphics to renderer
	SDL_RenderPresent(m_RendererRef);
}

void Game::CollectGarbage()
{
	//TODO: delte objects at end of frame
}
