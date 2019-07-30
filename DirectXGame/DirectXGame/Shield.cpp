#include "Shield.h"



Shield::Shield()
{
}

Shield::Shield(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, GameObject * _captain)
{
	m_dxBase = _m_dxBase;
	captain = _captain;
	this->GetTransform()->SetPosition(_captain->GetTransform()->GetPosition());
	this->GetTransform()->SetScale(Vector3(51, 60, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/shield_1.png"));
	//this->AddComponent<Animation>(new Animation(this->GetComponent<Renderer>(), 1, 4, 0.03f, 1.0f, true));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->GetComponent<Collider>()->SetTrigger(true);

	direction = Vector3(10, 0, 0);
}


Shield::~Shield()
{
}

void Shield::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void Shield::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
}

void Shield::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
	targetLeftSide = captain->GetTransform()->GetPosition();
	targetRightside = captain->GetTransform()->GetPosition() + Vector3(300, 0, 0);
	Vector3 offset = Vector3(0, -20, 0);
	if (captain->GetTransform()->GetRotation().y > 120)
	{
		this->GetTransform()->SetRotation(Vector3(0, 360, 0));
		offset.x = 20;
	}
	else
	{
		this->GetTransform()->SetRotation(Vector3(0, 0, 0));
		offset.x = -20;
	}
	Vector3 pos = this->GetTransform()->GetPosition();
	pos.y = captain->GetTransform()->GetPosition().y;
	if (pos.x > targetRightside.x && direction.x > 0) direction.x *= -1;
	else if (pos.x < targetLeftSide.x && direction.x < 0) direction.x *= -1;
	if (direction.x < 0)
	{
		/*if (captain->GetTransform()->GetPosition().y - this->GetTransform()->GetPosition().y > 10) direction.y = 10;
		else if(captain->GetTransform()->GetPosition().y - this->GetTransform()->GetPosition().y<-10)direction.y = -10;
		else direction.y = 0;*/
		//this->GetTransform()->SetPosition(this->GetTransform()->GetPosition().Lerp(this->GetTransform()->GetPosition(), captain->GetTransform()->GetPosition(), _deltaTime*5));
		Vector3 as = captain->GetTransform()->GetPosition() - this->GetTransform()->GetPosition();
		as.Normalize();
		this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + as*10);
	}
	else this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + direction);
	//this->GetTransform()->SetPosition(captain->GetTransform()->GetPosition() + offset);
}

void Shield::Render()
{
	GameObject::Render();
}

void Shield::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
	GameObject::OnCollisionEnter(_other, _normal);
}

void Shield::SetTarget(Vector3 _target)
{
}
