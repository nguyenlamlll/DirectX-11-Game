#include "ShurikenBoss.h"



ShurikenBoss::ShurikenBoss()
{
}

ShurikenBoss::ShurikenBoss(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, SimpleMath::Vector3 _instantiatePosition, SimpleMath::Vector3 _instantiateRotation, SimpleMath::Vector3 _instantiateScale)
{
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetPosition(_instantiatePosition);
	this->GetTransform()->SetScreenScale(_instantiateScale);
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->AddComponent<Animation>(new Animation(this->GetComponent<Renderer>(), 1, 11, 0.1f, 1.0f, true));
	this->GetTransform()->SetScale(Vector3(this->GetComponent<Animation>()->GetFrameScale().x / 2, this->GetComponent<Animation>()->GetFrameScale().y / 2, 1));
	std::vector<std::string>* stringStates = new std::vector<std::string>();
	stringStates->push_back("shoot");
	stringStates->push_back("stand");
	this->AddComponent<State>(new State(this, *stringStates));
	direction = Vector3(0, -200.0f, 0);
}

void ShurikenBoss::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
	this->GetComponent<Rigidbody>()->Move(direction);
}

void ShurikenBoss::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	if (this->GetComponent<State>())
	{
		if (this->GetComponent<State>()->GetState() != "stand") {
			this->GetComponent<State>()->SetState("stand");
			this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/boss/Shuriken/MMX3ShurikeinF.png", 1, 1);
			this->GetTransform()->SetScale(Vector3(this->GetComponent<Animation>()->GetFrameScale().x / 2, this->GetComponent<Animation>()->GetFrameScale().y / 2, 1)*this->GetTransform()->GetScreenScale());
		}
	}
}

void ShurikenBoss::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void ShurikenBoss::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
	if (_other->GetAttachedGameObject()->GetTag() == "Wall")
	{
		if (_normal.y < 0)
		{
			if (_normal.x == 0) direction = Vector3(0, -200, 0);
			//if (_normal.x < 0) if (direction.x > 0) this->GetComponent<Rigidbody>()->Move(Vector3(-200, 0, 0));
			//if (_normal.x > 0) if (direction.x < 0) this->GetComponent<Rigidbody>()->Move(Vector3(200, 0, 0));

		}
		else if (_normal.y > 0) direction = Vector3(0, 200, 0);
	}
}


ShurikenBoss::~ShurikenBoss()
{
}
