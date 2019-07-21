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
	this->GetTransform()->SetScreenScale(Vector3(2,2,1));
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/shield_2.png"));
	//this->AddComponent<Animation>(new Animation(this->GetComponent<Renderer>(), 1, 4, 0.03f, 1.0f, true));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->GetComponent<Collider>()->SetTrigger(true);
	m_dxBase->GetCurrentScene()->GetGameObjectList()->insert(m_dxBase->GetCurrentScene()->GetGameObjectList()->end(), this);
	//this->SetParent(captain);
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
	//this->GetTransform()->SetPosition(captain->GetTransform()->GetPosition());
}

void Shield::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate (_deltaTime);
}

void Shield::Render()
{
	GameObject::Render();
}

void Shield::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
	GameObject::OnCollisionEnter(_other,_normal);
}

void Shield::SetTarget(Vector3 _target)
{
}
