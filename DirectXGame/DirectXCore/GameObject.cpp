#include "stdafx.h"
#include "GameObject.h"

using namespace DirectXCore;

DirectXCore::GameObject::GameObject()
{
	transform = new Transform(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	componentList = new std::vector<Component*>();
	childrens = new std::vector<GameObject*>();
	parent = nullptr;
}

DirectXCore::GameObject::GameObject(GameObject * _parent)
{
	transform = new Transform(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	componentList = new std::vector<Component*>();
	childrens = new std::vector<GameObject*>();
	parent = _parent;
}

void DirectXCore::GameObject::PreUpdate(float _deltaTime)
{
	for (size_t i = 0; i < componentList->size(); i++)
	{
		componentList->at(i)->PreUpdate(_deltaTime);
	}
	for (size_t i = 0; i < childrens->size(); i++)
	{
		childrens->at(i)->PreUpdate(_deltaTime);
	}
}

void DirectXCore::GameObject::Update(float _deltaTime)
{
	for (size_t i = 0; i < componentList->size(); i++)
	{
		componentList->at(i)->Update(_deltaTime);
	}
	for (size_t i = 0; i < childrens->size(); i++)
	{
		childrens->at(i)->Update(_deltaTime);
	}
}

void DirectXCore::GameObject::LateUpdate(float _deltaTime)
{
	for (size_t i = 0; i < componentList->size(); i++)
	{
		componentList->at(i)->LateUpdate(_deltaTime);
	}
	for (size_t i = 0; i < childrens->size(); i++)
	{
		childrens->at(i)->LateUpdate(_deltaTime);
	}
}

void DirectXCore::GameObject::Render()
{
	for (size_t i = 0; i < childrens->size(); i++)
	{
		childrens->at(i)->Render();
	}
	for (size_t i = 0; i < componentList->size(); i++)
	{
		componentList->at(i)->Render();
	}
}

void DirectXCore::GameObject::OnCollisionEnter(Collider* _other, Vector3 _normal)
{
	if (this->GetComponent<Rigidbody>())
	{
		if (this->GetComponent<Collider>())
		{
			this->GetComponent<Collider>()->SetCollisionStatus(true);
			if (!this->GetComponent<Collider>()->IsTrigger() && !_other->IsTrigger())
			{
				if (!this->GetComponent<Rigidbody>()->IsKinematic())
				{
					if (_normal.y < 0)
					{
						if (this->GetComponent<Rigidbody>()->GetVelocity().y > 0)
						{
							Vector3 vec = this->GetComponent<Rigidbody>()->GetVelocity();
							vec.y *= -1;
							this->GetComponent<Rigidbody>()->SetVelocity(this->GetComponent<Rigidbody>()->GetVelocity() + vec);
						}
						if (this->GetComponent<Rigidbody>()->GetAcceleration().y > 0)
						{
							Vector3 acc = this->GetComponent<Rigidbody>()->GetAcceleration();
							acc.y *= -1;
							this->GetComponent<Rigidbody>()->AddForce(acc);
						}
					}
					if (_normal.x != 0)
					{
						Vector3 vec = this->GetComponent<Rigidbody>()->GetVelocity();
						vec.x = vec.x + vec.x*-1;
						this->GetComponent<Rigidbody>()->SetVelocity(vec);
					}
				}
			}
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
