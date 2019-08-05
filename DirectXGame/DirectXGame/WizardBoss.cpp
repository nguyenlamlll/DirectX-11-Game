#include "WizardBoss.h"



WizardBoss::WizardBoss()
{
}

WizardBoss::WizardBoss(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, GameObject * _captain)
{
	hurtTime = 0;
	loopDirection = 1;
	stateTimeCycle = 0;
	positionIndex = 0;
	bulletTimer = 0;
	positionList = new std::vector<Vector3>();
	Vector3 capPos = _captain->GetTransform()->GetPosition();
	transform->SetPosition(Vector3(900, 660, 0));
	Vector3 currPos = transform->GetPosition();
	positionList->push_back(currPos + Vector3(0, 0, 0));
	positionList->push_back(currPos + Vector3(0, -450, 0));
	positionList->push_back(currPos + Vector3(-800, -450, 0));
	positionList->push_back(currPos + Vector3(-800, 0, 0));

	m_dxBase = _m_dxBase;
	cap = _captain;

	this->GetTransform()->SetScale(Vector3(100, 100, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));

	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/boss/stand.png"));
	this->AddComponent<Animator>(new Animator(this->GetComponent<Renderer>()));
	AddAnimation();
	this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->GetComponent<Rigidbody>()->SetKinematic(true);

	this->SetTag("Boss");
}

void WizardBoss::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void WizardBoss::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	if (cap->GetTransform()->GetPosition().x - this->GetTransform()->GetPosition().x > 0) this->GetTransform()->SetRotation(Vector3(0,360,0));
	else this->GetTransform()->SetRotation(Vector3(0,0,0));

	if (stateTimeCycle > 10.0f)
	{
		// shooting
		this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
	}
	// STAGE 2
	else if (stateTimeCycle > 5.0f)
	{
		if (Vector3::Distance(this->GetTransform()->GetPosition(), positionList->at(positionIndex)) > 5 && this->GetComponent<Rigidbody>()->IsKinematic())
		{
			//this->GetComponent<Rigidbody>()->SetKinematic(true);
			Vector3 transformVector = positionList->at(positionIndex) - this->GetTransform()->GetPosition();
			transformVector.Normalize();
			this->GetComponent<Rigidbody>()->Move(transformVector * 400);
		}
		else
		{
			this->GetComponent<Rigidbody>()->SetKinematic(false);
		}
		if (!this->GetComponent<Rigidbody>()->IsKinematic())
		{
			// RUN
			this->GetComponent<Rigidbody>()->SetKinematic(false);
			this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
			//SHOOT
			if (bulletTimer > 1.0f && this->GetComponent<Collider>()->GetCollisionStatus())
			{
				this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));

				//shooting code
				float directionX = cap->GetTransform()->GetPosition().x - this->GetTransform()->GetPosition().x;
				if (directionX > 10) directionX = 400;
				else if (directionX < -10) directionX = -400;
				else directionX = 0;
				Bullet* bullet = new Bullet(L"Resources/Captain/Animations/boss/single_bullet.png", m_dxBase, this->GetTransform()->GetPosition(), Vector3(3, 3, 1), Vector3(directionX, 0, 0));
				bullet->SetTag("EnemyBullet");
				bullet->AddComponent<Rigidbody>(new Rigidbody(bullet));
				bullet->GetComponent<Rigidbody>()->SetKinematic(true);
				if (cap->GetTransform()->GetPosition().x - bullet->GetTransform()->GetPosition().x > 0) bullet->GetTransform()->SetRotation(Vector3(0, 360, 0));
				else this->GetTransform()->SetRotation(Vector3(0, 0, 0));
				m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->push_back(bullet);
				//this->AddChild(bullet);
				bulletTimer = 0;

			}
		}
	}
	// STAGE 1
	else if (stateTimeCycle > 0)
	{
		this->GetComponent<Rigidbody>()->SetKinematic(true);
		//flying
		if (Vector3::Distance(this->GetTransform()->GetPosition(), positionList->at(positionIndex)) < 5)
		{
			if ((positionIndex == positionList->size() - 1) && loopDirection == 1) loopDirection *= -1;
			if ((positionIndex == 0) && loopDirection == -1) loopDirection *= -1;
			positionIndex += loopDirection;
			//positionIndex = (positionIndex == positionList->size() - 1) ? 0 : positionIndex + 1;
		}
		else
		{
			Vector3 transformVector = positionList->at(positionIndex) - this->GetTransform()->GetPosition();
			transformVector.Normalize();
			this->GetComponent<Rigidbody>()->Move(transformVector * 400);
			if (this->GetTransform()->GetPosition().y < cap->GetTransform()->GetPosition().y && abs(this->GetTransform()->GetPosition().x - cap->GetTransform()->GetPosition().x) < 10)
			{
				//SHOOT
				if (bulletTimer > 1.0f)
				{
					Bullet* bullet = new Bullet(L"Resources/Captain/Animations/boss/bullet3.png", m_dxBase, this->GetTransform()->GetPosition(), Vector3(3, 3, 1), Vector3(0, 400, 0));
					//bullet->GetTransform()->SetRotation(Vector3(0.4f, 0, 0));
					bullet->SetTag("EnemyBullet");
					bullet->AddComponent<Rigidbody>(new Rigidbody(bullet));
					bullet->GetComponent<Rigidbody>()->SetKinematic(true);
					if (cap->GetTransform()->GetPosition().x - bullet->GetTransform()->GetPosition().x > 0) bullet->GetTransform()->SetRotation(Vector3(0, 360, 0));
					else this->GetTransform()->SetRotation(Vector3(0, 0, 0));
					m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->push_back(bullet);
					//this->AddChild(bullet);
					bulletTimer = 0;
				}
			}
		}
	}

	ManageAnimation();
	bulletTimer += _deltaTime;
	stateTimeCycle = (stateTimeCycle > 15.0f) ? 0 : stateTimeCycle + _deltaTime;
	if (hurtTime > 0 && hurtTime < 0.5)
	{
		m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->erase(std::remove(m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->begin(), m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->end(), this), m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->end());
		delete this;
	}
	else if (hurtTime > 0) hurtTime -= _deltaTime;
}

