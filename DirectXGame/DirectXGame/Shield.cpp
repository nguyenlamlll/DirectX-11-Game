#include "Shield.h"



Shield::Shield()
{
}

Shield::Shield(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, GameObject * _captain)
{
	m_dxBase = _m_dxBase;
	captain = _captain;
	this->GetTransform()->SetPosition(_captain->GetTransform()->GetPosition());
	this->GetTransform()->SetScale(Vector3(34, 40, 1));
	this->GetTransform()->SetScreenScale(Vector3(2, 2, 1));
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/shield_2.png"));
	//this->AddComponent<Animation>(new Animation(this->GetComponent<Renderer>(), 1, 4, 0.03f, 1.0f, true));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->GetComponent<Collider>()->SetTrigger(true);

	targetLeftSide = captain->GetTransform()->GetPosition() + Vector3(-300, 0, 0);
	targetRightside = captain->GetTransform()->GetPosition() + Vector3(300, 0, 0);
	direction = Vector3(10, 0, 0);
}


Shield::~Shield()
{
}

void Shield::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void Shield::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
}

void Shield::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
	//this->GetTransform()->SetPosition(captain->GetTransform()->GetPosition());
	Vector3 pos = this->GetTransform()->GetPosition();
	//pos.y = captain->GetTransform()->GetPosition().y;
	if (pos.x > targetRightside.x && direction.x > 0)
		direction.x *= -1;
	else if (pos.x < targetLeftSide.x && direction.x < 0)
		direction.x *= -1;
	this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + direction);
}

void Shield::Render()
{
	GameObject::Render();
}

void Shield::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
	GameObject::OnCollisionEnter(_other, _normal);
}

void Shield::SetTarget(Vector3 _target)
{
}
