#pragma once
#include "GameObjects/SpriteObject.h"

class PhysicsObject : public SpriteObject {
public:
	PhysicsObject() : m_Sprite(nullptr) {}
	~PhysicsObject() = default;

protected:
	virtual void OnStart() override;

	virtual void OnProcessInput(Input* GameInput) override;

	virtual void OnUpdate(float DeltaTime) override;

private:
	Animation* m_Sprite;
};