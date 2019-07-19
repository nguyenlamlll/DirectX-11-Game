#include "Player.h"

Player::Player(std::shared_ptr<DirectXCore::DxBase> _m_dxBase)
{
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetPosition(Vector3(100, 500, 0));
	this->GetTransform()->SetScale(Vector3(96, 120, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));
	this->AddComponent<Renderer>(new Renderer(_m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/stand.png"));
	this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->AddComponent<Animation>(new Animation(this->GetComponent<Renderer>(), 1, 11, 0.1f, 1.0f, true));
	std::vector<std::string>* stringStates = new std::vector<std::string>();
	stringStates->push_back("jump");
	stringStates->push_back("jumpflip");
	stringStates->push_back("run");
	stringStates->push_back("runflip");
	stringStates->push_back("shoot");
	stringStates->push_back("ground");
	stringStates->push_back("stand");
	stringStates->push_back("sweep");
	stringStates->push_back("sweepflip");
	this->AddComponent<State>(new State(this, *stringStates));
	this->GetComponent<Rigidbody>()->SetGravity(Vector3(0, 30, 0));
	cutscene = false;
	weaponTimer = 0;
}

void Player::PreUpdate(float _deltaTime)
{
	cutscene = false;
	GameObject::PreUpdate(_deltaTime);
	Rigidbody* getrigid = this->GetComponent<Rigidbody>();
	
	
	if (m_dxBase->GetInputManager()->IsKeyDown("L") && weaponTimer < 0)
	{
		if (!this->GetComponent<Collider>()->GetCollisionStatus()) this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/kick.png", 1, 1);
		else this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/attack.png", 1, 2);
		weaponTimer = 0.5;
	}
	weaponTimer -= _deltaTime;

	if (this->GetComponent<Collider>()->GetCollisionStatus())
	{
		if (m_dxBase->GetInputManager()->IsKeyDown("W"))
		{
			this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/lookup.png", 1, 1);
		}
		else if (m_dxBase->GetInputManager()->IsKeyDown("S"))
		{
			this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/sit.png", 1, 1);
		}
		else
		{
			if (m_dxBase->GetInputManager()->IsKeyDown("D"))
			{
				this->GetComponent<Rigidbody>()->Move(Vector3(160, 0, 0));
				if (weaponTimer < 0)  this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/move.png", 1, 4);
			}
			if (m_dxBase->GetInputManager()->IsKeyDown("A"))
			{
				this->GetComponent<Rigidbody>()->Move(Vector3(-160, 0, 0));
				if (weaponTimer < 0)  this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/move.png", 1, 4);
			}
			if (m_dxBase->GetInputManager()->IsKeyDown("K"))
			{
				this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -500, 0));
			}
			if (!m_dxBase->GetInputManager()->IsKeyDown("D") && !m_dxBase->GetInputManager()->IsKeyDown("A"))
			{
				this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
				if (weaponTimer < 0) this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/stand.png", 1, 1);
			}
		}
	}
	else
	{
		if (weaponTimer < 0)  this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/jump.png", 1, 1);
		if (m_dxBase->GetInputManager()->IsKeyDown("D"))
		{
			this->GetComponent<Rigidbody>()->Move(Vector3(360, 0, 0));
		}
		if (m_dxBase->GetInputManager()->IsKeyDown("A"))
		{
			this->GetComponent<Rigidbody>()->Move(Vector3(-360, 0, 0));
		}
	}
	
	
	lastFrameAcc = this->GetComponent<Rigidbody>()->GetAcceleration();
	lastFrameMove = this->GetComponent<Rigidbody>()->GetMovingVector();
	this->GetComponent<Collider>()->SetCollisionStatus(false);
	if (lastFrameMove.x > 0) transform->SetRotation(Vector3(transform->GetRotation().x, 360, transform->GetRotation().z));
	else if (lastFrameMove.x < 0) transform->SetRotation(Vector3(transform->GetRotation().x, 0, transform->GetRotation().z));
}

void Player::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
}

void Player::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void Player::OnCollisionEnter(Collider* _other, Vector3 _normal)
{
	GameObject::OnCollisionEnter(_other, _normal);

	/*if (_normal.y != 0)
	{
		this->GetComponent<Animation>()->ResetAnimation(L"Resources/Captain/Animations/move.png", 1, 6);
	}*/
	if (_other->GetAttachedGameObject()->GetTag() == "Elevator")
	{
		if (_normal.x != 0 && this->GetComponent<Rigidbody>()->GetVelocity().y > 0 && lastFrameMove.x != 0)
		{
			this->GetComponent<Rigidbody>()->AddForce(Vector3(0, this->GetComponent<Rigidbody>()->GetVelocity().y / -2, 0));
		}
	}

	else if (_other->GetAttachedGameObject()->GetTag() == "Door")
	{
		if (lastFrameMove.x >= 0)
		{
			cutscene = true;
			this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + Vector3(3, 0, 0));
		}
		else if (lastFrameMove.x < 0) GameObject::OnCollisionEnter(_other, _normal);
	}
}


Player::~Player()
{
}
