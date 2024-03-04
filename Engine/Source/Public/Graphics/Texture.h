#pragma once

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
struct SDL_Rect;

class Texture {
public:
	Texture(SDL_Renderer* Renderer);
	~Texture();
	
	// import and create a texture
	bool ImportTexture(const char* PathToFile);

	void CopyTexture(Texture* CopyTexture);

	// draw the texture to the renderer
	void Draw();

	// deallocate memory
	void CleanUp();

	// set clip for the texture
	void SetClip(int x, int y, int w, int h);

	//get original image path
	const char* GetPath() const { return m_Path; }

	// position to render to
	int m_PosX, m_PosY;

	// rotation of image
	float m_Angle;

	//scale the texture
	float m_ScaleX, m_ScaleY;

private:
	// texture that SDL understands
	SDL_Texture* m_TextureRef;

	// store assigned renderer
	SDL_Renderer* m_RendererRef;

	// surface data for original image
	SDL_Surface* m_SurfaceData;

	// path to original image
	const char* m_Path;

	//store clip for texture
	SDL_Rect* m_ClipRect;
};