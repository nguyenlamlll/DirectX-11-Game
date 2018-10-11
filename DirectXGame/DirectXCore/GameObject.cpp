#include "stdafx.h"
#include "GameObject.h"

using namespace DirectXCore;

GameObject::GameObject()
{
	transform = new Transform(Vector2(0, 0), Vector2(0, 0), Vector2(1, 1));
	boxCollider = new BoundingBox();
}

void DirectXCore::GameObject::Update()
{
	Vector2* colliderCenter = new Vector2(transform->GetPosition().x + transform->GetScale().x / 2, transform->GetPosition().y + transform->GetScale().y / 2);
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
