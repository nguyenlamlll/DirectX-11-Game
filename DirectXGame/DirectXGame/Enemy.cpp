#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(std::shared_ptr<DirectXCore::DxBase> _m_dxBase)
{
	player = NULL;
	bulletTimer = 0;
	deathTimer = 0;
	attackTimer = 0;
	death = false;
	m_dxBase = _m_dxBase;
	//this->GetTransform()->SetPosition(Vector3(50, 3500, 0));
	this->GetTransform()->SetScale(Vector3(93, 141, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/enemy/shooter_sit.png"));
	this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->AddComponent<Animation>(new Animation("asd",this->GetComponent<Renderer>(), 1, 11, 0.1f, 1.0f, true));
	std::vector<std::string>* stringStates = new std::vector<std::string>();
	stringStates->push_back("shoot");
	stringStates->push_back("stand");
	this->AddComponent<State>(new State(this, *stringStates));

	this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/enemy/shooter_move.png", 1, 3);
	this->SetTag("Enemy");
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
		//JUMP
		if (attackTimer > 2.0f)
		{
			this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -300, 0));
			attackTimer = 0;
		}
		else if (attackTimer > 0 && attackTimer < 2.0f)
		{
			float dirX = (player->GetTransform()->GetPosition().x - this->GetTransform()->GetPosition().x) > 0 ? 50 : -50;
			this->GetComponent<Rigidbody>()->Move(Vector3(dirX, 0, 0));
		}
		//SHOOT
		if (bulletTimer > 3.0f)
		{
			//shooting code
			float directionX = player->GetTransform()->GetPosition().x - this->GetTransform()->GetPosition().x;
			if (directionX > 10)
			{
				directionX = 100;
			}
			else if (directionX < -10)
			{
				directionX = -100;
			}
			else directionX = 0;
			Bullet* bullet = new Bullet(L"Resources/Captain/Animations/enemy/shooter_bullet.png", m_dxBase, this->GetTransform()->GetPosition(), Vector3(3, 3, 1), Vector3(directionX,0,0));
			//Bullet* bullet = new Bullet(m_dxBase, this->GetTransform()->GetPosition());
			bullet->SetTag("EnemyBullet");
			bullet->AddComponent<Rigidbody>(new Rigidbody(bullet));
			bullet->GetComponent<Rigidbody>()->SetKinematic(true);
			m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->push_back(bullet);
			//this->AddChild(bullet);
			bulletTimer = 0;
		}
		attackTimer += _deltaTime;
		bulletTimer += _deltaTime;
	}
	else
	{
		//this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/enemies/stand.png", 1, 4);
		if (deathTimer > 1.5f)
		{
			m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->erase(std::remove(m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->begin(), m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->end(), this), m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->end());
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
	if (_other->GetAttachedGameObject()->GetTag() != "Player") GameObject::OnCollisionEnter(_other, _normal);
	/*if (_other->GetAttachedGameObject()->GetTag() == "Wall") GameObject::OnCollisionEnter(_other, _normal);
	if (_other->GetAttachedGameObject()->GetTag() == "PlayerBullet") death = true;*/
}

Enemy::~Enemy()
{
}
