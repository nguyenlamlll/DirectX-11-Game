#include "Player.h"

Player::Player(std::shared_ptr<DirectXCore::DxBase> _m_dxBase)
{
	cutscene = false;
	weaponTimer = 0;
	this->SetTag("Player");
	m_dxBase = _m_dxBase;

	this->GetTransform()->SetPosition(Vector3(500, 500, 0));
	this->GetTransform()->SetScale(Vector3(50, 120, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));
	this->AddComponent<Renderer>(new Renderer(_m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/stand.png"));
	this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->AddComponent<Animator>(new Animator(this->GetComponent<Renderer>()));
	AddAnimators();

	this->GetComponent<Rigidbody>()->SetGravity(Vector3(0, 30, 0));


	capshield = new Shield(_m_dxBase, this);
	this->AddChild(capshield);
}

void Player::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);

	if (hurtTime <= 0)
	{
		//if (m_dxBase->GetInputManager()->IsKeyDown("M") && weaponTimer < 0)
		//{
		//	if (!this->GetComponent<Collider>()->GetCollisionStatus()) this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/kick.png", 1, 1);
		//	else this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/dash.png", 1, 2);
		//	weaponTimer = 0.6f;
		//}
		//else if (m_dxBase->GetInputManager()->IsKeyDown("L") && weaponTimer < 0)
		//{
		//	if (!this->GetComponent<Collider>()->GetCollisionStatus()) this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/kick.png", 1, 1);
		//	else
		//	{
		//		this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/attack.png", 1, 2);
		//	}
		//	weaponTimer = 0.6f;
		//}
		//else if (m_dxBase->GetInputManager()->IsKeyDown("L") && weaponTimer < 0.4f)
		//{
		//	this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/shieldlessattack.png", 1, 2);
		//}
		//else if (m_dxBase->GetInputManager()->IsKeyDown("L") && m_dxBase->GetInputManager()->IsKeyDown("S") && weaponTimer < 0)
		//{
		//	if (this->GetComponent<Collider>()->GetCollisionStatus()) this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/sit_attack.png", 1, 2);
		//	weaponTimer = 0.6f;
		//}
		//weaponTimer -= _deltaTime;
		//if (this->GetComponent<Collider>()->GetCollisionStatus())
		//{
		//	if (m_dxBase->GetInputManager()->IsKeyDown("W"))
		//	{
		//		this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/lookup.png", 1, 1);
		//	}
		//	else if (m_dxBase->GetInputManager()->IsKeyDown("S"))
		//	{
		//		if (m_dxBase->GetInputManager()->IsKeyDown("L") && weaponTimer < 0)
		//		{
		//			this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/sit_attack.png", 1, 2);
		//			//weaponTimer = 0.5f;
		//		}
		//		else this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/sit.png", 1, 1);
		//	}
		//	else if (m_dxBase->GetInputManager()->IsKeyDown("O"))
		//	{
		//		this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/damage.png", 1, 1);
		//	}
		//	else if (m_dxBase->GetInputManager()->IsKeyDown("P"))
		//	{
		//		this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/die.png", 1, 2);
		//	}
		//	else
		//	{
		//		if (m_dxBase->GetInputManager()->IsKeyDown("D"))
		//		{
		//			this->GetComponent<Rigidbody>()->Move(Vector3(160, 0, 0));
		//			if (weaponTimer < 0)  this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/move.png", 1, 4);
		//		}
		//		if (m_dxBase->GetInputManager()->IsKeyDown("A"))
		//		{
		//			this->GetComponent<Rigidbody>()->Move(Vector3(-160, 0, 0));
		//			if (weaponTimer < 0)  this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/move.png", 1, 4);
		//		}
		//		if (m_dxBase->GetInputManager()->IsKeyDown("K"))
		//		{
		//			if (this->GetComponent<Rigidbody>()->GetAcceleration().y >= 0 && this->GetComponent<Collider>()->GetCollisionStatus())this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -1000, 0));
		//			jumpTime = -0.5f;
		//		}
		//		if (!m_dxBase->GetInputManager()->IsKeyDown("D") && !m_dxBase->GetInputManager()->IsKeyDown("A"))
		//		{
		//			this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
		//			if (weaponTimer < 0) this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/stand.png", 1, 1);
		//		}
		//	}
		//}
		//else
		//{
		//	jumpTime += _deltaTime;
		//	if (weaponTimer < 0)
		//	{
		//		//if (jumpTime > 0.5f) 
		//		this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/jump.png", 1, 1);
		//		if (jumpTime > 0 && m_dxBase->GetInputManager()->IsKeyDown("K"))
		//		{
		//			//jumpTime = 0;
		//			this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/spin.png", 1, 2);
		//		}
		//	}
		//	if (m_dxBase->GetInputManager()->IsKeyDown("D"))
		//	{
		//		this->GetComponent<Rigidbody>()->Move(Vector3(360, 0, 0));
		//	}
		//	if (m_dxBase->GetInputManager()->IsKeyDown("A"))
		//	{
		//		this->GetComponent<Rigidbody>()->Move(Vector3(-360, 0, 0));
		//	}
		//}
		if (!m_dxBase->GetInputManager()->IsKeyDown("D") && !m_dxBase->GetInputManager()->IsKeyDown("A"))
		{
			this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
		}
		if (m_dxBase->GetInputManager()->IsKeyDown("D"))
		{
			this->GetComponent<Rigidbody>()->Move(Vector3(160, 0, 0));
		}
		if (m_dxBase->GetInputManager()->IsKeyDown("A"))
		{
			this->GetComponent<Rigidbody>()->Move(Vector3(-160, 0, 0));
		}
		if (m_dxBase->GetInputManager()->IsKeyDown("K"))
		{
			if (this->GetComponent<Rigidbody>()->GetAcceleration().y >= 0 && this->GetComponent<Collider>()->GetCollisionStatus())this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -1000, 0));
		}
		if (this->GetComponent<Rigidbody>()->GetVelocity().x > 0) transform->SetRotation(Vector3(transform->GetRotation().x, 360, transform->GetRotation().z));
		else if (this->GetComponent<Rigidbody>()->GetVelocity().x < 0) transform->SetRotation(Vector3(transform->GetRotation().x, 0, transform->GetRotation().z));
	}
	else
	{
		hurtTime -= _deltaTime;
		this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
	}
}