void WizardBoss::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void WizardBoss::Render()
{
	GameObject::Render();
}

void WizardBoss::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
	if (_other->GetAttachedGameObject()->GetTag() != "Player") GameObject::OnCollisionEnter(_other, _normal);
	else if (_other->GetAttachedGameObject()->GetTag() == "Player")
	{
		if (_other->GetAttachedGameObject()->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Attack"
			|| _other->GetAttachedGameObject()->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "SitAttack"
			|| _other->GetAttachedGameObject()->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "JumpAttack"
			|| _other->GetAttachedGameObject()->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Dash")
		{
			hurtTime = 1.0f;
		}
		else
		{
			Player* a = (Player*)(_other->GetAttachedGameObject());
			a->TakeDamage();
		}
	}
}


WizardBoss::~WizardBoss()
{
}

void WizardBoss::AddAnimation()
{
	//Animation* moveAnim = new Animation(L"Resources/Captain/Animations/boss/wizard_1.png", "Move", this->GetComponent<Renderer>(), 1, 3, 0.1f, 1.0f, true);
	Animation* standAnim = new Animation(L"Resources/Captain/Animations/boss/stand.png", "Stand", this->GetComponent<Renderer>(), 1, 2, 0.1f, 1.0f, true);
	Animation* jumpAnim = new Animation(L"Resources/Captain/Animations/boss/fly.png", "Jump", this->GetComponent<Renderer>(), 1, 4, 0.1f, 1.0f, true);
	Animation* attackAnim = new Animation(L"Resources/Captain/Animations/boss/attack.png", "Attack", this->GetComponent<Renderer>(), 1, 3, 0.1f, 1.0f, true);
	Animation* dieAnim = new Animation(L"Resources/Captain/Animations/boss/die.png", "Die", this->GetComponent<Renderer>(), 1, 3, 0.1f, 1.0f, true);
	//Animation* attackAnim = new Animation(L"Resources/Captain/Animations/boss/wizard_1.png", "Attack", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	//Animation* dieAnim = new Animation(L"Resources/Captain/Animations/boss/wizard_1.png", "Die", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	//moveAnim->interupt = true;
	this->GetComponent<Animator>()->AddAnimation(standAnim);
	//this->GetComponent<Animator>()->AddAnimation(moveAnim);
	this->GetComponent<Animator>()->AddAnimation(jumpAnim);
	this->GetComponent<Animator>()->AddAnimation(attackAnim);
	this->GetComponent<Animator>()->AddAnimation(dieAnim);
	//this->GetComponent<Animator>()->AddAnimation(attackAnim);
	//this->GetComponent<Animator>()->AddAnimation(dieAnim);
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

	this->GetComponent<Animator>()->SetCurrentAnimation(standAnim);
}

void WizardBoss::ManageAnimation()
{

	this->GetComponent<Animator>()->SetBool("Jump", !this->GetComponent<Collider>()->GetCollisionStatus() && this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "Jump");
	if (stateTimeCycle > 5.0f && this->GetComponent<Collider>()->GetCollisionStatus())
	{
		int aasdasd = 1;
	}
	this->GetComponent<Animator>()->SetBool("Attack", stateTimeCycle > 5.0f && this->GetComponent<Collider>()->GetCollisionStatus());
	if (this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Attack")
	{
		this->GetComponent<Animator>()->SetBool("Attack", "Stand", stateTimeCycle < 5.0f && this->GetComponent<Collider>()->GetCollisionStatus());
	}
	else
	{
		this->GetComponent<Animator>()->SetBool("Stand", this->GetComponent<Collider>()->GetCollisionStatus() && this->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() != "Stand");
	}

}
