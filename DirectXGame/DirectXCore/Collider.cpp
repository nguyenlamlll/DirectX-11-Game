#include "stdafx.h"
#include "Collider.h"
#include "GameObject.h"

using namespace DirectXCore;

Collider::Collider()
{
}
DirectXCore::Collider::Collider(GameObject * _attachedGameObject, Transform* _gameObjectTransform)
{
	attachedGameObject = _attachedGameObject;
	collider = new BoundingBox(_gameObjectTransform->GetPosition(), _gameObjectTransform->GetScale());
	SetColliderTransform(_gameObjectTransform);
}
DirectXCore::Collider::Collider(GameObject * _attachedGameObject, Vector3 _pos, Vector3 _rot, Vector3 _scl)
{
	attachedGameObject = _attachedGameObject;
}
void DirectXCore::Collider::PreUpdate(float _deltaTime)
{
}
void DirectXCore::Collider::Update(float _deltaTime)
{
	//if (attachedGameObject) SetColliderTransform(attachedGameObject->GetTransform());
}
void DirectXCore::Collider::LateUpdate(float _deltaTime)
{
	if (attachedGameObject) SetColliderTransform(attachedGameObject->GetTransform());
}
void DirectXCore::Collider::SetColliderPosition(Vector3 _newPosition)
{
	collider->Center.x = _newPosition.x;
	collider->Center.y = _newPosition.y;
	collider->Center.z = _newPosition.z;
}
void DirectXCore::Collider::SetColliderScale(Vector3 _newScale)
{
	collider->Extents.x = _newScale.x / 2;
	collider->Extents.y = _newScale.y / 2;
	collider->Extents.z = _newScale.z;
}
void DirectXCore::Collider::SetColliderTransform(Transform* _newTransform)
{
	SetColliderScale(_newTransform->GetScale());
	SetColliderPosition(_newTransform->GetPosition());
}
void DirectXCore::Collider::OnCollisionEnter(Collider * _other, SimpleMath::Vector3 _normal)
{
	
}
Collider::~Collider()
{
}