void Player::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	ManageAnimators();
	jumpTime = (this->GetComponent<Collider>()->GetCollisionStatus()) ? 0 : jumpTime + _deltaTime;
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Sit")
	{
		if (this->GetTransform()->GetScale().y != 60)
		{
			this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + Vector3(0, 30, 0));
			this->GetTransform()->SetScale(Vector3(25, 60, 0));
		}
	}
	else
	{
		if (this->GetTransform()->GetScale().y != 120)
		{
			this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + Vector3(0, -30, 0));
			this->GetTransform()->SetScale(Vector3(50, 120, 0));
		}
	}
}

void Player::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void Player::OnCollisionEnter(Collider* _other, Vector3 _normal)
{
	if (_other->GetAttachedGameObject()->GetTag() == "Enemy" || _other->GetAttachedGameObject()->GetTag() == "Boss" || _other->GetAttachedGameObject()->GetTag() == "EnemyBullet")
	{
		TakeDamage();
		//this->GetComponent<Collider>()->SetCollisionStatus(false);
	}
	else if (_other->GetAttachedGameObject()->GetTag() == "Water")
	{
		GameObject::OnCollisionEnter(_other, _normal);
		if (this->GetComponent<Rigidbody>()->GetAcceleration().y >= 0 && this->GetComponent<Collider>()->GetCollisionStatus())this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -1000, 0));
	}
	else
	{
		GameObject::OnCollisionEnter(_other, _normal);
		this->GetComponent<Collider>()->SetCollisionStatus(true);
	}
}


Player::~Player()
{
}

