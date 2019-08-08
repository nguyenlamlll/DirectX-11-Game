#include "Barrel.h"



Barrel::Barrel()
{

}

Barrel::Barrel(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, GameObject * _boss)
{
	boss = _boss;
	m_dxBase = _m_dxBase;
	this->SetActive(true);
	this->GetTransform()->SetScale(Vector3(78, 54, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/mini_boss/barrel.png"));
	//this->AddComponent<Animator>(new Animator(this->GetComponent<Renderer>()));
	Addanimation();
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	//this->GetComponent<Collider>()->SetTrigger(true);
	this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->GetComponent<Rigidbody>()->SetKinematic(true);
	this->SetTag("Barrel");
	direction = Vector3(10, 0, 0);
}

void Barrel::PreUpdate(float _deltaTime)
{
	if (this->IsActive())
	{
		GameObject::PreUpdate(_deltaTime);
	}
}

void Barrel::Update(float _deltaTime)
{
	if (this->IsActive())GameObject::Update(_deltaTime);
}

void Barrel::LateUpdate(float _deltaTime)
{
	if (this->IsActive())
	{
		GameObject::LateUpdate(_deltaTime);
		this->GetComponent<Rigidbody>()->Move(direction);
	}
}

void Barrel::Render()
{
	if (this->IsActive()) GameObject::Render();
}

void Barrel::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
	if (_other->GetAttachedGameObject()->GetTag() == "Player")
	{
		if (this->IsActive() && this->GetComponent<Rigidbody>()->IsKinematic() && _other->GetAttachedGameObject()->GetComponent<Animator>()->GetCurrentAnimation()->GetAnimationName() == "Kick")
		{
			this->SetActive(false);
			SecondBoss* cloneBoss = (SecondBoss*)boss;
			cloneBoss->health -= 1;
		}
	}
	if (_other->GetAttachedGameObject()->GetTag() != "Player" && _other->GetAttachedGameObject()->GetTag() != "Boss")
	{
		GameObject::OnCollisionEnter(_other, _normal);
		this->SetActive(false);
	}
}


Barrel::~Barrel()
{
}

void Barrel::Addanimation()
{
}

void Barrel::ManageAnimation()
{
}
