#pragma once

class Texture;

struct AnimationParams {
	AnimationParams() {
		FrameWidth = FrameHeight = 0;
		fps = 0.0f;
		StartFrame = EndFrame = 0;
		MaxFrames = 0;
	}

	//sets animation parameters so i dont have to repeat the decleration over and over
	AnimationParams(float fps, unsigned int MaxFrames, unsigned int EndFrame, unsigned int FrameWidth, unsigned int FrameHeight) {
		this->fps = fps;
		this->MaxFrames = MaxFrames;
		this->EndFrame = EndFrame;
		this->FrameWidth = FrameWidth;
		this->FrameHeight = FrameHeight;
	}

	// width / height of each frame
	unsigned int FrameWidth, FrameHeight;

	// frames per second
	float fps;

	// start and end frame that animation will play
	unsigned int StartFrame, EndFrame;

	//amount of frames in the sprite
	unsigned int MaxFrames;
};

class Animation {
public:
	Animation();
	~Animation();

	//import animation and add animation params
	bool CreateAnimation(const char* PathToFile, AnimationParams* Params = nullptr);

	//update anim logic each frame
	void Update(float DeltaTime);

	void SetPosition(int x, int y);

	void SetRotation(float Angle);

	void SetScale(float Scale);

private:
	// stores the texture to render
	Texture* m_TextureRef;

	//store animation data
	AnimationParams* m_AnimParams;
	
	//current playing frame of animation
	unsigned int m_CurrentFrame;

	//how much time has passed since the last animation frame
	float m_FrameTimer;
};