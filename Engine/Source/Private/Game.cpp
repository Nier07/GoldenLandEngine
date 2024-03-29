#include "Game.h"
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Graphics/Texture.h"
#include "Input.h"
#include "GameObjects/GameObject.h"

//DEBUG
#include "Graphics/Animation.h"
#include "Math/Vector2.h"
#include "GameObjects/PhysicsObject.h"

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

Texture* Game::ImportTexture(const char* PathToFile)
{
	Texture* NewTexture = new Texture(m_RendererRef);

	// loop through textures
	for (Texture* TexRef : m_TextureStack) {
		// check if texture has already been imported
		if (std::strcmp(TexRef->GetPath(), PathToFile) == 0) {
			//copy matched element if there is a matching path
			NewTexture->CopyTexture(TexRef);
			//add to texture stack
			m_TextureStack.push_back(NewTexture);
			//ignore rest of funciton on success
			return NewTexture;
		}
	}

	//attempt to import texture
	if (!NewTexture->ImportTexture(PathToFile)) {
		//if it failed delete and update new texture to null ptr
		delete NewTexture;
		NewTexture = nullptr;
	}
	else {
		//if import was successful
		m_TextureStack.push_back(NewTexture);
	}
	return NewTexture;
}

void Game::DestroyTexture(Texture* TextureToDestroy)
{
	int TexturesFound = 0;

	//loop through textures
	for (Texture* TexRef : m_TextureStack) {
		//if texture has a matching path
		if (std::strcmp(TextureToDestroy->GetPath(), TexRef->GetPath()) == 0) {
			TexturesFound++;

			if (TexturesFound > 1) {
				break;
			}
		}
	}

	//if there is not a copy deallocate all memeory related to texture
	if (TexturesFound <= 1) {
		TextureToDestroy->CleanUp();
	}

	//find texture in array
	auto it = std::find(m_TextureStack.begin(), m_TextureStack.end(), TextureToDestroy);
	//if texture is found
	if (it != m_TextureStack.end()) {
		m_TextureStack.erase(it);
	}

	//remove texture object from memory
	delete TextureToDestroy;
	TextureToDestroy = nullptr;

	GL_LOG("Game", "Texture has been destroyed");
}

template<typename T>
T* Game::AddGameObject()
{
	//create game object
	T* NewObject = new T();

	//add the object to pending spawn array
	m_GameObjectPendingSpawn.push_back(NewObject);

	return NewObject;
}

Game::Game()
{
	printf("Game Created.\n");

	m_IsGameOpen = true;
	m_WindowRef = nullptr;
	m_RendererRef = nullptr;
	m_GameInput = nullptr;

	//Debug Vars
	m_TestAnim1 = nullptr;
	m_TestObject = nullptr;
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
	m_WindowRef = SDL_CreateWindow("Golden Land Engine", // title
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

	//create the game input
	m_GameInput = new Input();

	//Debug

	m_TestObject = AddGameObject<PhysicsObject>();

	GameLoop();
}

void Game::GameLoop()
{
	while (m_IsGameOpen) {
		PreLoop();

		ProcessInput();

		Update();

		Render();

		CollectGarbage();
	}

	CleanUp();
}

void Game::CleanUp()
{
	//destroy any objects pending spawn
	for (auto GO : m_GameObjectPendingSpawn) {
		GO->CleanUp();
		delete GO;
		GO = nullptr;
	}
	//destroy any remaining game objects
	for (auto GO : m_GameObjectStack) {
		GO->CleanUp();
		delete GO;
		GO = nullptr;
	}
	//clean up and remove all textures from texture stack
	for (int i = m_TextureStack.size() - 1; i > -1; i--) {
		DestroyTexture(m_TextureStack[i]);
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

void Game::PreLoop()
{
	//add all game objects pending spawn to game obeject stack
	for (auto GO : m_GameObjectPendingSpawn) {
		m_GameObjectStack.push_back(GO);
		GO->Start();
	}

	//resize the array to 0
	m_GameObjectPendingSpawn.clear();
}

void Game::ProcessInput()
{
	//process the inputs for the game
	m_GameInput->ProcessInput();

	//run the input listener function for all game objects
	for (auto GO : m_GameObjectStack) {
		if (GO != nullptr) {
			GO->ProcessInput(m_GameInput);
		}
	}
}

void Game::Update()
{
	//record previous frame time
	static double LastTickTime = 0.0f;
	//record current frame time
	double CurrentTickTime = (double)SDL_GetTicks64();
	//get delta time - how much time passed since the last frame 
	double LongDelta = CurrentTickTime - LastTickTime;
	//convert from ms to seconds
	double DeltaTime = LongDelta / 1000.0f;
	//set the last tick time
	LastTickTime = CurrentTickTime;

	//DEBUG
	//pos of animation on screen
	//static Vector2 Position(640.0f, 360.0f);
	//float Speed = 100.0f * (float) DeltaTime;
	////direction to move in
	//Vector2 MovementDirection(0.0f);

	//if (m_GameInput->IsKeyDown(GL_KEY_W)) {
	//	MovementDirection.y += -1.0f;
	//}
	//if (m_GameInput->IsKeyDown(GL_KEY_S)) {
	//	MovementDirection.y += 1.0f;
	//}
	//if (m_GameInput->IsKeyDown(GL_KEY_A)) {
	//	MovementDirection.x += -1.0f;
	//}
	//if (m_GameInput->IsKeyDown(GL_KEY_D)) {
	//	MovementDirection.x += 1.0f;
	//}

	//if (m_GameInput->IsKeyDown(GL_KEY_LSHIFT)) {
	//	Speed = 200.0f * (float) DeltaTime;
	//}

	//if (m_GameInput->IsKeyDown(GL_KEY_Q)) {
	//	if (m_TestObject != nullptr) {
	//		m_TestObject->DestroyObject();
	//		m_TestObject = nullptr;
	//	}
	//}

	//Position += MovementDirection * Speed;

	////TODO: update game logic
	//if (m_TestAnim1 != nullptr) {
	//	m_TestAnim1->SetPosition(Position.x, Position.y);
	//	m_TestAnim1->Update((float)DeltaTime);
	//}
	//run the update logic for all game objects
	for (auto GO : m_GameObjectStack) {
		if (GO != nullptr) {
			GO->Update((float)DeltaTime);
			GO->PostUpdate((float)DeltaTime);
		}
	}
}

void Game::Render()
{
	//telling renderer what color to use next
	SDL_SetRenderDrawColor(m_RendererRef, 40, 40, 40, 255);

	//Use stored color to clear previous frame and refill with stored color
	SDL_RenderClear(m_RendererRef);

	//Render Custom Graphics
	for (Texture* TexRef: m_TextureStack) {
		if (TexRef != nullptr) {
			TexRef->Draw();
		}
	}

	//Present graphics to renderer
	SDL_RenderPresent(m_RendererRef);
}

void Game::CollectGarbage()
{
	//TODO: delte objects at end of frame
	for (int i = m_GameObjectStack.size() - 1; i >= 0; --i) {
		if (!m_GameObjectStack[i]->isPendingDestroy()) {
			continue;
		}
		
		//make sure game object isnt nullptr
		if (m_GameObjectStack[i] != nullptr) {
			m_GameObjectStack[i]->CleanUp();
			delete m_GameObjectStack[i];

			//remove from and resize the array
			m_GameObjectStack.erase(m_GameObjectStack.begin() + i);
		}
	}
}
