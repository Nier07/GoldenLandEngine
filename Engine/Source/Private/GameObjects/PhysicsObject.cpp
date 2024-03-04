#include "GameObjects/PhysicsObject.h"

void PhysicsObject::OnStart()
{
	SetPosition({ 640.0f, 360.0f });

	AnimationParams SheildAnimParams(24, 12, 11, 64, 64);

	m_Sprite = AddSprite("Content/Sprites/Main Ship/Main Ship - Shields/PNGs/Main Ship - Shields - Round Shield.png",
	&SheildAnimParams);
}

void PhysicsObject::OnProcessInput(Input* GameInput)
{

}

void PhysicsObject::OnUpdate(float DeltaTime)
{
	if (m_Sprite != nullptr) {
		m_Sprite->Update(DeltaTime);
	}
}
