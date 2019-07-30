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
		//if (this->GetName() == "Brute")
		//{
		//	if (player == NULL)
		//	{
		//		for (size_t i = 0; i < m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->size(); i++)
		//		{
		//			if (m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->at(i)->GetTag() == "Player") player = m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->at(i);
		//		}
		//	}
		//	if (this->GetComponent<State>())
		//	{
		//		if (this->GetComponent<State>()->GetState() != "stand") {
		//			this->GetComponent<State>()->SetState("stand");
		//			this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/enemies/enemies11.png", 1, 4);
		//			this->GetTransform()->SetScale(Vector3(this->GetComponent<Animation>()->GetFrameScale().x / 2, this->GetComponent<Animation>()->GetFrameScale().y / 2, 1)*this->GetTransform()->GetScreenScale());
		//		}
		//	}
		//	if (bulletTimer >= 3.0f)
		//	{
		//		Bullet* asd = new Bullet(L"Resources/Animations/bullet/lv1.png", m_dxBase, this->GetTransform()->GetPosition() + Vector3(transform->GetRotation().y == 0 ? 10 : -10, -10, 0), Vector3(2, 2, 2), Vector3(transform->GetRotation().y == 0 ? 20 : -20, 0, 0));
		//		asd->SetTag("EnemyBullet");
		//		asd->SetName("BruteBullet");
		//		asd->SetTarget(player->GetTransform()->GetPosition());
		//		asd->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/enemies/rocket.png", 1, 2);
		//		asd->GetTransform()->SetScale(Vector3(5, 5, 5));
		//		//asd->AddComponent<Rigidbody>(new Rigidbody(asd));
		//		//asd->GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 100.0f, 0));
		//		//asd->GetComponent<Rigidbody>()->AddForce(Vector3(-300, -200, 0));
		//		bulletTimer = 0;
		//	}
		//	else bulletTimer += _deltaTime;
		//}
		//else if (this->GetName() == "Copter")
		//{
		//	if (this->GetComponent<State>())
		//	{
		//		if (this->GetComponent<State>()->GetState() != "stand") {
		//			this->GetComponent<State>()->SetState("stand");
		//			this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/enemies/enemies15.png", 1, 4);
		//			this->GetTransform()->SetScale(Vector3(this->GetComponent<Animation>()->GetFrameScale().x / 2, this->GetComponent<Animation>()->GetFrameScale().y / 2, 1)*this->GetTransform()->GetScreenScale());
		//		}
		//	}
		//	if (bulletTimer >= 3.0f)
		//	{
		//		Bullet* asd = new Bullet(L"Resources/Animations/bullet/lv1.png", m_dxBase, this->GetTransform()->GetPosition() + Vector3(transform->GetRotation().y == 0 ? 10 : -10, -10, 0), Vector3(2, 2, 2), Vector3(transform->GetRotation().y == 0 ? 20 : -20, 0, 0));
		//		asd->SetTag("EnemyBullet");
		//		asd->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/enemies/enemies17.png", 1, 4);
		//		asd->GetTransform()->SetScale(Vector3(5, 5, 5));
		//		asd->AddComponent<Rigidbody>(new Rigidbody(asd));
		//		bulletTimer = 0;
		//	}
		//	else bulletTimer += _deltaTime;
		//}
		//else
		//{
		//	if (this->GetComponent<State>())
		//	{
		//		if (this->GetComponent<State>()->GetState() != "stand") {
		//			this->GetComponent<State>()->SetState("stand");
		//			this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/enemies/stand.png", 1, 4);
		//			this->GetTransform()->SetScale(Vector3(this->GetComponent<Animation>()->GetFrameScale().x / 2, this->GetComponent<Animation>()->GetFrameScale().y / 2, 1)*this->GetTransform()->GetScreenScale());
		//		}
		//	}
		//	if (bulletTimer >= 3.0f)
		//	{
		//		Bullet* asd = new Bullet(L"Resources/Animations/bullet/lv1.png", m_dxBase, this->GetTransform()->GetPosition() + Vector3(transform->GetRotation().y == 0 ? 10 : -10, -10, 0), Vector3(2, 2, 2), Vector3(transform->GetRotation().y == 0 ? 20 : -20, 0, 0));
		//		asd->SetTag("EnemyBullet");
		//		asd->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/enemies/1.png", 1, 1);
		//		asd->GetTransform()->SetScale(Vector3(5, 5, 5));
		//		asd->AddComponent<Rigidbody>(new Rigidbody(asd));
		//		asd->GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 100.0f, 0));
		//		asd->GetComponent<Rigidbody>()->AddForce(Vector3(-300, -200, 0));
		//		bulletTimer = 0;
		//	}
		//	else bulletTimer += _deltaTime;
		//}

		//JUMP
		if (attackTimer > 2.0f)
		{
			this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -300, 0));
			attackTimer = 0;
		}
		else if (attackTimer > 0 && attackTimer < 2.0f)
		{
			this->GetComponent<Rigidbody>()->Move(Vector3(50, 0, 0));
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
	GameObject::OnCollisionEnter(_other, _normal);
	/*if (_other->GetAttachedGameObject()->GetTag() == "Wall") GameObject::OnCollisionEnter(_other, _normal);
	if (_other->GetAttachedGameObject()->GetTag() == "PlayerBullet") death = true;*/
}

Enemy::~Enemy()
{
}
