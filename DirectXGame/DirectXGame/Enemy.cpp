#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(std::shared_ptr<DirectXCore::DxBase> _m_dxBase)
{
	bulletTimer = 0;
	deathTimer = 0;
	death = false;
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
	bulletTimer = 0;
	deathTimer = 0;
	death = false;
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
	bulletTimer = 0;
	deathTimer = 0;
	death = false;
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
}



void Enemy::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void Enemy::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	if (!death)
	{
		if (this->GetComponent<State>())
		{
			if (this->GetComponent<State>()->GetState() != "stand") {
				this->GetComponent<State>()->SetState("stand");
				if (this->GetName() == "Brute") this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/enemies/enemies11.png", 1, 4);
				else if (this->GetName() == "Copter") this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/enemies/enemies18.png", 1, 6);
				else this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/enemies/stand.png", 1, 4);
				this->GetTransform()->SetScale(Vector3(this->GetComponent<Animation>()->GetFrameScale().x / 2, this->GetComponent<Animation>()->GetFrameScale().y / 2, 1)*this->GetTransform()->GetScreenScale());
			}
		}
		if (bulletTimer >= 3.0f)
		{
			Bullet* asd = new Bullet(L"Resources/Animations/bullet/lv1.png", m_dxBase, this->GetTransform()->GetPosition() + Vector3(transform->GetRotation().y == 0 ? 10 : -10, -10, 0), Vector3(2, 2, 2), Vector3(transform->GetRotation().y == 0 ? 20 : -20, 0, 0));
			asd->SetTag("EnemyBullet");
			asd->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/enemies/1.png", 1, 1);
			asd->GetTransform()->SetScale(Vector3(5, 5, 5));
			asd->AddComponent<Rigidbody>(new Rigidbody(asd));
			asd->GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 100.0f, 0));
			asd->GetComponent<Rigidbody>()->AddForce(Vector3(-300, -200, 0));
			bulletTimer = 0;
		}
		else bulletTimer += _deltaTime;
	}
	else
	{
		//this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/enemies/stand.png", 1, 4);
		if (deathTimer > 1.5f)
		{
			m_dxBase->GetCurrentScene()->GetGameObjectList()->erase(std::remove(m_dxBase->GetCurrentScene()->GetGameObjectList()->begin(), m_dxBase->GetCurrentScene()->GetGameObjectList()->end(), this), m_dxBase->GetCurrentScene()->GetGameObjectList()->end());
		}
		else deathTimer += _deltaTime;
	}
}

void Enemy::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void Enemy::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
	if (_other->GetAttachedGameObject()->GetTag() == "Wall") GameObject::OnCollisionEnter(_other, _normal);
	if (_other->GetAttachedGameObject()->GetTag() == "PlayerBullet") death = true;
}

Enemy::~Enemy()
{
}
