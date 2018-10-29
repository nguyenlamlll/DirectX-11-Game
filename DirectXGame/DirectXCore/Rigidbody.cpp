#include "stdafx.h"
#include "Rigidbody.h"
#include "GameObject.h"
using namespace DirectXCore;

Rigidbody::Rigidbody()
{
	position = SimpleMath::Vector3(0, 0, 0);
	velocity = SimpleMath::Vector3(0, 0, 0);
	force = SimpleMath::Vector3(0, 0, 0);
	impulse = SimpleMath::Vector3(0, 0, 0);
	mass = SimpleMath::Vector3(1, 1, 1);
	kinematic = false;
}

DirectXCore::Rigidbody::Rigidbody(GameObject * _gameObject)
{
	if (!attachedGameObject) attachedGameObject = _gameObject;
	position = SimpleMath::Vector3(0, 0, 0);
	velocity = SimpleMath::Vector3(0, 0, 0);
	force = SimpleMath::Vector3(0, 0, 0);
	impulse = SimpleMath::Vector3(0, 0, 0);
	mass = SimpleMath::Vector3(1, 1, 1);
	kinematic = false;
}

void DirectXCore::Rigidbody::Update()
{
	OnPhysicUpdate(0.6);
	if (!kinematic && attachedGameObject)attachedGameObject->GetTransform()->SetPosition(attachedGameObject->GetTransform()->GetPosition() + GetVelocity());
}

void DirectXCore::Rigidbody::MovePosition(SimpleMath::Vector3 _newPosition)
{
	position += _newPosition;
}

void DirectXCore::Rigidbody::Move(SimpleMath::Vector3 _velocity, float _deltaTime)
{
	//velocity = _velocity;
	velocity.x = _velocity.x / GetMass().x*_deltaTime;
	velocity.y = _velocity.y / GetMass().y*_deltaTime;
	velocity.z = _velocity.z / GetMass().z*_deltaTime;
}


Rigidbody::~Rigidbody()
{
}

void DirectXCore::Rigidbody::OnPhysicUpdate(float _delta)
{
	velocity += gravity;
	position += velocity * _delta;
}
