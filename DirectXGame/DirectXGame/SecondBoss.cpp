#include "SecondBoss.h"



SecondBoss::SecondBoss()
{
}

SecondBoss::SecondBoss(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, GameObject * _captain)
{
	triggered = false;
	health = 4;
	m_dxBase = _m_dxBase;
	captain = _captain;
	barrel = NULL;
	hurtTime = 0;
	loopDirection = 1;
	stateTimeCycle = 0;
	positionIndex = 0;
	bulletTimer = 0;

	positionList = new std::vector<Vector3>();
	transform->SetPosition(Vector3(800, 550, 0));
	positionList->push_back(transform->GetPosition() + Vector3(-600, 0, 0));
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

	if (stateTimeCycle > 14.0f)
	{
		if (Vector3::Distance(this->GetTransform()->GetPosition(), positionList->at(positionIndex)) < 10)
			positionIndex = (positionIndex == positionList->size() - 1) ? 0 : positionIndex + 1;
		else
		{
			Vector3 transformVector = positionList->at(positionIndex) - this->GetTransform()->GetPosition();
			this->GetTransform()->SetRotation(Vector3(0, transformVector.x > 0 ? 360 : 0, 0));
			transformVector.Normalize();
			transformVector.y = 0;
			this->GetComponent<Rigidbody>()->Move(transformVector * 100);
		}

		if (bulletTimer > 2.5f && this->GetComponent<Collider>()->GetCollisionStatus())
		{
			//shooting code
			float directionX = positionList->at(positionIndex).x - this->GetTransform()->GetPosition().x;
			if (directionX > 10) directionX = 400;
			else if (directionX < -10) directionX = -400;
			else directionX = 0;
			Bullet* bullet = new Bullet(L"Resources/Captain/Animations/mini_boss/bullet.png", m_dxBase, this->GetTransform()->GetPosition(), Vector3(3, 3, 1), Vector3(directionX, 0, 0));
			bullet->SetTag("BossBullet");
			bullet->AddComponent<Rigidbody>(new Rigidbody(bullet));
			bullet->GetComponent<Rigidbody>()->SetKinematic(true);
			if (captain->GetTransform()->GetPosition().x - bullet->GetTransform()->GetPosition().x > 0) bullet->GetTransform()->SetRotation(Vector3(0, 360, 0));
			else this->GetTransform()->SetRotation(Vector3(0, 0, 0));
			m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->push_back(bullet);
			//this->AddChild(bullet);
			bulletTimer = 0;
		}
	}
	else if (stateTimeCycle > 12.0f)
	{
		this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
	}
	else if (stateTimeCycle > 7.2f)
	{
		if (stateTimeCycle < 7.5f)
		{
			if (Vector3::Distance(this->GetTransform()->GetPosition(), positionList->at(positionIndex)) < 10) positionIndex = (positionIndex == positionList->size() - 1) ? 0 : positionIndex + 1;
		}
		else
		{
			if (Vector3::Distance(this->GetTransform()->GetPosition(), positionList->at(positionIndex)) > 10)
			{
				Vector3 transformVector = positionList->at(positionIndex) - this->GetTransform()->GetPosition();
				transformVector.Normalize();
				transformVector.y = 0;
				this->GetComponent<Rigidbody>()->Move(transformVector * 80);
			}
			else this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
		}
	}
	else if (stateTimeCycle > 6.0f)
	{
		this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
		// shoot
		if (bulletTimer > 1.0f && this->GetComponent<Collider>()->GetCollisionStatus())
		{
			//shooting code
			float directionX = captain->GetTransform()->GetPosition().x - this->GetTransform()->GetPosition().x;
			if (directionX > 10) directionX = 400;
			else if (directionX < -10) directionX = -400;
			else directionX = 0;
			Bullet* bullet = new Bullet(L"Resources/Captain/Animations/mini_boss/bullet.png", m_dxBase, this->GetTransform()->GetPosition(), Vector3(3, 3, 1), Vector3(directionX, 0, 0));
			bullet->SetTag("BossBullet");
			bullet->AddComponent<Rigidbody>(new Rigidbody(bullet));
			bullet->GetComponent<Rigidbody>()->SetKinematic(true);
			if (captain->GetTransform()->GetPosition().x - bullet->GetTransform()->GetPosition().x > 0) bullet->GetTransform()->SetRotation(Vector3(0, 360, 0));
			else this->GetTransform()->SetRotation(Vector3(0, 0, 0));
			m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->push_back(bullet);
			//this->AddChild(bullet);
			bulletTimer = 0;
		}
	}
	else if (stateTimeCycle > 4.0f)
	{
		this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
	}
	else if (stateTimeCycle > 0)
	{
		this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
		if (stateTimeCycle < 0.1f)
		{
			if (barrel == NULL)
			{
				barrel = new Barrel(m_dxBase, this);
				m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->push_back(barrel);
			}
			else
			{
				if (!barrel->IsActive()) barrel->SetActive(true);
				Barrel* cloneBarrel = (Barrel*)barrel;
				cloneBarrel->GetComponent<Rigidbody>()->SetKinematic(true);
				cloneBarrel->direction = Vector3(0, 0, 0);
				barrel->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + Vector3(0, -100, 0));
			}
		}
		else if (stateTimeCycle < 3.8f)
		{
			if (!barrel->IsActive()) stateTimeCycle = 4.0f;
			Vector3 acc = barrel->GetComponent<Rigidbody>()->GetAcceleration();
			barrel->GetComponent<Rigidbody>()->AddForce(acc + acc * -1);
			barrel->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + Vector3(0, -100, 0));
		}
		else if (stateTimeCycle < 4.0f)
		{
			if (barrel->IsActive())
			{
				barrel->GetComponent<Rigidbody>()->SetKinematic(false);
				if (barrel->GetComponent<Rigidbody>()->GetVelocity().y == 0)barrel->GetComponent<Rigidbody>()->AddForce(Vector3(0, -400, 0));
				Vector3 dir = captain->GetTransform()->GetPosition() - this->GetTransform()->GetPosition();
				dir.y = 0;
				dir.Normalize();
				Barrel* cloneBarrel = (Barrel*)barrel;
				cloneBarrel->direction = dir * 120;
			}
		}
	}

	ManageAnimation();
	bulletTimer += _deltaTime;
	if (health > 2)stateTimeCycle = (stateTimeCycle > 12.0f) ? 0 : stateTimeCycle + _deltaTime;
	else
	{
		if (!triggered)
		{
			stateTimeCycle = 10.0f;
			triggered = true;
		}
		stateTimeCycle = (stateTimeCycle > 119.0f) ? 14.0f : stateTimeCycle + _deltaTime;
	}
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

	if (health > 2)
	{
		if (_other->GetAttachedGameObject()->GetTag() == "Barrel");
		else if (_other->GetAttachedGameObject()->GetTag() != "Player" || _other->GetAttachedGameObject()->GetTag() != "Shield")
		{
			GameObject::OnCollisionEnter(_other, _normal);
		}
	}
	else
	{
		if (_other->GetAttachedGameObject()->GetTag() == "Barrel");
		else if (_other->GetAttachedGameObject()->GetTag() == "Shield")
		{
			health -= 0.5f;
			if (health <= 0) hurtTime = 1.0f;
		}
		else GameObject::OnCollisionEnter(_other, _normal);
	}
}


