#include "stdafx.h"
#include "GameObject.h"

using namespace DirectXCore;

GameObject::GameObject()
{
	transform = new Transform(Vector3(0, 0, 1), Vector3(0, 0, 1), Vector3(1, 1, 1));
	boxCollider = new BoundingBox();
}

void DirectXCore::GameObject::Update()
{
	Vector3* colliderCenter = new Vector3(transform->GetPosition().x + transform->GetScale().x / 2, transform->GetPosition().y + transform->GetScale().y / 2, 1);
	boxCollider->Center = Vector3(colliderCenter->x, colliderCenter->y, 1);
	boxCollider->Extents = Vector3(transform->GetScale().x / 2, transform->GetScale().y / 2, 1);
}


void DirectXCore::GameObject::OnCollisionEnter()
{
	//transform->SetPosition(transform->GetPosition());
}

GameObject::~GameObject()
{
}
