#include "Shooter.h"



Shooter::Shooter()
{
}

Shooter::Shooter(std::shared_ptr<DirectXCore::DxBase> _m_dxBase)
{
	m_dxBase = _m_dxBase;
	hurtTime = 0;
	stateTimeCycle = 0;
	player = NULL;
	bulletTimer = 0;
	deathTimer = 0;
	attackTimer = 0;
	death = false;
	this->GetTransform()->SetScale(Vector3(93, 141, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/enemy/shooter_sit.png"));
	this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->AddComponent<Animator>(new Animator(this->GetComponent<Renderer>()));
	AddAnimators();
	this->SetTag("Enemy");
}

void Shooter::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void Shooter::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	transform->SetRotation(Vector3(transform->GetRotation().x, (player->GetTransform()->GetPosition().x - this->transform->GetPosition().x > 0) ? 360 : 0, transform->GetRotation().z));
	
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Sit")
	{
		if (this->GetTransform()->GetScale().y != 70)
		{
			this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + Vector3(0, 35, 0));
			this->GetTransform()->SetScale(Vector3(93, 70, 0));
		}
	}
	else
	{
		if (this->GetTransform()->GetScale().y != 141)
		{
			this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + Vector3(0, -45, 0));
			this->GetTransform()->SetScale(Vector3(93, 141, 0));
		}
	}

	// STAGE 2
	if (stateTimeCycle > 2.0f)
	{
		this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
		//SHOOT
		if (bulletTimer > 1.5f && this->GetComponent<Collider>()->GetCollisionStatus())
		{
			this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
			Vector3 offset = Vector3((this->GetTransform()->GetRotation().y > 120) ? 80 : -80, -50, 0);

			//shooting code
			float directionX = player->GetTransform()->GetPosition().x - this->GetTransform()->GetPosition().x;
			if (directionX > 10) directionX = 400;
			else if (directionX < -10) directionX = -400;
			else directionX = 0;
			Vector3 dir = player->GetTransform()->GetPosition() - this->transform->GetPosition();
			dir.Normalize();
			Bullet* bullet = new Bullet(L"Resources/Captain/Animations/enemy/shooter_bullet.png", m_dxBase, this->GetTransform()->GetPosition() + offset, Vector3(3, 3, 1), dir * 400);
			bullet->SetTag("EnemyBullet");
			bullet->AddComponent<Rigidbody>(new Rigidbody(bullet));
			bullet->GetComponent<Rigidbody>()->SetKinematic(true);
			m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->push_back(bullet);
			//this->AddChild(bullet);
			bulletTimer = 0;
		}
		bulletTimer += _deltaTime;
	}
	// STAGE 1
	else if (stateTimeCycle > 0)
	{
	}
	ManageAnimators();
	stateTimeCycle = (stateTimeCycle > 4.0f) ? 0 : stateTimeCycle + _deltaTime;
	if (hurtTime > 0 && hurtTime < 0.5)
	{
		m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->erase(std::remove(m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->begin(), m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->end(), this), m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->end());
		delete this;
	}
	else if (hurtTime > 0) hurtTime -= _deltaTime;
}

void Shooter::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void Shooter::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
	if (_other->GetAttachedGameObject()->GetTag() != "Player") GameObject::OnCollisionEnter(_other, _normal);
	else
	{
		if (_other->GetAttachedGameObject()->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Attack"
			|| _other->GetAttachedGameObject()->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "SitAttack"
			|| _other->GetAttachedGameObject()->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "JumpAttack"
			|| _other->GetAttachedGameObject()->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Dash")
		{
			hurtTime = 1.0f;
		}
	}
	if (_other->GetAttachedGameObject()->GetTag() == "Shield" && _other->GetAttachedGameObject()->GetComponent<Rigidbody>()->GetVelocity().x != 0)
	{
		hurtTime = 1.0f;
	}

}


Shooter::~Shooter()
{
}

void Shooter::AddAnimators()
{
	//Animation* standAnim = new Animation(L"Resources/Captain/Animations/enemy/stand.png", "Stand", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* attackAnim = new Animation(L"Resources/Captain/Animations/enemy/shooter_shoot.png", "Attack", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* sitAnim = new Animation(L"Resources/Captain/Animations/enemy/shooter_sit.png", "Sit", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* dieAnim = new Animation(L"Resources/Captain/Animations/enemy/shooter_die.png", "Die", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	//this->GetComponent<Animator>()->AddAnimation(standAnim);
	this->GetComponent<Animator>()->AddAnimation(sitAnim);
	this->GetComponent<Animator>()->AddAnimation(attackAnim);
	this->GetComponent<Animator>()->AddAnimation(dieAnim);
	this->GetComponent<Animator>()->SetCurrentAnimation(attackAnim);
}

void Shooter::ManageAnimators()
{
	this->GetComponent<Animator>()->SetBool("Attack", stateTimeCycle > 2.0f);
	this->GetComponent<Animator>()->SetBool("Sit", stateTimeCycle > 0 && stateTimeCycle < 2.0f);
	this->GetComponent<Animator>()->SetBool("Die", hurtTime > 0.5f);
}
