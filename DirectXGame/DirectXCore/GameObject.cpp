#include "stdafx.h"
#include "GameObject.h"

using namespace DirectXCore;

DirectXCore::GameObject::GameObject()
{
	transform = new Transform(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	componentList = new std::vector<Component*>();
}

void DirectXCore::GameObject::PreUpdate(float _deltaTime)
{
	for (size_t i = 0; i < componentList->size(); i++)
	{
		componentList->at(i)->PreUpdate(_deltaTime);
	}
}

void DirectXCore::GameObject::Update(float _deltaTime)
{
	for (size_t i = 0; i < componentList->size(); i++)
	{
		componentList->at(i)->Update(_deltaTime);
	}
}

void DirectXCore::GameObject::LateUpdate(float _deltaTime)
{
	for (size_t i = 0; i < componentList->size(); i++)
	{
		componentList->at(i)->LateUpdate(_deltaTime);
	}
}

void DirectXCore::GameObject::Render()
{
	for (size_t i = 0; i < componentList->size(); i++)
	{
		componentList->at(i)->Render();
	}
}

void DirectXCore::GameObject::OnCollisionEnter(Collider* _other, Vector3 _normal)
{
	if (this->GetComponent<Rigidbody>())
	{
		if (!this->GetComponent<Rigidbody>()->IsKinematic())
		{
			this->GetComponent<Collider>()->SetCollisionStatus(true);
			Vector3 objectVec = this->GetComponent<Rigidbody>()->GetAcceleration();
			Vector3 velocityVec = this->GetComponent<Rigidbody>()->GetVelocity();
			Vector3 moveVec = this->GetComponent<Rigidbody>()->GetMovingVector();
			if (moveVec.x > 0)
			{
				if (_normal.x < 0) moveVec.x = 0;
			}
			else if (moveVec.x < 0)
			{
				if (_normal.x > 0) moveVec.x = 0;
			}
			objectVec.x = (_normal.x > 0) ? -objectVec.x : objectVec.x;
			velocityVec.x = (_normal.x > 0) ? -velocityVec.x : velocityVec.x;
			objectVec.y = (_normal.y > 0) ? -objectVec.y : objectVec.y;
			velocityVec.y = (_normal.y > 0) ? -velocityVec.y : velocityVec.y;
			Vector3 newVec = objectVec * _normal + this->GetComponent<Rigidbody>()->GetVelocity();
			this->GetComponent<Rigidbody>()->Move(moveVec);
			this->GetComponent<Rigidbody>()->AddForce(objectVec*_normal);
		}
	}
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
