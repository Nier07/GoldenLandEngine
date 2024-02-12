#pragma once

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;

class Texture {
public:
	Texture(SDL_Renderer* Renderer);
	~Texture() = default;
	
	// import and create a texture
	bool ImportTexture(const char* PathToFile);

	// draw the texture to the renderer
	void Draw();

	//deallocate memory
	void CleanUp();

	//get original image path
	const char* GetPath() const { return m_Path; }

	// position to render to
	int m_PosX, m_PosY;

	// rotation of image
	float m_Angle;

	float m_Scale;

private:
	// texture that SDL understands
	SDL_Texture* m_TextureRef;

	// store assigned renderer
	SDL_Renderer* m_RendererRef;

	// surface data for original image
	SDL_Surface* m_SurfaceData;

	// path to original image
	const char* m_Path;
};