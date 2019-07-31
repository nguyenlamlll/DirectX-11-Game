#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(std::shared_ptr<DirectXCore::DxBase> _m_dxBase)
{
	stateTimeCycle = 0;
	player = NULL;
	bulletTimer = 0;
	deathTimer = 0;
	attackTimer = 0;
	death = false;
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetScale(Vector3(93, 141, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/enemy/shooter_sit.png"));
	this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));

	this->AddComponent<Animator>(new Animator(this->GetComponent<Renderer>()));
	AddAnimators();
	this->SetTag("Enemy");
}





void Enemy::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
	if (this->GetComponent<Rigidbody>()->GetVelocity().x > 0) transform->SetRotation(Vector3(transform->GetRotation().x, 360, transform->GetRotation().z));
	else if (this->GetComponent<Rigidbody>()->GetVelocity().x < 0) transform->SetRotation(Vector3(transform->GetRotation().x, 0, transform->GetRotation().z));
}

void Enemy::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	//if (!death)
	//{
	//	//JUMP
	//	if (attackTimer > 2.0f)
	//	{
	//		this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -300, 0));
	//		attackTimer = 0;
	//	}
	//	else if (attackTimer > 0 && attackTimer < 2.0f)
	//	{
	//		float dirX = (player->GetTransform()->GetPosition().x - this->GetTransform()->GetPosition().x) > 0 ? 50 : -50;
	//		this->GetComponent<Rigidbody>()->Move(Vector3(dirX, 0, 0));
	//	}
	//	
	//}
	//else
	//{
	//	//this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/enemies/stand.png", 1, 4);
	//	if (deathTimer > 1.5f)
	//	{
	//		m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->erase(std::remove(m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->begin(), m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->end(), this), m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->end());
	//	}
	//	else deathTimer += _deltaTime;
	//}

	// STAGE 2
	if (stateTimeCycle > 2.0f)
	{
		//SHOOT
		if (bulletTimer > 1.0f && this->GetComponent<Collider>()->GetCollisionStatus())
		{
			this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));

			//shooting code
			float directionX = player->GetTransform()->GetPosition().x - this->GetTransform()->GetPosition().x;
			if (directionX > 10) directionX = 400;
			else if (directionX < -10) directionX = -400;
			else directionX = 0;
			Bullet* bullet = new Bullet(L"Resources/Captain/Animations/enemy/shooter_bullet.png", m_dxBase, this->GetTransform()->GetPosition(), Vector3(3, 3, 1), Vector3(directionX, 0, 0));
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
		//JUMP
		if (this->GetComponent<Collider>()->GetCollisionStatus() && this->GetComponent<Rigidbody>()->GetVelocity().y >= 0) this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -300, 0));
		float dirX = (player->GetTransform()->GetPosition().x - this->GetTransform()->GetPosition().x) > 0 ? 50 : -50;
		this->GetComponent<Rigidbody>()->Move(Vector3(dirX, 0, 0));
	}


	ManageAnimators();
	stateTimeCycle = (stateTimeCycle > 4.0f) ? 0 : stateTimeCycle + _deltaTime;
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

void Enemy::AddAnimators()
{
	Animation* moveAnim = new Animation(L"Resources/Captain/Animations/enemy/shooter_move.png", "Move", this->GetComponent<Renderer>(), 1, 3, 0.1f, 1.0f, true);
	//Animation* standAnim = new Animation(L"Resources/Captain/Animations/enemy/stand.png", "Stand", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* jumpAnim = new Animation(L"Resources/Captain/Animations/enemy/shooter_sit.png", "Jump", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* throwAnim = new Animation(L"Resources/Captain/Animations/enemy/shooter_shoot.png", "Attack", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* sitAnim = new Animation(L"Resources/Captain/Animations/enemy/shooter_sit.png", "Sit", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	moveAnim->interupt = true;
	//this->GetComponent<Animator>()->AddAnimation(standAnim);
	this->GetComponent<Animator>()->AddAnimation(moveAnim);
	this->GetComponent<Animator>()->AddAnimation(jumpAnim);
	this->GetComponent<Animator>()->AddAnimation(sitAnim);
	this->GetComponent<Animator>()->AddAnimation(throwAnim);
	this->GetComponent<Animator>()->AddTransition("Stand", "Move", true);
	this->GetComponent<Animator>()->AddTransition("Stand", "Attack", true);
	this->GetComponent<Animator>()->AddTransition("Stand", "Jump", true);

	this->GetComponent<Animator>()->AddTransition("Move", "Stand", true);
	this->GetComponent<Animator>()->AddTransition("Move", "Attack", true);
	this->GetComponent<Animator>()->AddTransition("Move", "Jump", true);

	this->GetComponent<Animator>()->AddTransition("Jump", "Stand", true);
	this->GetComponent<Animator>()->AddTransition("Jump", "Move", true);

	this->GetComponent<Animator>()->AddTransition("Attack", "Stand", true);
	this->GetComponent<Animator>()->AddTransition("Attack", "Move", true);

	this->GetComponent<Animator>()->AddTransition("Sit", "Stand", true);

	this->GetComponent<Animator>()->AddTransition("Throw", "Stand", true);

	this->GetComponent<Animator>()->SetCurrentAnimation(moveAnim);
}

void Enemy::ManageAnimators()
{
	this->GetComponent<Animator>()->SetBool("Attack", this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "Attack" && stateTimeCycle > 2.0f &&  this->GetComponent<Collider>()->GetCollisionStatus());
	//this->GetComponent<Animator>()->SetBool("Sit",this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "Sit" && this->GetComponent<Collider>()->GetCollisionStatus());

	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Move")
	{
		this->GetComponent<Animator>()->SetBool("Move", "Jump", !this->GetComponent<Collider>()->GetCollisionStatus());
		this->GetComponent<Animator>()->SetBool("Move", "Stand", this->GetComponent<Rigidbody>()->GetVelocity().x == 0 && this->GetComponent<Collider>()->GetCollisionStatus());
	}
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Stand")
	{
		this->GetComponent<Animator>()->SetBool("Stand", "Move", this->GetComponent<Rigidbody>()->GetVelocity().x != 0 && this->GetComponent<Collider>()->GetCollisionStatus());
		this->GetComponent<Animator>()->SetBool("Stand", "Jump", !this->GetComponent<Collider>()->GetCollisionStatus());
	}
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Jump")
	{
		//this->GetComponent<Animator>()->SetBool("Jump", "Stand", this->GetComponent<Collider>()->GetCollisionStatus());
		this->GetComponent<Animator>()->SetBool("Jump", "Move", this->GetComponent<Collider>()->GetCollisionStatus());
	}
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Attack")
	{
		this->GetComponent<Animator>()->SetBool("Attack", "Move", stateTimeCycle < 2.0f && this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "Move");
		//this->GetComponent<Animator>()->SetBool("Attack", "Stand", !m_dxBase->GetInputManager()->IsKeyDown("L") && this->GetComponent<Rigidbody>()->GetVelocity().x == 0);
		//this->GetComponent<Animator>()->SetBool("Attack", "Move", !m_dxBase->GetInputManager()->IsKeyDown("L") && this->GetComponent<Rigidbody>()->GetVelocity().x != 0);
	}
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Sit")
	{
		//this->GetComponent<Animator>()->SetBool("Sit", "Stand",this->GetComponent<Collider>()->GetCollisionStatus());
	}
}
