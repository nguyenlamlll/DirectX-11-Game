#include "Player.h"

Player::Player(std::shared_ptr<DirectXCore::DxBase> _m_dxBase)
{
	dashTime = 0;
	cutscene = false;
	weaponTimer = 0;
	this->SetTag("Player");
	m_dxBase = _m_dxBase;

	this->GetTransform()->SetScale(Vector3(50, 120, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));
	this->AddComponent<Renderer>(new Renderer(_m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/stand.png"));
	this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->AddComponent<Animator>(new Animator(this->GetComponent<Renderer>()));
	AddAnimators();

	this->GetComponent<Rigidbody>()->SetGravity(Vector3(0, 30, 0));


	capshield = new Shield(_m_dxBase, this);
	//m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->push_back(capshield);
	//this->AddChild(capshield);
}

void Player::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);

	if (hurtTime <= 0)
	{
		if (!m_dxBase->GetInputManager()->IsKeyDown("D") && !m_dxBase->GetInputManager()->IsKeyDown("A"))
		{
			this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
		}
		if (m_dxBase->GetInputManager()->IsKeyDown("D"))
		{
			this->GetComponent<Rigidbody>()->Move(Vector3(100, 0, 0));
		}
		if (m_dxBase->GetInputManager()->IsKeyDown("A"))
		{
			this->GetComponent<Rigidbody>()->Move(Vector3(-100, 0, 0));
		}
		if (m_dxBase->GetInputManager()->IsKeyDown("K"))
		{
			if (this->GetComponent<Rigidbody>()->GetAcceleration().y >= 0 && this->GetComponent<Collider>()->GetCollisionStatus())this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -800, 0));
		}
		if (this->GetComponent<Rigidbody>()->GetVelocity().x > 0) transform->SetRotation(Vector3(transform->GetRotation().x, 360, transform->GetRotation().z));
		else if (this->GetComponent<Rigidbody>()->GetVelocity().x < 0) transform->SetRotation(Vector3(transform->GetRotation().x, 0, transform->GetRotation().z));

		if (m_dxBase->GetInputManager()->IsKeyDown("L") && this->GetComponent<Collider>()->GetCollisionStatus() && Vector3::Distance(this->GetTransform()->GetPosition(), capshield->GetTransform()->GetPosition()) < 40 && weaponTimer < 0)
		{
			capshield->endpoint = this->GetTransform()->GetPosition() + Vector3((transform->GetRotation().y == 360) ? 300 : -300, -20, 0);
			weaponTimer = 0.8f;
			capshield->holded = false;
		}
	}
	else
	{
		hurtTime -= _deltaTime;
		this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
	}
	weaponTimer -= _deltaTime;
}

