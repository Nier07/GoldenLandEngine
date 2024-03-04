#include "Graphics/Animation.h"
#include "Debug.h"
#include "Game.h"
#include "Graphics/Texture.h"

Animation::Animation()
{
	m_TextureRef = nullptr;
	m_AnimParams = nullptr;
	m_CurrentFrame = 0;
	m_FrameTimer = 0.0f;
}

Animation::~Animation()
{
	if (m_AnimParams != nullptr) {
		delete m_AnimParams;
	}

	if (m_TextureRef != nullptr) {
		Game::GetGame()->DestroyTexture(m_TextureRef);
	}
}

bool Animation::CreateAnimation(const char* PathToFile, AnimationParams* Params)
{
	m_TextureRef = Game::GetGame()->ImportTexture(PathToFile);

	//if import failed
	if (m_TextureRef == nullptr) {
		GL_LOG("Animation", "Animation failed to import texture: " << PathToFile);
		return false;
	}

	//set params
	m_AnimParams = new AnimationParams();
	m_AnimParams->EndFrame = Params->EndFrame;
	m_AnimParams->fps = Params->fps;
	m_AnimParams->FrameHeight = Params->FrameHeight;
	m_AnimParams->FrameWidth = Params->FrameWidth;
	m_AnimParams->MaxFrames = Params->MaxFrames;
	m_AnimParams->StartFrame = Params->StartFrame;

	//if animation params were set
	if (m_AnimParams != nullptr) {
		m_CurrentFrame = m_AnimParams->StartFrame;

		//update the clip to start on first frame
		m_TextureRef->SetClip(
			m_AnimParams->FrameWidth * m_CurrentFrame,
			0,
			m_AnimParams->FrameWidth,
			m_AnimParams->FrameHeight
		);
	}

	return true;
}

void Animation::Update(float DeltaTime)
{
	if (m_AnimParams == nullptr || m_AnimParams->fps == 0.0f) {
		return;
	}

	//increase frame timer each frame to get time passed
	m_FrameTimer += DeltaTime;

	//check the frame timer has reached the time to update to next frame
	if (m_FrameTimer >= 1.0f / m_AnimParams->fps) {
		m_CurrentFrame++;

		if (m_CurrentFrame > m_AnimParams->EndFrame) {
			m_CurrentFrame = 0;
		}

		//update the clip to start on next frame
		m_TextureRef->SetClip(
			m_AnimParams->FrameWidth * m_CurrentFrame,
			0,
			m_AnimParams->FrameWidth,
			m_AnimParams->FrameHeight
		);

		//reset timer for the next frame
		m_FrameTimer = 0.0f;
	}
}

void Animation::SetPosition(int x, int y)
{
	if (m_TextureRef == nullptr) {
		return;

	}

	m_TextureRef->m_PosX = x;
	m_TextureRef->m_PosY = y;
}

void Animation::SetRotation(float Angle)
{
	if (m_TextureRef == nullptr) {
		return;
	}

	m_TextureRef->m_Angle = Angle;
}

void Animation::SetScale(float x, float y)
{
	if (m_TextureRef == nullptr) {
		return;
	}

	m_TextureRef->m_ScaleX = x;
	m_TextureRef->m_ScaleY = y;
}
