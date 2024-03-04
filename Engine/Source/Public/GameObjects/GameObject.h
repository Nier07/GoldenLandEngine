#pragma once
#include "Math/Vector2.h"
#include "EngineTypes.h"

class Input;

struct GLTransform {
	//default constructor
	GLTransform() : Position(0.0f), Rotation(0.0f), Scale(1.0f) {}

	//assignment constructor
	GLTransform(Vector2 Position, float Rotation, Vector2 Scale) : 
		Position(Position), Rotation(Rotation), Scale(Scale) {}

	//transform constructor
	GLTransform(const GLTransform& Other) :

		Position(Other.Position), Rotation(Other.Rotation), Scale(Other.Scale) {}

	Vector2 Position;
	float Rotation;
	Vector2 Scale;
};

class GameObject {
public:
	GameObject() : m_ShouldDestroy(false) {}
	virtual ~GameObject() = default;

	// when object spawns into the game this will run
	virtual void Start();

	// listen for input events
	void ProcessInput(Input* GameInput);

	// runs every frame
	void Update(float DeltaTime);
	
	// runs every frame after the update
	virtual void PostUpdate(float DeltaTime);

	// destory game object
	void DestroyObject();

	// is the object pending to destroy at the end of gameloop
	bool isPendingDestroy() const { return m_ShouldDestroy; }

	//remove any memory references
	virtual void CleanUp() {}

	
	//get the transform of the game object
	GLTransform GetTransform() const { return m_Transform;  }

	//set the transform of game object
	virtual void SetTransform(GLTransform Transform);

	//set position of object
	void SetPosition(Vector2 Position);

	//set rotation angle of object
	void SetRotation(float Rotation);

	//set the scale of object
	void SetScale(Vector2 Scale);

protected: 
	//run when game object has been marked for destruction
	virtual void OnDestroy();

	//runs when the game object spawns
	virtual void OnStart() {}

	//run on game objects process input (before update each frame);
	virtual void OnProcessInput(Input* GameInput) {}

	//run on the game objects update (each frame)
	virtual void OnUpdate(float DeltaTime) {}

	//run on the game objects post update (each frame after update)
	virtual void OnPostUpdate(float DeltaTime) {}

private:
	//determine if an object should be destroyed at the end of loop
	bool m_ShouldDestroy;

	//store the transform for the game object
	GLTransform m_Transform;
};