SecondBoss::~SecondBoss()
{
}

void SecondBoss::AddAnimation()
{
	Animation* moveAnim = new Animation(L"Resources/Captain/Animations/mini_boss/move.png", "Move", this->GetComponent<Renderer>(), 1, 3, 0.1f, 1.0f, true);
	Animation* moveShootAnim = new Animation(L"Resources/Captain/Animations/mini_boss/move_shoot.png", "MoveShoot", this->GetComponent<Renderer>(), 1, 3, 0.1f, 1.0f, true);
	Animation* standAnim = new Animation(L"Resources/Captain/Animations/mini_boss/stand.png", "Stand", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* liftAnim = new Animation(L"Resources/Captain/Animations/mini_boss/lift.png", "Lift", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* throwAnim = new Animation(L"Resources/Captain/Animations/mini_boss/throw.png", "Throw", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* shootAnim = new Animation(L"Resources/Captain/Animations/mini_boss/shoot.png", "Shoot", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* dieAnim = new Animation(L"Resources/Captain/Animations/mini_boss/die.png", "Die", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	this->GetComponent<Animator>()->AddAnimation(standAnim);
	this->GetComponent<Animator>()->AddAnimation(moveAnim);
	this->GetComponent<Animator>()->AddAnimation(shootAnim);
	this->GetComponent<Animator>()->AddAnimation(dieAnim);
	this->GetComponent<Animator>()->AddAnimation(moveShootAnim);
	this->GetComponent<Animator>()->AddAnimation(liftAnim);
	this->GetComponent<Animator>()->AddAnimation(throwAnim);

	this->GetComponent<Animator>()->SetCurrentAnimation(moveAnim);
}

void SecondBoss::ManageAnimation()
{
	if (hurtTime > 0.5f) this->GetComponent<Animator>()->SetBool("Die", true);
	else
	{
		if (stateTimeCycle > 14.0f)this->GetComponent<Animator>()->SetBool("MoveShoot", true);
		else if (stateTimeCycle > 12.0f)this->GetComponent<Animator>()->SetBool("Stand", true);
		else if (stateTimeCycle > 7.2f) this->GetComponent<Animator>()->SetBool("Move", true);
		else if (stateTimeCycle > 6.0f)
		{
			this->GetComponent<Animator>()->SetBool("Shoot", true);
		}
		else if (stateTimeCycle > 4.0f) this->GetComponent<Animator>()->SetBool("Stand", true);
		else if (stateTimeCycle > 0)
		{
			if (stateTimeCycle < 3.8f)
			{
				this->GetComponent<Animator>()->SetBool("Lift", barrel->IsActive());
				this->GetComponent<Animator>()->SetBool("Hurt", !barrel->IsActive());
			}
			else if (stateTimeCycle < 4.0f)
			{
				this->GetComponent<Animator>()->SetBool("Throw", barrel->IsActive());
			}
		}
	}
}
