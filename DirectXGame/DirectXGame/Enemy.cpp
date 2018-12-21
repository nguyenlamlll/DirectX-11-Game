#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(std::shared_ptr<DirectXCore::DxBase> _m_dxBase)
{
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetPosition(Vector3(50, 3500, 0));
	//this->GetTransform()->SetScale(Vector3(50, 50, 1));
	this->GetTransform()->SetScreenScale(Vector3(1, 1, 1));
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
	this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->AddComponent<Animation>(new Animation(this->GetComponent<Renderer>(), 1, 11, 0.1f, 1.0f, true));
	this->GetTransform()->SetScale(Vector3(this->GetComponent<Animation>()->GetFrameScale().x / 2, this->GetComponent<Animation>()->GetFrameScale().y / 2, 1));
	std::vector<std::string>* stringStates = new std::vector<std::string>();
	stringStates->push_back("shoot");
	stringStates->push_back("stand");
	this->AddComponent<State>(new State(this, *stringStates));
}

Enemy::Enemy(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, SimpleMath::Vector3 _instantiatePosition)
{
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetPosition(_instantiatePosition);
	this->GetTransform()->SetScale(Vector3(120, 120, 1));
	this->GetTransform()->SetScreenScale(Vector3(1, 1, 1));
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->AddComponent<Animation>(new Animation(this->GetComponent<Renderer>(), 1, 11, 0.1f, 1.0f, true));
	this->GetTransform()->SetScale(Vector3(this->GetComponent<Animation>()->GetFrameScale().x / 2, this->GetComponent<Animation>()->GetFrameScale().y / 2, 1));
	std::vector<std::string>* stringStates = new std::vector<std::string>();
	stringStates->push_back("shoot");
	stringStates->push_back("stand");
	this->AddComponent<State>(new State(this, *stringStates));
}

Enemy::Enemy(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, SimpleMath::Vector3 _instantiatePosition, SimpleMath::Vector3 _instantiateRotation, SimpleMath::Vector3 _instantiateScale)
{
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetPosition(_instantiatePosition);
	this->GetTransform()->SetScreenScale(_instantiateScale);
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->AddComponent<Animation>(new Animation(this->GetComponent<Renderer>(), 1, 11, 0.1f, 1.0f, true));
	this->GetTransform()->SetScale(Vector3(this->GetComponent<Animation>()->GetFrameScale().x/2, this->GetComponent<Animation>()->GetFrameScale().y/2, 1));
	std::vector<std::string>* stringStates = new std::vector<std::string>();
	stringStates->push_back("shoot");
	stringStates->push_back("stand");
	this->AddComponent<State>(new State(this, *stringStates));
}



void Enemy::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void Enemy::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	if (this->GetComponent<State>())
	{
		if (this->GetComponent<State>()->GetState() != "stand") {
			this->GetComponent<State>()->SetState("stand");
			this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/enemies/stand.png", 1, 4);
			this->GetTransform()->SetScale(Vector3(this->GetComponent<Animation>()->GetFrameScale().x / 2, this->GetComponent<Animation>()->GetFrameScale().y / 2, 1)*this->GetTransform()->GetScreenScale());
		}
	}
}

void Enemy::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

Enemy::~Enemy()
{
}
