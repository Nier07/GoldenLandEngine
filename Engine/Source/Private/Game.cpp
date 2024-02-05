#include "Game.h"
#include <iostream>

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
}

Game::~Game()
{
	printf("Game Destroyed\n");
}

void Game::Initialise()
{
	printf("Initialise Game\n");

	//init dependencies

	Start();
}

void Game::Start()
{
	printf("Start Game\n");

	//launch game window

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
	printf("Cleanup Game\n");
}

void Game::ProcessInput()
{
	printf("Process Input\n");
}

void Game::Update()
{
	printf("Update\n");

	static int Frames = 0;

	if (Frames >= 30) m_IsGameOpen = false;
	else Frames++;
}

void Game::Render()
{
	printf("Render\n");
}

void Game::CollectGarbage()
{
	printf("Garbage\n");
}
