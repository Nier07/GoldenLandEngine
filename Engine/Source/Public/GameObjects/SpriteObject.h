#pragma once
#include "GameObjects/GameObject.h"
#include "Graphics/Animation.h"


class SpriteObject : public GameObject{
public:
	SpriteObject() = default;
	virtual ~SpriteObject() = default;

	virtual void CleanUp() override;

protected:
	//add animation/sprite to sprite stack
	Animation* AddSprite(const char* PathToFile, AnimationParams* Params = nullptr);

	virtual void OnPostUpdate(float DeltaTime) override;

private:
	//store all sprites related to this object
	TArray<Animation*> m_SpriteStack;


};