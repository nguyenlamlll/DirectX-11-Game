#include "WizardBoss.h"



WizardBoss::WizardBoss()
{
}

WizardBoss::WizardBoss(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, GameObject * _captain)
{
	Vector3 temPos = _captain->GetTransform()->GetPosition();
	m_dxBase = _m_dxBase;
	cap = _captain;

	this->GetTransform()->SetPosition(temPos + Vector3(100,0,0));
	this->GetTransform()->SetScale(Vector3(100, 100, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));
	
	uprightPos = temPos + Vector3(0, -100, 0);
	upleftPos = uprightPos + Vector3(-100, 0, 0);

	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/boss/wizard_1.png"));
	this->AddComponent<Animation>(new Animation("asdsad",this->GetComponent<Renderer>(), 1, 11, 0.1f, 1.0f, true));
	//this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));

	this->GetComponent<Collider>()->SetTrigger(true);
	this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/boss/wizard_1.png", 1, 5);
	//this->GetComponent<Rigidbody>()->SetKinematic(true);
}

void WizardBoss::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void WizardBoss::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	Vector3 tempPos = this->GetTransform()->GetPosition();
	if (tempPos.y > uprightPos.y) this->GetTransform()->SetPosition(tempPos + Vector3(0, -4, 0));
	else
	{
		if (this->GetTransform()->GetPosition().x > upleftPos.x) this->GetTransform()->SetPosition(tempPos + Vector3(-4, 0, 0));
	}
	//this->GetTransform()->SetPosition(tempPos + Vector3(-2, 0, 0));
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
	GameObject::OnCollisionEnter(_other, _normal);
}


WizardBoss::~WizardBoss()
{
}
