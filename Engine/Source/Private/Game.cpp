#include "Game.h"
#include "SDL2/SDL.h"
#include "Debug.h"
#include "Graphics/Texture.h"

//DEBUG
#include "Graphics/Animation.h"

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

Game::Game()
{
	printf("Game Created.\n");

	m_IsGameOpen = true;
	m_WindowRef = nullptr;
	m_RendererRef = nullptr;

	//Debug Vars
	m_TestAnim1 = nullptr;
	m_TestAnim2 = nullptr;
	m_TestAnim3 = nullptr;
	m_TestAnim4 = nullptr;
	m_TestAnim5 = nullptr;
	m_TestAnim6 = nullptr;
	m_TestAnim7 = nullptr;
	m_TestAnim8 = nullptr;
	m_TestAnim9 = nullptr;
	m_TestAnim10 = nullptr;
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

	//Debug
	AnimationParams SheildAnimParams(24, 12, 11, 64, 64);
	AnimationParams EngineAnimParams(24, 4, 3, 48, 48);
	AnimationParams AutoCannonAnimParams(24, 7, 6, 48, 48);
	AnimationParams AutoCannonProjectileAnimParams(24, 4, 3, 32, 32);
	AnimationParams BigSpaceGunAnimParams(24, 12, 11, 48, 48);
	AnimationParams BigSpaceGunProjectileAnimParams(24, 10, 9, 32, 32);


	m_TestAnim1 = new Animation();
	m_TestAnim1->CreateAnimation("Content/Sprites/Main Ship/Main Ship - Bases/PNGs/Main Ship - Base - Full health.png");

	m_TestAnim1->SetPosition(640.0f, 360.0f);
	m_TestAnim1->SetScale(1.25f);

	m_TestAnim2 = new Animation();
	m_TestAnim2->CreateAnimation("Content/Sprites/Main Ship/Main Ship - Engines/PNGs/Main Ship - Engines - Big Pulse Engine.png");

	m_TestAnim2->SetPosition(640.0f, 370.0f);

	m_TestAnim3 = new Animation();
	m_TestAnim3->CreateAnimation("Content/Sprites/Main Ship/Main Ship - Weapons/PNGs/Main Ship - Weapons - Auto Cannon.png",
		&AutoCannonAnimParams);

	m_TestAnim3->SetPosition(640.0f, 350.0f);
	m_TestAnim3->SetScale(1.25f);

	m_TestAnim4 = new Animation();
	m_TestAnim4->CreateAnimation("Content/Sprites/Main Ship/Main Ship - Weapons/PNGs/Main Ship - Weapons - Big Space Gun.png",
		&BigSpaceGunAnimParams);

	m_TestAnim4->SetPosition(600.0f, 370.0f);
	m_TestAnim4->SetScale(1.25f);

	m_TestAnim5 = new Animation();
	m_TestAnim5->CreateAnimation("Content/Sprites/Main Ship/Main Ship - Weapons/PNGs/Main Ship - Weapons - Big Space Gun.png",
		&BigSpaceGunAnimParams);

	m_TestAnim5->SetPosition(680.0f, 370.0f);
	m_TestAnim5->SetScale(1.25f);

	m_TestAnim6 = new Animation();
	m_TestAnim6->CreateAnimation("Content/Sprites/Main ship weapons/PNGs/Main ship weapon - Projectile - Big Space Gun.png",
		&BigSpaceGunProjectileAnimParams);

	m_TestAnim6->SetPosition(680.0f, 330.0f);
	m_TestAnim6->SetScale(1.25f);

	m_TestAnim7 = new Animation();
	m_TestAnim7->CreateAnimation("Content/Sprites/Main ship weapons/PNGs/Main ship weapon - Projectile - Big Space Gun.png",
		&BigSpaceGunProjectileAnimParams);

	m_TestAnim7->SetPosition(600.0f, 330.0f);
	m_TestAnim7->SetScale(1.25f);

	m_TestAnim8 = new Animation();
	m_TestAnim8->CreateAnimation("Content/Sprites/Main ship weapons/PNGs/Main ship weapon - Projectile - Auto cannon bullet.png",
		&AutoCannonProjectileAnimParams);

	m_TestAnim8->SetPosition(640.0f, 300.0f);
	m_TestAnim8->SetScale(1.25f);

	m_TestAnim9 = new Animation();
	m_TestAnim9->CreateAnimation("Content/Sprites/Main Ship/Main Ship - Shields/PNGs/Main Ship - Shields - Round Shield.png",
		&SheildAnimParams);

	m_TestAnim9->SetPosition(640.0f, 360.0f);

	m_TestAnim10 = new Animation();
	m_TestAnim10->CreateAnimation("Content/Sprites/Main Ship/Main Ship - Engine Effects/PNGs/Main Ship - Engines - Big Pulse Engine - Powering.png",
		&EngineAnimParams);

	m_TestAnim10->SetPosition(640.0f, 370.0f);


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

void Game::ProcessInput()
{
	//data type to read STL input events for the window
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

	static float i = 0.0f;
	i += 0.1f;

	//TODO: update game logic
	if (m_TestAnim1 != nullptr) {
		m_TestAnim1->SetPosition(640, 360 - i);
	}
	if (m_TestAnim2 != nullptr) {
		m_TestAnim2->SetPosition(640, 370 - i);
	}
	if (m_TestAnim3 != nullptr) {
		m_TestAnim3->Update((float)DeltaTime);
		m_TestAnim3->SetPosition(640, 350 - i);
	}
	if (m_TestAnim4 != nullptr) {
		m_TestAnim4->Update((float)DeltaTime);
		m_TestAnim4->SetPosition(600, 370 - i);
	}
	if (m_TestAnim5 != nullptr) {
		m_TestAnim5->Update((float)DeltaTime);
		m_TestAnim5->SetPosition(680, 370 - i);
	}
	if (m_TestAnim6 != nullptr) {
		m_TestAnim6->Update((float)DeltaTime);
		m_TestAnim6->SetPosition(680, 330 - 5 * i);
	}
	if (m_TestAnim7 != nullptr) {
		m_TestAnim7->Update((float)DeltaTime);
		m_TestAnim7->SetPosition(600, 330 - 5 * i);
	}
	if (m_TestAnim8 != nullptr) {
		m_TestAnim8->Update((float)DeltaTime);
		m_TestAnim8->SetPosition(640, 300 - 5 * i);
	}
	if (m_TestAnim9 != nullptr) {
		m_TestAnim9->Update((float)DeltaTime);
		m_TestAnim9->SetPosition(640, 360 - i);
	}
	if (m_TestAnim10 != nullptr) {
		m_TestAnim10->Update((float)DeltaTime);
		m_TestAnim10->SetPosition(640, 370 - i);
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
}
