#include "stdafx.h"
#include "Rigidbody.h"
#include "GameObject.h"
using namespace DirectXCore;

Rigidbody::Rigidbody()
{
	move = SimpleMath::Vector3(0, 0, 0);
	position = SimpleMath::Vector3(0, 0, 0);
	velocity = SimpleMath::Vector3(0, 0, 0);
	force = SimpleMath::Vector3(0, 0, 0);
	impulse = SimpleMath::Vector3(0, 0, 0);
	mass = SimpleMath::Vector3(1, 1, 1);
	acceleration = SimpleMath::Vector3(0, 0, 0);
	kinematic = false;
}

DirectXCore::Rigidbody::Rigidbody(GameObject * _gameObject)
{
	if (!attachedGameObject) attachedGameObject = _gameObject;
	position = SimpleMath::Vector3(0, 0, 0);
	velocity = SimpleMath::Vector3(0, 0, 0);
	acceleration = SimpleMath::Vector3(0, 0, 0);
	force = SimpleMath::Vector3(0, 0, 0);
	impulse = SimpleMath::Vector3(0, 0, 0);
	mass = SimpleMath::Vector3(1, 1, 1);
	kinematic = false;
}

void DirectXCore::Rigidbody::PreUpdate(float _deltaTime)
{
	//const float physicTimeStep = 1.0f / 60.0f;
	//accumulatedTime += _deltaTime;
	//while (accumulatedTime >= physicTimeStep)
	//{
	//	accumulatedTime -= physicTimeStep;
	//	OnPhysicUpdate(accumulatedTime);
	//}
	AddForce(gravity);
}

void DirectXCore::Rigidbody::Update(float _deltaTime)
{
	velocity = acceleration + move;
	//velocity += move;
}

void DirectXCore::Rigidbody::LateUpdate(float _deltaTime)
{
	if (!kinematic && attachedGameObject)
		attachedGameObject->GetTransform()->SetPosition(attachedGameObject->GetTransform()->GetPosition() + (velocity)*_deltaTime);
	move = SimpleMath::Vector3(0, 0, 0);
}

void DirectXCore::Rigidbody::MovePosition(SimpleMath::Vector3 _newPosition)
{
	position += _newPosition;
}

void DirectXCore::Rigidbody::Move(SimpleMath::Vector3 _velocity)
{
	/*if (move.x == 0) move.x = _velocity.x;
	if (move.y == 0) move.y = _velocity.y;
	if (move.z == 0) move.z = _velocity.z;*/
	move = _velocity;
}

void DirectXCore::Rigidbody::AddForce(SimpleMath::Vector3 _force)
{
	acceleration += _force;
	//force = _force;
}


Rigidbody::~Rigidbody()
{
}

void DirectXCore::Rigidbody::OnPhysicUpdate(float _delta)
{
	
}

