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
	transform->SetPosition(Vector3(900, 660, 0));
	positionList->push_back(transform->GetPosition() + Vector3(-800, 0, 0));
	positionList->push_back(transform->GetPosition());

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
				float directionX = captain->GetTransform()->GetPosition().x - this->GetTransform()->GetPosition().x;
				if (directionX > 10) directionX = 400;
				else if (directionX < -10) directionX = -400;
				else directionX = 0;
				Bullet* bullet = new Bullet(L"Resources/Captain/Animations/boss/single_bullet.png", m_dxBase, this->GetTransform()->GetPosition(), Vector3(3, 3, 1), Vector3(directionX, 0, 0));
				bullet->SetTag("EnemyBullet");
				bullet->AddComponent<Rigidbody>(new Rigidbody(bullet));
				bullet->GetComponent<Rigidbody>()->SetKinematic(true);
				if (captain->GetTransform()->GetPosition().x - bullet->GetTransform()->GetPosition().x > 0) bullet->GetTransform()->SetRotation(Vector3(0, 360, 0));
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
			if (this->GetTransform()->GetPosition().y < captain->GetTransform()->GetPosition().y && abs(this->GetTransform()->GetPosition().x - captain->GetTransform()->GetPosition().x) < 10)
			{
				//SHOOT
				if (bulletTimer > 1.0f)
				{
					Bullet* bullet = new Bullet(L"Resources/Captain/Animations/boss/bullet3.png", m_dxBase, this->GetTransform()->GetPosition(), Vector3(3, 3, 1), Vector3(0, 400, 0));
					//bullet->GetTransform()->SetRotation(Vector3(0.4f, 0, 0));
					bullet->SetTag("EnemyBullet");
					bullet->AddComponent<Rigidbody>(new Rigidbody(bullet));
					bullet->GetComponent<Rigidbody>()->SetKinematic(true);
					if (captain->GetTransform()->GetPosition().x - bullet->GetTransform()->GetPosition().x > 0) bullet->GetTransform()->SetRotation(Vector3(0, 360, 0));
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
		m_dxBase->SwitchToScene(2);
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
	GameObject::OnCollisionEnter(_other,_normal);
}


SecondBoss::~SecondBoss()
{
}

void SecondBoss::AddAnimation()
{
}

void SecondBoss::ManageAnimation()
{
}
