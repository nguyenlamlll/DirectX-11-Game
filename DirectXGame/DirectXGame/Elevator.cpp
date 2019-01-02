#include "Elevator.h"



Elevator::Elevator()
{
}

Elevator::Elevator(std::shared_ptr<DirectXCore::DxBase> _m_dxBase)
{
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetPosition(Vector3(3590, 3810, 0));
	this->GetTransform()->SetScale(Vector3(200, 50, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->AddComponent<Animation>(new Animation(this->GetComponent<Renderer>(), 1, 11, 0.1f, 1.0f, true));
	this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/Elevator/elevator_1.png", 1, 3);
	this->SetTag("Elevator");
}

void Elevator::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void Elevator::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
}

void Elevator::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void Elevator::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
	GameObject::OnCollisionEnter(_other, _normal);
	if (_other->GetAttachedGameObject()->GetTag() == "Player")
	{
		if (this->GetTransform()->GetPosition().y > 1760)
		{
			this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + Vector3(0, -5.0f, 0));
			_other->GetAttachedGameObject()->GetTransform()->SetPosition(_other->GetAttachedGameObject()->GetTransform()->GetPosition() + Vector3(0, -5.0f, 0));
		}
	}
}


Elevator::~Elevator()
{
}
