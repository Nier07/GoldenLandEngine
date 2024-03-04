#include "GameObjects/GameObject.h"
#include "Debug.h"

void GameObject::Start()
{
	if (isPendingDestroy()) {
		return;
	}

	GL_LOG("GameObject", "GameObject has spawned into the game");

	OnStart();
}

void GameObject::ProcessInput(Input* GameInput)
{
	if (isPendingDestroy()) {
		return;
	}

	OnProcessInput(GameInput);
}

void GameObject::Update(float DeltaTime)
{
	if (isPendingDestroy()) {
		return;
	}

	OnUpdate(DeltaTime);
}

void GameObject::PostUpdate(float DeltaTime)
{
	if (isPendingDestroy()) {
		return;
	}

	OnPostUpdate(DeltaTime);
}

void GameObject::DestroyObject()
{
	//ensure the OnDestroy only runs once
	if (!m_ShouldDestroy) {
		OnDestroy();
	}

	m_ShouldDestroy = true;
}

void GameObject::SetTransform(GLTransform Transform)
{
	m_Transform = Transform;
}

void GameObject::SetPosition(Vector2 Position)
{
	GLTransform NewTransform(
		Position,
		m_Transform.Rotation,
		m_Transform.Scale
	);

	SetTransform(NewTransform);
}

void GameObject::SetRotation(float Rotation)
{
	GLTransform NewTransform(
		m_Transform.Position,
		Rotation,
		m_Transform.Scale
	);

	SetTransform(NewTransform);
}

void GameObject::SetScale(Vector2 Scale)
{
	GLTransform NewTransform(
		m_Transform.Position, 
		m_Transform.Rotation,
		Scale
	);

	SetTransform(NewTransform);
}

void GameObject::OnDestroy()
{
	GL_LOG("GameObject", "GameObject has been destroyed");
}
