#include "GameObjects/SpriteObject.h"

void SpriteObject::CleanUp()
{
	for (auto Sprite : m_SpriteStack) {
		delete Sprite;
		Sprite = nullptr;
	}
}

Animation* SpriteObject::AddSprite(const char* PathToFile, AnimationParams* Params)
{
	Animation* NewAnim = new Animation();

	if (!NewAnim->CreateAnimation(PathToFile, Params)) {
		return nullptr;
	}

	m_SpriteStack.push_back(NewAnim);

	//set the sprite position to match the objects
	NewAnim->SetPosition((int)GetTransform().Position.x, (int)GetTransform().Position.y);
	//set the sprite rotation to match the objects
	NewAnim->SetRotation(GetTransform().Rotation);
	//set the sprites scale to match the object
	NewAnim->SetScale(GetTransform().Scale.x, GetTransform().Scale.y);

	return NewAnim;
}

void SpriteObject::OnPostUpdate(float DeltaTime)
{
	// loop through each sprite and set it to match the objects tranform
	for(auto Sprite : m_SpriteStack) {
		if (Sprite == nullptr) {
			continue;
		}

		//set the sprite position to match the objects
		Sprite->SetPosition((int)GetTransform().Position.x, (int)GetTransform().Position.y);
		//set the sprite rotation to match the objects
		Sprite->SetRotation(GetTransform().Rotation);
		//set the sprites scale to match the object
		Sprite->SetScale(GetTransform().Scale.x, GetTransform().Scale.y);
	}
}
