#include "Player.h"

Player::Player(std::shared_ptr<DirectXCore::DxBase> _m_dxBase)
{
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetPosition(Vector3(50, 3500, 0));
	this->GetTransform()->SetScale(Vector3(120, 120, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));
	this->AddComponent<Renderer>(new Renderer(_m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
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
}

void Player::PreUpdate(float _deltaTime)
{
	cutscene = false;
	GameObject::PreUpdate(_deltaTime);
	if (m_dxBase->GetInputManager()->IsKeyDown("D"))
	{
		this->GetComponent<Rigidbody>()->Move(Vector3(400, 0, 0));
		//this->GetComponent<Rigidbody>()->SetVelocity(Vector3(300, this->GetComponent<Rigidbody>()->GetVelocity().y , 0));
		//this->GetComponent<Rigidbody>()->AddForce(Vector3(3, 0, 0));
		//camera->SetPosition(camera->GetPosition() + Vector3(10, 0, 0));
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("A"))
	{
		this->GetComponent<Rigidbody>()->Move(Vector3(-400, 0, 0));
		//this->GetComponent<Rigidbody>()->AddForce(Vector3(-3, 0, 0));
		//camera->SetPosition(camera->GetPosition() + Vector3(-10, 0, 0));
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("S"))
	{
		//camera->SetPosition(camera->GetPosition() + Vector3(0, 10, 0));
	}
	if (!m_dxBase->GetInputManager()->IsKeyDown("D") && !m_dxBase->GetInputManager()->IsKeyDown("A"))
	{
		this->GetComponent<Rigidbody>()->Move(Vector3(0, 0, 0));
	}
	lastFrameAcc = this->GetComponent<Rigidbody>()->GetAcceleration();
	lastFrameMove = this->GetComponent<Rigidbody>()->GetMovingVector();
	this->GetComponent<Collider>()->SetCollisionStatus(false);
	if (lastFrameMove.x > 0) transform->SetRotation(Vector3(transform->GetRotation().x, 0, transform->GetRotation().z));
	else if (lastFrameMove.x < 0) transform->SetRotation(Vector3(transform->GetRotation().x, 360, transform->GetRotation().z));
}

void Player::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	if (m_dxBase->GetInputManager()->IsKeyDown("W") && this->GetComponent<Collider>()->GetCollisionStatus())
	{
		if (this->GetComponent<Rigidbody>()->GetVelocity().y == 0)
		{
			if (lastFrameAcc.y > 0) this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -1000, 0));
		}
		else if (this->GetComponent<Rigidbody>()->GetVelocity().y > 0)
		{
			if (lastFrameMove.x != 0 && this->GetComponent<Rigidbody>()->GetMovingVector().x == 0)
				this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -1000, 0));
		}
	}

	const wchar_t* animationString = L"";
	int animationCount = 0;
	if (this->GetComponent<Collider>()->GetCollisionStatus())
	{
		if (this->GetComponent<Rigidbody>()->GetVelocity().y != 0)
		{
			if (transform->GetRotation().y == 0 && lastFrameMove.x > 0) transform->SetRotation(Vector3(transform->GetRotation().x, 360, transform->GetRotation().z));
			else if (transform->GetRotation().y == 360 && lastFrameMove.x < 0) transform->SetRotation(Vector3(transform->GetRotation().x, 0, transform->GetRotation().z));
			if (this->GetComponent<State>()->GetState() == "shoot")
				animationString = (lastFrameMove.x != 0) ? (L"Resources/Animations/sweep_wall_attack_flip.png") : L"Resources/Animations/jump_attack.png";
			else
				animationString = (lastFrameMove.x != 0) ? (L"Resources/Animations/sweep_wall_flip.png") : L"Resources/Animations/jump.png";
			animationCount = (this->GetComponent<Rigidbody>()->GetMovingVector().x == 0 && lastFrameMove.x != 0) ? 3 : 7;
		}
		else
		{
			if (this->GetComponent<State>()->GetState() == "shoot")
			{
				animationString = (this->GetComponent<Rigidbody>()->GetMovingVector().x != 0) ? L"Resources/Animations/run-attack.png" : L"Resources/Animations/stand_attack.png";
				animationCount = (this->GetComponent<Rigidbody>()->GetMovingVector().x != 0) ? 10 : 2;
			}
			else
			{
				animationString = (this->GetComponent<Rigidbody>()->GetMovingVector().x != 0) ? L"Resources/Animations/run.png" : L"Resources/Animations/stand.png";
				animationCount = (this->GetComponent<Rigidbody>()->GetMovingVector().x != 0) ? 11 : 4;
			}

		}
	}
	else
	{
		animationString = (this->GetComponent<State>()->GetState() == "shoot") ? L"Resources/Animations/jump_attack.png" : L"Resources/Animations/jump.png";
		animationCount = 7;
	}
	this->GetComponent<Animation>()->ResetAnimation(animationString, 1, animationCount);

	if (currentCountTimer >= 0.2f)
	{
		if (m_dxBase->GetInputManager()->IsKeyDown("L") && !shoot)
		{
			Bullet* asd = new Bullet(L"Resources/Animations/bullet/lv1.png", m_dxBase, this->GetTransform()->GetPosition() + Vector3(transform->GetRotation().y == 0 ? 10 : -10, 0, 0), Vector3(3, 3, 3), Vector3(transform->GetRotation().y == 0 ? 20 : -20, 0, 0));
			asd->SetTag("PlayerBullet");
			asd->AddComponent<Rigidbody>(new Rigidbody(asd));
			asd->GetComponent<Rigidbody>()->SetGravity(Vector3(0, 0, 0));
			asd->GetComponent<Rigidbody>()->AddForce(Vector3(transform->GetRotation().y == 0 ? 1000 : -1000, 0, 0));
			currentCountTimer = 0;
			this->GetComponent<State>()->SetState("shoot");
			currentCountTimer = 0;
			weaponTimer = 0;
			shoot = true;
		}
		else this->GetComponent<State>()->SetState("none");
	}
	else currentCountTimer += _deltaTime;
	if (weaponTimer > 0.8f && weaponTimer < 1.8f)
	{
		if (shoot && m_dxBase->GetInputManager()->IsKeyUp("L"))
		{
			Bullet* asd = new Bullet(L"Resources/Animations/bullet/lv1.png", m_dxBase, this->GetTransform()->GetPosition() + Vector3(transform->GetRotation().y == 0 ? 10 : -10, 0, 0), Vector3(5, 5, 5), Vector3(transform->GetRotation().y == 0 ? 20 : -20, 0, 0));
			asd->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/bullet/lv2.png", 1, 16);
			asd->SetTag("PlayerBullet");
			asd->AddComponent<Rigidbody>(new Rigidbody(asd));
			asd->GetComponent<Rigidbody>()->SetGravity(Vector3(0, 0, 0));
			asd->GetComponent<Rigidbody>()->AddForce(Vector3(transform->GetRotation().y == 0 ? 1000 : -1000, 0, 0));
			this->GetComponent<State>()->SetState("shoot");
			shoot = false;
		}
		else this->GetComponent<State>()->SetState("none");
	}
	else if (weaponTimer > 1.8f)
	{
		if (shoot && m_dxBase->GetInputManager()->IsKeyUp("L"))
		{
			Bullet* asd = new Bullet(L"Resources/Animations/bullet/lv1.png", m_dxBase, this->GetTransform()->GetPosition() + Vector3(transform->GetRotation().y == 0 ? 10 : -10, 0, 0), Vector3(5, 5, 5), Vector3(transform->GetRotation().y == 0 ? 20 : -20, 0, 0));
			asd->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/bullet/lv3.png", 1, 19);
			asd->SetTag("PlayerBullet");
			asd->AddComponent<Rigidbody>(new Rigidbody(asd));
			asd->GetComponent<Rigidbody>()->SetGravity(Vector3(0, 0, 0));
			asd->GetComponent<Rigidbody>()->AddForce(Vector3(transform->GetRotation().y == 0 ? 1000 : -1000, 0, 0));
			this->GetComponent<State>()->SetState("shoot");
			shoot = false;
		}
		else this->GetComponent<State>()->SetState("none");
	}
	if (weaponTimer < 1.8f)
	{
		if (m_dxBase->GetInputManager()->IsKeyDown("L")) weaponTimer += _deltaTime;
		else shoot = false;
	}
	if (cutscene) this->GetComponent<Rigidbody>()->SetVelocity(Vector3(0, 0, 0));
}

void Player::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void Player::OnCollisionEnter(Collider* _other, Vector3 _normal)
{
	if (_other->GetAttachedGameObject()->GetTag() == "Wall" || _other->GetAttachedGameObject()->GetTag() == "Elevator")
	{
		GameObject::OnCollisionEnter(_other, _normal);
		if (_normal.x != 0 && this->GetComponent<Rigidbody>()->GetVelocity().y > 0 && lastFrameMove.x != 0)
		{
			this->GetComponent<Rigidbody>()->AddForce(Vector3(0, this->GetComponent<Rigidbody>()->GetVelocity().y/-2, 0));
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
