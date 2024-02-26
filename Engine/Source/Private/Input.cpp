#include "Input.h"
#include "SDL2/SDL.h"
#include "Game.h"
#include "Math/Vector2.h"

void Input::ProcessInput()
{
	//data type to read STL input events for the window
	SDL_Event InputEvent;

	//run through each input in the frame
	while (SDL_PollEvent(&InputEvent)) {
		// was the input a moust button and is it pressed down
		if (InputEvent.type == SDL_MOUSEBUTTONDOWN) {
			DetectMouseButtonState(InputEvent.button.button, true);
		}
		
		// was the input a mouse button and was it released
		if (InputEvent.type == SDL_MOUSEBUTTONUP) {
			DetectMouseButtonState(InputEvent.button.button, false);
		}

		//when x is pressed close the app
		if (InputEvent.type == SDL_QUIT) {
			Game::GetGame()->QuitApp();
		}
	}
}

bool Input::IsKeyDown(GL_Key Key)
{
	const Uint8* KeyStates = SDL_GetKeyboardState(NULL);

	if (KeyStates == nullptr) {
		return false;
	}

	return KeyStates[Key];
}

bool Input::IsMouseButtonDown(GL_MouseButton Button)
{
	if (Button >= GL_MOUSE_BUTTONS) {
		return false;
	}

	return m_MouseState[Button];
}

Vector2 Input::GetMousePosition() const
{
	int x = 0;
	int y = 0;

	// changes x and y to the location of the mouse
	SDL_GetMouseState(&x, &y);

	return Vector2((float) x, (float) y);
}

void Input::DetectMouseButtonState(unsigned int Event, bool Value)
{
	switch (Event) {
	case SDL_BUTTON_LEFT :
		m_MouseState[GL_MOUSE_LEFT] = Value;
		break;
	case SDL_BUTTON_MIDDLE :
		m_MouseState[GL_MOUSE_MIDDLE] = Value;
		break;
	case SDL_BUTTON_RIGHT :
		m_MouseState[GL_MOUSE_RIGHT] = Value;
		break;
	default:
		break;
	}
}