void Player::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	ManageAnimators();
	if (m_dxBase->GetInputManager()->IsKeyDown("P") && dashTime <= 0) dashTime = 0.5f;
	else if (dashTime > 0 && dashTime < 0.3f) this->GetComponent<Rigidbody>()->Move(Vector3((transform->GetRotation().y == 360) ? 500 : -500, 0, 0));
	dashTime -= _deltaTime;
	jumpTime = (this->GetComponent<Collider>()->GetCollisionStatus()) ? 0 : jumpTime + _deltaTime;
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Sit" || this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "SitAttack")
	{
		if (this->GetTransform()->GetScale().y != 60)
		{
			this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + Vector3(0, 30, 0));
			this->GetTransform()->SetScale(Vector3(50, 60, 0));
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
	if (_other->GetAttachedGameObject()->GetTag() == "Shield");
	else if (_other->GetAttachedGameObject()->GetTag() == "EnemyBullet")
	{
		TakeDamage();
		//this->GetComponent<Collider>()->SetCollisionStatus(false);
	}
	else if (_other->GetAttachedGameObject()->GetTag() == "Enemy" || _other->GetAttachedGameObject()->GetTag() == "Boss")
	{
		if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Attack"
			|| this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "SitAttack"
			|| this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "JumpAttack")
		{
			int a = 1;
		}
	}
	else if (_other->GetAttachedGameObject()->GetTag() == "Water")
	{
		GameObject::OnCollisionEnter(_other, _normal);
		if (this->GetComponent<Rigidbody>()->GetAcceleration().y >= 0 && this->GetComponent<Collider>()->GetCollisionStatus())this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -1000, 0));
	}
	else if (_other->GetAttachedGameObject()->GetTag() == "TriggerFirstBoss")
	{
		cutscene = true;
		m_dxBase->SwitchToScene(1);
	}
	else if (_other->GetAttachedGameObject()->GetTag()=="TriggerSecondBoss")
	{
		m_dxBase->SwitchToScene(3);
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
	Animation* throwAnim = new Animation(L"Resources/Captain/Animations/attack.png", "Throw", this->GetComponent<Renderer>(), 1, 2, 0.1f, 1.0f, true);
	Animation* sitAttackAnim = new Animation(L"Resources/Captain/Animations/sit_attack.png", "SitAttack", this->GetComponent<Renderer>(), 1, 2, 0.1f, 1.0f, true);
	Animation* jumpAttack = new Animation(L"Resources/Captain/Animations/jump_attack.png", "JumpAttack", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* sitAnim = new Animation(L"Resources/Captain/Animations/sit.png", "Sit", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* hurtAnim = new Animation(L"Resources/Captain/Animations/hurt.png", "Hurt", this->GetComponent<Renderer>(), 1, 3, 0.1f, 1.0f, true);
	Animation* dashAnim = new Animation(L"Resources/Captain/Animations/dash.png", "Dash", this->GetComponent<Renderer>(), 1, 2, 0.1f, 1.0f, true);

	moveAnim->interupt = true;
	this->GetComponent<Animator>()->AddAnimation(standAnim);
	this->GetComponent<Animator>()->AddAnimation(moveAnim);
	this->GetComponent<Animator>()->AddAnimation(jumpAnim);
	this->GetComponent<Animator>()->AddAnimation(attackAnim);
	this->GetComponent<Animator>()->AddAnimation(sitAttackAnim);
	this->GetComponent<Animator>()->AddAnimation(jumpAttack);
	this->GetComponent<Animator>()->AddAnimation(spinJumpAnim);
	this->GetComponent<Animator>()->AddAnimation(sitAnim);
	this->GetComponent<Animator>()->AddAnimation(throwAnim);
	this->GetComponent<Animator>()->AddAnimation(hurtAnim);
	this->GetComponent<Animator>()->AddAnimation(dashAnim);

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
	this->GetComponent<Animator>()->AddTransition("SitAttack", "Stand", true);
	this->GetComponent<Animator>()->AddTransition("SitAttack", "Move", true);

	this->GetComponent<Animator>()->AddTransition("Sit", "Stand", true);
	this->GetComponent<Animator>()->AddTransition("Sit", "SitAttack", true);

	this->GetComponent<Animator>()->AddTransition("Throw", "Stand", true);

	this->GetComponent<Animator>()->AddTransition("Hurt", "Stand", true);

	this->GetComponent<Animator>()->AddTransition("JumpAttack", "Jump", true);
	this->GetComponent<Animator>()->AddTransition("Dash", "Stand", true);

	this->GetComponent<Animator>()->SetCurrentAnimation(moveAnim);
}

void Player::ManageAnimators()
{
	this->GetComponent<Animator>()->SetBool("Throw", m_dxBase->GetInputManager()->IsKeyDown("L") && this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "Throw" && Vector3::Distance(capshield->GetTransform()->GetPosition(), this->GetTransform()->GetPosition()) < 40);
	this->GetComponent<Animator>()->SetBool("Attack", m_dxBase->GetInputManager()->IsKeyDown("L") && this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "Attack" && Vector3::Distance(capshield->GetTransform()->GetPosition(), this->GetTransform()->GetPosition()) > 50);
	this->GetComponent<Animator>()->SetBool("Sit", m_dxBase->GetInputManager()->IsKeyDown("S") && this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "Sit" && this->GetComponent<Collider>()->GetCollisionStatus());
	this->GetComponent<Animator>()->SetBool("Hurt", this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "Hurt" && hurtTime > 0);
	this->GetComponent<Animator>()->SetBool("Dash", this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "Dash" && (dashTime > 0 && dashTime < 0.3f) && this->GetComponent<Collider>()->GetCollisionStatus());
	this->GetComponent<Animator>()->SetBool("JumpAttack", this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "JumpAttack" &&  m_dxBase->GetInputManager()->IsKeyDown("L") && !this->GetComponent<Collider>()->GetCollisionStatus());

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
		this->GetComponent<Animator>()->SetBool("Sit", "SitAttack", this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "SitAttack" && m_dxBase->GetInputManager()->IsKeyDown("L") && this->GetComponent<Collider>()->GetCollisionStatus());
		this->GetComponent<Animator>()->SetBool("Sit", "Stand", !m_dxBase->GetInputManager()->IsKeyDown("S") && this->GetComponent<Collider>()->GetCollisionStatus());
	}
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "SitAttack")
	{
		this->GetComponent<Animator>()->SetBool("SitAttack", "Sit", m_dxBase->GetInputManager()->IsKeyDown("S") && !m_dxBase->GetInputManager()->IsKeyDown("L"));
		this->GetComponent<Animator>()->SetBool("Sit", "Stand", !m_dxBase->GetInputManager()->IsKeyDown("S") && !m_dxBase->GetInputManager()->IsKeyDown("L"));
	}
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Hurt")
	{
		this->GetComponent<Animator>()->SetBool("Hurt", "Stand", hurtTime <= 0);
	}
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "JumpAttack")
	{
		this->GetComponent<Animator>()->SetBool("JumpAttack", "Jump", !m_dxBase->GetInputManager()->IsKeyDown("L") && !this->GetComponent<Collider>()->GetCollisionStatus());
	}
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Dash")
	{
		this->GetComponent<Animator>()->SetBool("Dash", "Stand", this->GetComponent<Collider>()->GetCollisionStatus() && (dashTime <= 0));
	}
}