void Player::AddAnimators()
{
	Animation* moveAnim = new Animation(L"Resources/Captain/Animations/move.png", "Move", this->GetComponent<Renderer>(), 1, 4, 0.1f, 1.0f, true);
	Animation* standAnim = new Animation(L"Resources/Captain/Animations/stand.png", "Stand", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* jumpAnim = new Animation(L"Resources/Captain/Animations/jump.png", "Jump", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* spinJumpAnim = new Animation(L"Resources/Captain/Animations/spin.png", "SpinJump", this->GetComponent<Renderer>(), 1, 2, 0.1f, 1.0f, true);
	Animation* attackAnim = new Animation(L"Resources/Captain/Animations/shieldlessattack.png", "Attack", this->GetComponent<Renderer>(), 1, 2, 0.1f, 1.0f, true);
	Animation* throwAnim = new Animation(L"Resources/Captain/Animations/attack.png", "Attack", this->GetComponent<Renderer>(), 1, 2, 0.1f, 1.0f, true);
	Animation* sitAnim = new Animation(L"Resources/Captain/Animations/sit.png", "Sit", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* hurtAnim = new Animation(L"Resources/Captain/Animations/hurt.png", "Hurt", this->GetComponent<Renderer>(), 1, 3, 0.1f, 1.0f, true);

	moveAnim->interupt = true;
	this->GetComponent<Animator>()->AddAnimation(standAnim);
	this->GetComponent<Animator>()->AddAnimation(moveAnim);
	this->GetComponent<Animator>()->AddAnimation(jumpAnim);
	this->GetComponent<Animator>()->AddAnimation(attackAnim);
	this->GetComponent<Animator>()->AddAnimation(spinJumpAnim);
	this->GetComponent<Animator>()->AddAnimation(sitAnim);
	this->GetComponent<Animator>()->AddAnimation(throwAnim);
	this->GetComponent<Animator>()->AddAnimation(hurtAnim);

	this->GetComponent<Animator>()->AddTransition("Stand", "Move", true);
	this->GetComponent<Animator>()->AddTransition("Stand", "Attack", true);
	this->GetComponent<Animator>()->AddTransition("Stand", "Throw", true);
	this->GetComponent<Animator>()->AddTransition("Stand", "Jump", true);

	this->GetComponent<Animator>()->AddTransition("Move", "Stand", true);
	this->GetComponent<Animator>()->AddTransition("Move", "Attack", true);
	this->GetComponent<Animator>()->AddTransition("Move", "Throw", true);
	this->GetComponent<Animator>()->AddTransition("Move", "Jump", true);

	this->GetComponent<Animator>()->AddTransition("Jump", "Stand", true);
	this->GetComponent<Animator>()->AddTransition("Jump", "Move", true);
	this->GetComponent<Animator>()->AddTransition("Jump", "SpinJump", true);

	this->GetComponent<Animator>()->AddTransition("SpinJump", "Stand", true);
	this->GetComponent<Animator>()->AddTransition("SpinJump", "Move", true);

	this->GetComponent<Animator>()->AddTransition("Attack", "Stand", true);
	this->GetComponent<Animator>()->AddTransition("Attack", "Move", true);

	this->GetComponent<Animator>()->AddTransition("Sit", "Stand", true);

	this->GetComponent<Animator>()->AddTransition("Throw", "Stand", true);

	this->GetComponent<Animator>()->AddTransition("Hurt", "Stand", true);

	this->GetComponent<Animator>()->SetCurrentAnimation(moveAnim);
}

void Player::ManageAnimators()
{
	this->GetComponent<Animator>()->SetBool("Throw", m_dxBase->GetInputManager()->IsKeyDown("L") && this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "Attack" && Vector3::Distance(capshield->GetTransform()->GetPosition(), this->GetTransform()->GetPosition()) < 10);
	this->GetComponent<Animator>()->SetBool("Attack", m_dxBase->GetInputManager()->IsKeyDown("L") && this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "Attack" && Vector3::Distance(capshield->GetTransform()->GetPosition(), this->GetTransform()->GetPosition()) > 10);
	this->GetComponent<Animator>()->SetBool("Sit", m_dxBase->GetInputManager()->IsKeyDown("S") && this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "Sit" && this->GetComponent<Collider>()->GetCollisionStatus());
	this->GetComponent<Animator>()->SetBool("Hurt", this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "Hurt" && hurtTime > 0);

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
		this->GetComponent<Animator>()->SetBool("Jump", "Stand", this->GetComponent<Collider>()->GetCollisionStatus());
		this->GetComponent<Animator>()->SetBool("Jump", "SpinJump", jumpTime > 0.3f);
	}
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "SpinJump")
	{
		this->GetComponent<Animator>()->SetBool("SpinJump", "Stand", this->GetComponent<Collider>()->GetCollisionStatus());
	}
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Attack")
	{
		/*this->GetComponent<Animator>()->SetBool("Attack", "Stand", !m_dxBase->GetInputManager()->IsKeyDown("L") && this->GetComponent<Rigidbody>()->GetVelocity().x == 0);
		this->GetComponent<Animator>()->SetBool("Attack", "Move", !m_dxBase->GetInputManager()->IsKeyDown("L") && this->GetComponent<Rigidbody>()->GetVelocity().x != 0);*/
		this->GetComponent<Animator>()->SetBool("Attack", "Stand", !m_dxBase->GetInputManager()->IsKeyDown("L") && this->GetComponent<Rigidbody>()->GetVelocity().x == 0);
		this->GetComponent<Animator>()->SetBool("Attack", "Move", !m_dxBase->GetInputManager()->IsKeyDown("L") && this->GetComponent<Rigidbody>()->GetVelocity().x != 0);
	}
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Throw")
	{
		this->GetComponent<Animator>()->SetBool("Throw", "Stand", !m_dxBase->GetInputManager()->IsKeyDown("L") && this->GetComponent<Rigidbody>()->GetVelocity().x == 0);
		this->GetComponent<Animator>()->SetBool("Throw", "Move", !m_dxBase->GetInputManager()->IsKeyDown("L") && this->GetComponent<Rigidbody>()->GetVelocity().x != 0);
	}
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Sit")
	{
		this->GetComponent<Animator>()->SetBool("Sit", "Stand", !m_dxBase->GetInputManager()->IsKeyDown("S") && this->GetComponent<Collider>()->GetCollisionStatus());
	}
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Hurt")
	{
		this->GetComponent<Animator>()->SetBool("Hurt", "Stand", hurtTime <= 0);
	}
}
