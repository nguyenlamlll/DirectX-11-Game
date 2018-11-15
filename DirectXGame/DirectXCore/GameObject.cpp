#include "stdafx.h"
#include "GameObject.h"

using namespace DirectXCore;

DirectXCore::GameObject::GameObject()
{
	transform = new Transform(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	componentList = new std::vector<Component*>();
}

void DirectXCore::GameObject::Update()
{
	Vector3* colliderCenter = new Vector3(transform->GetPosition().x + transform->GetScale().x, transform->GetPosition().y + transform->GetScale().y, 1);
	Rigidbody *rigidBody = GetComponent<Rigidbody>();
	if (rigidBody) GetTransform()->SetPosition(GetTransform()->GetPosition()+rigidBody->GetVelocity());
	Collider *collider = GetComponent<Collider>();
	/*if (collider)
	{
		collider->SetColliderTransform(transform);
	}*/
	for (size_t i = 0; i < componentList->size(); i++)
	{
		componentList->at(i)->Update();
	}
}

void DirectXCore::GameObject::Render()
{

}

void DirectXCore::GameObject::OnCollisionEnter()
{
	//transform->SetPosition(transform->GetPosition());
}

DirectXCore::GameObject::~GameObject()
{
}

void DirectXCore::GameObject::ReferenceGameObject()
{
	for (size_t i = 0; i < componentList->size(); i++)
	{
		componentList->at(i)->SetAttachedGameObject(this);
	}
}
