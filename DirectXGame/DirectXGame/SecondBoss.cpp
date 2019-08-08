#include "SecondBoss.h"



SecondBoss::SecondBoss()
{
}

SecondBoss::SecondBoss(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, GameObject * _captain)
{
	m_dxBase = _m_dxBase;
	captain = _captain;

	hurtTime = 0;
	loopDirection = 1;
	stateTimeCycle = 0;
	positionIndex = 0;
	bulletTimer = 0;

	positionList = new std::vector<Vector3>();
	transform->SetPosition(Vector3(900, 550, 0));
	positionList->push_back(transform->GetPosition() + Vector3(-800, 0, 0));
	positionList->push_back(transform->GetPosition());

	this->GetTransform()->SetScale(Vector3(100, 100, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));

	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/boss/stand.png"));
	this->AddComponent<Animator>(new Animator(this->GetComponent<Renderer>()));
	AddAnimation();
	this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	//this->GetComponent<Rigidbody>()->SetKinematic(true);

	this->SetTag("Boss");
}

void SecondBoss::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void SecondBoss::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	if (captain->GetTransform()->GetPosition().x - this->GetTransform()->GetPosition().x > 0) this->GetTransform()->SetRotation(Vector3(0, 360, 0));
	else this->GetTransform()->SetRotation(Vector3(0, 0, 0));

	

	if (stateTimeCycle > 10.0f)
	{
		if (Vector3::Distance(this->GetTransform()->GetPosition(), positionList->at(positionIndex)) < 10)
			positionIndex = (positionIndex == positionList->size() - 1) ? 0 : positionIndex + 1;
		else
		{
			Vector3 transformVector = positionList->at(positionIndex) - this->GetTransform()->GetPosition();
			transformVector.Normalize();
			transformVector.y = 0;
			this->GetComponent<Rigidbody>()->Move(transformVector * 100);
		}
	}
	// STAGE 2
	else if (stateTimeCycle > 5.0f)
	{
		this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
		//run to another spot
	}
	// STAGE 1
	else if (stateTimeCycle > 0)
	{
		if (stateTimeCycle < 3.0f)
		{
			//lift barrel
		}
		else
		{
			//throw
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

void SecondBoss::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void SecondBoss::Render()
{
	GameObject::Render();
}

void SecondBoss::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
	if (_other->GetAttachedGameObject()->GetTag() != "Player" || _other->GetAttachedGameObject()->GetTag() != "Shield")
	{
		GameObject::OnCollisionEnter(_other, _normal);
	}
}


SecondBoss::~SecondBoss()
{
}

void SecondBoss::AddAnimation()
{
	Animation* moveAnim = new Animation(L"Resources/Captain/Animations/mini_boss/move.png", "Move", this->GetComponent<Renderer>(), 1, 3, 0.1f, 1.0f, true);
	Animation* standAnim = new Animation(L"Resources/Captain/Animations/mini_boss/stand.png", "Stand", this->GetComponent<Renderer>(), 1, 2, 0.1f, 1.0f, true);
	Animation* attackAnim = new Animation(L"Resources/Captain/Animations/mini_boss/attack.png", "Attack", this->GetComponent<Renderer>(), 1, 3, 0.1f, 1.0f, true);
	Animation* dieAnim = new Animation(L"Resources/Captain/Animations/mini_boss/mini_boss12.png", "Die", this->GetComponent<Renderer>(), 1, 3, 0.1f, 1.0f, true);
	moveAnim->interupt = true;
	this->GetComponent<Animator>()->AddAnimation(standAnim);
	this->GetComponent<Animator>()->AddAnimation(moveAnim);
	this->GetComponent<Animator>()->AddAnimation(attackAnim);
	this->GetComponent<Animator>()->AddAnimation(dieAnim);
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

	this->GetComponent<Animator>()->SetCurrentAnimation(moveAnim);
}

void SecondBoss::ManageAnimation()
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
