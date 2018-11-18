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
	for (size_t i = 0; i < componentList->size(); i++)
	{
		componentList->at(i)->Update();
	}
}

void DirectXCore::GameObject::Render()
{
	for (size_t i = 0; i < componentList->size(); i++)
	{
		componentList->at(i)->Render();
	}
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
