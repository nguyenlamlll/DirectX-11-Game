#include "HornetBoss.h"



HornetBoss::HornetBoss()
{
}

HornetBoss::HornetBoss(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, SimpleMath::Vector3 _position, SimpleMath::Vector3 _rotation, SimpleMath::Vector3 _scale)
{
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetPosition(_position);
	this->GetTransform()->SetScreenScale(_scale);
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->AddComponent<Animation>(new Animation(this->GetComponent<Renderer>(), 1, 11, 0.1f, 1.0f, true));
	this->GetTransform()->SetScale(Vector3(this->GetComponent<Animation>()->GetFrameScale().x*_scale.x, this->GetComponent<Animation>()->GetFrameScale().y*_scale.y, 1));
	std::vector<std::string>* stringStates = new std::vector<std::string>();
	stringStates->push_back("shoot");
	stringStates->push_back("stand");
	this->AddComponent<State>(new State(this, *stringStates));
}

void HornetBoss::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void HornetBoss::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
}

void HornetBoss::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void HornetBoss::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
}


HornetBoss::~HornetBoss()
{
}
