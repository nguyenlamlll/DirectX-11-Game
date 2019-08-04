#include "Shield.h"
#include "Enemy.h"
#include "WizardBoss.h"


Shield::Shield()
{
}

Shield::Shield(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, GameObject * _captain)
{
	holded = true;
	startpoint = endpoint = Vector3(0, 0, 0);
	m_dxBase = _m_dxBase;
	captain = _captain;
	this->GetTransform()->SetPosition(_captain->GetTransform()->GetPosition());
	this->GetTransform()->SetScale(Vector3(51, 60, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/shield_strait.png"));
	this->AddComponent<Animator>(new Animator(this->GetComponent<Renderer>()));
	Addanimation();
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	//this->GetComponent<Collider>()->SetTrigger(true);
	this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->GetComponent<Rigidbody>()->SetKinematic(true);
	this->SetTag("Shield");
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
	ManageAnimation();
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
		offset.x = 30;
	}
	else
	{
		this->GetTransform()->SetRotation(Vector3(0, 0, 0));
		offset.x = -30;
	}
	startpoint = captain->GetTransform()->GetPosition() + offset;

	/*Vector3 pos = this->GetTransform()->GetPosition();
	pos.y = captain->GetTransform()->GetPosition().y;
	if (direction.x < 0)
	{
		Vector3 as = captain->GetTransform()->GetPosition() - this->GetTransform()->GetPosition();
		as.Normalize();
		this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + as * 15);
	}
	else
	{
		this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + direction);
	}
	if (pos.x > targetRightside.x && direction.x > 0) direction.x *= -1;
	else if (pos.x < targetLeftSide.x && direction.x < 0) this->GetTransform()->SetPosition(captain->GetTransform()->GetPosition() + offset);*/
	if (Vector3::Distance(this->GetTransform()->GetPosition(), endpoint) > 5)
	{
		/*if (endpoint == startpoint)
		{
			this->GetTransform()->SetPosition(endpoint);
		}
		else*/
		{
			Vector3 as = endpoint - this->GetTransform()->GetPosition();
			as.Normalize();
			//this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + as * 15);
			this->GetComponent<Rigidbody>()->Move(as * 600);
		}
	}
	else
	{
		if (endpoint != startpoint) endpoint = startpoint;
		else
		{
			holded = true;
			/*this->GetTransform()->SetPosition(startpoint);
			this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));*/
		}
	}
	if (holded)
	{
		this->GetTransform()->SetPosition(startpoint);
		this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
	}
}

void Shield::Render()
{
	GameObject::Render();
}

void Shield::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
	//GameObject::OnCollisionEnter(_other, _normal);
	if (this->GetComponent<Rigidbody>()->GetVelocity().x != 0)
	{
		if (_other->GetAttachedGameObject()->GetTag() == "Boss")
		{
			WizardBoss* a = (WizardBoss*)(_other->GetAttachedGameObject());
			a->TakeDamage();
		}
		if (_other->GetAttachedGameObject()->GetTag() == "Enemy")
		{
			Enemy* a = (Enemy*)(_other->GetAttachedGameObject());
			a->TakeDamage();
		}
	}
}

void Shield::SetTarget(Vector3 _target)
{
}

void Shield::Addanimation()
{
	Animation* stillAnim = new Animation(L"Resources/Captain/Animations/shield_still.png", "Still", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	Animation* flyAnim = new Animation(L"Resources/Captain/Animations/shield_fly.png", "Fly", this->GetComponent<Renderer>(), 1, 1, 0.1f, 1.0f, true);
	this->GetComponent<Animator>()->AddAnimation(stillAnim);
	this->GetComponent<Animator>()->AddAnimation(flyAnim);
	//this->GetComponent<Animator>()->AddTransition("Stand", "Move", true);
	this->GetComponent<Animator>()->SetCurrentAnimation(stillAnim);
}

void Shield::ManageAnimation()
{
	this->GetComponent<Animator>()->SetBool("Still", Vector3::Distance(this->GetTransform()->GetPosition(), startpoint) < 10);
	this->GetComponent<Animator>()->SetBool("Fly", Vector3::Distance(this->GetTransform()->GetPosition(), startpoint) > 10);

}
