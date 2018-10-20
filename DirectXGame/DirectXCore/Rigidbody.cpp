#include "stdafx.h"
#include "Rigidbody.h"
using namespace DirectXCore;

Rigidbody::Rigidbody()
{
}

void DirectXCore::Rigidbody::Update()
{
	OnPhysicUpdate(0.6);
}

void DirectXCore::Rigidbody::MovePosition(SimpleMath::Vector3 _newPosition)
{
	position += _newPosition;
}

void DirectXCore::Rigidbody::Move(SimpleMath::Vector3 _velocity)
{
	velocity += _velocity;
}


Rigidbody::~Rigidbody()
{
}

void DirectXCore::Rigidbody::OnPhysicUpdate(float _delta)
{
	velocity += gravity;
	position += velocity * _delta;
}
