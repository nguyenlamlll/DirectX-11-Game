#include "WizardBoss.h"



WizardBoss::WizardBoss()
{
}

WizardBoss::WizardBoss(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, GameObject * _captain)
{
	loopDirection = 1;
	stateTimeCycle = 0;
	positionIndex = 0;
	positionList = new std::vector<Vector3>();
	Vector3 capPos = _captain->GetTransform()->GetPosition();
	positionList->push_back(capPos + Vector3(200, 0, 0));
	positionList->push_back(capPos + Vector3(200, -200, 0));
	positionList->push_back(capPos + Vector3(-200, -200, 0));
	positionList->push_back(capPos + Vector3(-200, 0, 0));

	m_dxBase = _m_dxBase;
	cap = _captain;

	this->GetTransform()->SetScale(Vector3(100, 100, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));

	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/boss/wizard_1.png"));
	this->AddComponent<Animation>(new Animation("asdsad", this->GetComponent<Renderer>(), 1, 11, 0.1f, 1.0f, true));
	this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));

	//this->GetComponent<Collider>()->SetTrigger(true);
	this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/boss/wizard_1.png", 1, 5);
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

	// STAGE 4
	if (stateTimeCycle > 15.0f)
	{
		//shooting
		this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
	}
	// STAGE 3
	else if (stateTimeCycle > 10.0f)
	{
		
	}
	// STAGE 2
	else if (stateTimeCycle > 5.0f)
	{
		//running
		this->GetComponent<Rigidbody>()->SetKinematic(false);
		this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
	}
	// STAGE 1
	else if (stateTimeCycle > 0)
	{
		this->GetComponent<Rigidbody>()->SetKinematic(true);
		//flying
		if (Vector3::Distance(this->GetTransform()->GetPosition(), positionList->at(positionIndex)) < 5)
		{
			if ((positionIndex == positionList->size() - 1) && loopDirection == 1)
				loopDirection *= -1;
			if ((positionIndex == 0) && loopDirection == -1)
				loopDirection *= -1;
			positionIndex += loopDirection;
			//positionIndex = (positionIndex == positionList->size() - 1) ? 0 : positionIndex + 1;
		}
		else
		{
			Vector3 transformVector = positionList->at(positionIndex) - this->GetTransform()->GetPosition();
			transformVector.Normalize();
			this->GetComponent<Rigidbody>()->Move(transformVector * 400);
			//this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + transformVector * 5);
		}
	}

	stateTimeCycle = (stateTimeCycle > 10.0f) ? 0 : stateTimeCycle + _deltaTime;
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
		if (this->GetTag() == "Boss")
		{
			Player* a = (Player*)(_other->GetAttachedGameObject());
			a->TakeDamage();
		}
	}
}


WizardBoss::~WizardBoss()
{
}
