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
	//this->GetComponent<Rigidbody>()->SetGravity(Vector3(0, 0, 0));
}

void Player::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
	if (m_dxBase->GetInputManager()->IsKeyDown("D"))
	{
		this->GetComponent<Rigidbody>()->Move(Vector3(300, 0, 0));
		//this->GetComponent<Rigidbody>()->SetVelocity(Vector3(300, this->GetComponent<Rigidbody>()->GetVelocity().y , 0));
		//this->GetComponent<Rigidbody>()->AddForce(Vector3(3, 0, 0));
		//camera->SetPosition(camera->GetPosition() + Vector3(10, 0, 0));
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("A"))
	{
		this->GetComponent<Rigidbody>()->Move(Vector3(-300, 0, 0));
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
	if (currentCountTimer >= 0.5f)
	{
		if (m_dxBase->GetInputManager()->IsKeyDown("L"))
		{
			Bullet* asd = new Bullet(L"Resources/Animations/bullet/lv2.png", m_dxBase, this->GetTransform()->GetPosition() + Vector3(100, 0, 0), Vector3(2, 2, 2), Vector3(lastFrameMove.x > 0 ? 20 : -20, 0, 0));
			asd->SetTag("PlayerBullet");
			m_dxBase->GetCurrentScene()->GetGameObjectList()->insert(m_dxBase->GetCurrentScene()->GetGameObjectList()->end(), asd);
			//m_dxBase->GetCurrentScene()->GetQuadTree()->Insert(asd);
			currentCountTimer = 0;
		}
	}
	else currentCountTimer += _deltaTime;

	if (m_dxBase->GetInputManager()->IsKeyDown("W") && this->GetComponent<Collider>()->GetCollisionStatus())
	{
		/*	if(lastFrameAcc.y!=0)
				this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -400, 0));;*/
		if (this->GetComponent<Rigidbody>()->GetVelocity().y == 0)
		{
			if (lastFrameAcc.y > 0)		this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -800, 0));
		}
		else if (this->GetComponent<Rigidbody>()->GetVelocity().y > 0)
		{
			if (lastFrameMove.x != 0 && this->GetComponent<Rigidbody>()->GetMovingVector().x == 0)
			{
				this->GetComponent<Rigidbody>()->AddForce(Vector3(0, -800, 0));
				//this->GetComponent<Rigidbody>()->Move(Vector3(lastFrameMove.x*-2, 0, 0));
				//this->GetComponent<Rigidbody>()->Update(_deltaTime);
			}
		}
	}
	/*if (this->GetComponent<Collider>()->GetCollisionStatus())
	{
		if (this->GetComponent<Rigidbody>()->GetVelocity().y == 0)
		{
			if (lastFrameAcc.y > 0)
			{
				if (this->GetComponent<Rigidbody>()->GetVelocity().x > 0)
				{
					if (this->GetComponent<State>()->GetState() != "run")
					{
						this->GetComponent<State>()->SetState("run");
						this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/run.png", 1, 11);
					}
				}
				else if (this->GetComponent<Rigidbody>()->GetVelocity().x < 0)
				{
					if (this->GetComponent<State>()->GetState() != "runflip")
					{
						this->GetComponent<State>()->SetState("runflip");
						this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/run_flip.png", 1, 11);
					}
				}
				else if (this->GetComponent<Rigidbody>()->GetVelocity().x == 0)
				{
					if (this->GetComponent<State>()->GetState() != "stand")
					{
						this->GetComponent<State>()->SetState("stand");
						this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/stand.png", 1, 4);
					}
				}
			}
		}
		else if (this->GetComponent<Rigidbody>()->GetVelocity().y != 0)
		{
			if (lastFrameMove.x > 0)
			{
				if (this->GetComponent<State>()->GetState() != "sweep")
				{
					this->GetComponent<State>()->SetState("sweep");
					this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/sweep_wall.png", 1, 3);
				}
			}
			else if (lastFrameMove.x < 0)
			{
				if (this->GetComponent<State>()->GetState() != "sweepflip")
				{
					this->GetComponent<State>()->SetState("sweepflip");
					this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/sweep_wall_flip.png", 1, 3);
				}
			}
		}
	}
	else if (!this->GetComponent<Collider>()->GetCollisionStatus())
	{
		if (this->GetComponent<Rigidbody>()->GetVelocity().y != 0)
		{
			if (this->GetComponent<State>())
			{
				if (lastFrameMove.x > 0)
				{
					if (this->GetComponent<State>()->GetState() != "jump")
					{
						this->GetComponent<State>()->SetState("jump");
						this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/jump.png", 1, 7);
					}
				}
				else if (lastFrameMove.x < 0)
				{
					if (this->GetComponent<State>()->GetState() != "jumpflip")
					{
						this->GetComponent<State>()->SetState("jumpflip");
						this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/jump_flip.png", 1, 7);
					}
				}
			}
		}
	}*/

	const wchar_t* animationString = L"";
	int animationCount = 0;
	if (this->GetComponent<Collider>()->GetCollisionStatus())
	{
		if (this->GetComponent<Rigidbody>()->GetVelocity().y != 0)
		{
			animationString = (lastFrameMove.x != 0) ? (L"Resources/Animations/sweep_wall.png") : L"Resources/Animations/jump.png";
			animationCount = (this->GetComponent<Rigidbody>()->GetMovingVector().x == 0 && lastFrameMove.x != 0) ? 3 : 7;
		}
		else
		{
			animationString = (this->GetComponent<Rigidbody>()->GetMovingVector().x != 0) ? L"Resources/Animations/run.png" : L"Resources/Animations/stand.png";
			animationCount = (this->GetComponent<Rigidbody>()->GetMovingVector().x != 0) ? 11 : 4;
		}
	}
	else
	{
		animationString = L"Resources/Animations/jump.png";
		animationCount = 7;
	}
	this->GetComponent<Animation>()->ResetAnimation(animationString, 1, animationCount);
}

void Player::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void Player::OnCollisionEnter(Collider* _other, Vector3 _normal)
{
	if (_other->GetAttachedGameObject()->GetTag() == "Wall" || _other->GetAttachedGameObject()->GetTag() == "Elevator")
		GameObject::OnCollisionEnter(_other, _normal);
}


Player::~Player()
{
}
