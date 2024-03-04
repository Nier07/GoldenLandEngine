#include "Graphics/Texture.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Debug.h"

Texture::Texture(SDL_Renderer* Renderer)
{
	m_RendererRef = Renderer;
	m_Angle = 0.0f;
	m_Path = "";
	m_PosX = m_PosY = 0;
	m_SurfaceData = nullptr;
	m_TextureRef = nullptr;
	m_ScaleX = m_ScaleY = 1.0f;
	m_ClipRect = nullptr;
}

Texture::~Texture()
{
	if (m_ClipRect != nullptr) {
		delete m_ClipRect;
	}
}

bool Texture::ImportTexture(const char* PathToFile)
{
	//store path to file
	m_Path = PathToFile;
	//import image and convert to surface
	//fill object with data for image
	m_SurfaceData = IMG_Load(PathToFile);

	//did import fail
	if (m_SurfaceData == nullptr) {
		GL_LOG("Texture", "Image failed to import: " << SDL_GetError());
		return false;
	}

	//create texture from surface
	m_TextureRef = SDL_CreateTextureFromSurface(m_RendererRef, m_SurfaceData);

	//did conversion fail
	if (m_TextureRef == nullptr) {
		GL_LOG("Texture", "Image failed to convert to texture: " << SDL_GetError());

		CleanUp();
		return false;
	}

	GL_LOG("Texture", "Successfully imported texture: " << m_Path);

	return true;
}

void Texture::CopyTexture(Texture* CopyTexture)
{
	m_Path = CopyTexture->m_Path;
	m_SurfaceData = CopyTexture->m_SurfaceData;
	m_TextureRef = CopyTexture->m_TextureRef;
}

void Texture::Draw()
{
	float ImageWidth = (float)m_SurfaceData->w;
	float ImageHeight = (float)m_SurfaceData->h;

	SDL_FRect DestRect = {
		(float)m_PosX, (float)m_PosY,
		ImageWidth * m_ScaleX, ImageHeight * m_ScaleY
	};

	//if there is a set clip then update the w and h of texture
	if (m_ClipRect != nullptr) {
		DestRect.w = m_ClipRect->w * m_ScaleX;
		DestRect.h = m_ClipRect->h * m_ScaleY;
	}

	// move texture to be centered at middle point of image
	DestRect.x -= DestRect.w / 2;
	DestRect.y -= DestRect.h / 2;

	SDL_FPoint Center{
		DestRect.w / 2,
		DestRect.h / 2
	};

	SDL_RenderCopyExF(
		m_RendererRef, // renderer to draw to
		m_TextureRef, // texture to draw to renderer
		m_ClipRect, // clip rect
		&DestRect, // pos and scale on screen 
		m_Angle, // rotation of texture
		&Center, // center point for rotation
		SDL_FLIP_NONE); // flip texture vertical/horizontal
}

void Texture::CleanUp()
{
	if (m_SurfaceData != nullptr) {
		SDL_FreeSurface(m_SurfaceData);
	}

	if (m_TextureRef != nullptr) {
		SDL_DestroyTexture(m_TextureRef);
	}

	GL_LOG("Texture", "Sucessfully destroyed image: " << m_Path);
}

void Texture::SetClip(int x, int y, int w, int h)
{
	if (m_ClipRect == nullptr) {
		//create sdl rect object
		m_ClipRect = new SDL_Rect();
	}

	//set the rect values
	m_ClipRect->x = x;
	m_ClipRect->y = y;
	m_ClipRect->w = w;
	m_ClipRect->h = h;
}
