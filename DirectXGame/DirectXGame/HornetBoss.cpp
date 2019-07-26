#include "HornetBoss.h"



HornetBoss::HornetBoss()
{
}

HornetBoss::HornetBoss(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, SimpleMath::Vector3 _position, SimpleMath::Vector3 _rotation, SimpleMath::Vector3 _scale)
{
	_player = NULL;
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetPosition(_position);
	this->GetTransform()->SetScreenScale(_scale);
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	//this->AddComponent<Rigidbody>(new Rigidbody(this));
	this->AddComponent<Animation>(new Animation("asd",this->GetComponent<Renderer>(), 1, 11, 0.1f, 1.0f, true));
	this->GetTransform()->SetScale(Vector3(this->GetComponent<Animation>()->GetFrameScale().x*_scale.x, this->GetComponent<Animation>()->GetFrameScale().y*_scale.y, 1));
	std::vector<std::string>* stringStates = new std::vector<std::string>();
	stringStates->push_back("stage1");
	stringStates->push_back("stage2");
	stringStates->push_back("stage3");
	this->AddComponent<State>(new State(this, *stringStates));
	//this->GetTransform()->SetScreenScale(Vector3(1, 1, 1));
	originPos = _position - Vector3(300, 0, 0);
	leftPos = _position - Vector3(600, 0, 0);
	rightPos = _position;
	angle = 0;
	stageOneTimer = 0;
	stageTwoTimer = 0;
	stageThreeTimer = 0;
	this->GetComponent<State>()->SetState("stage2");
}

void HornetBoss::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void HornetBoss::Update(float _deltaTime)
{
	if (_player == NULL)
	{
		for (int i = 0; i < m_dxBase->GetCurrentScene()->GetGameObjectList()->size(); i++)
		{
			if (m_dxBase->GetCurrentScene()->GetGameObjectList()->at(i)->GetTag() == "Player") _player = m_dxBase->GetCurrentScene()->GetGameObjectList()->at(i);
		}
	}
	if (angle >= 360)angle = 0;
	else angle += 1 * _deltaTime * 2;
	if (this->GetComponent<State>())
	{
		if (this->GetComponent<State>()->GetState() != "stage1") {
			//this->GetComponent<State>()->SetState("stage1");
			this->GetComponent<Animation>()->ResetAnimation(L"Resources/Animations/boss/Hornet/Bhornetsprite1.png", 1, 5);
			this->GetTransform()->SetScale(Vector3(this->GetComponent<Animation>()->GetFrameScale().x / 2, this->GetComponent<Animation>()->GetFrameScale().y / 2, 1)*this->GetTransform()->GetScreenScale());
		}
	}

	if (this->GetComponent<State>()->GetState() == "stage1")
	{
		if (stageOneTimer > 5.0f)
		{
			this->GetComponent<State>()->SetState("stage2");
			stageOneTimer = 0;
		}
		else
		{
			this->GetTransform()->LerpPosition(leftPos, _deltaTime);
			stageOneTimer += _deltaTime;
		}
	}
	else if (this->GetComponent<State>()->GetState() == "stage2")
	{
		if (stageTwoTimer > 5.0f)
		{
			this->GetComponent<State>()->SetState("stage3");
			stageTwoTimer = 0;
		}
		else
		{
			if (abs(rightPos.x - this->GetTransform()->GetPosition().x) < 10);
			Vector3 moveSin = Vector3(originPos.x + cos(angle) * 300, originPos.y + sin(2 * angle) / 2 * 160, 0);
			this->GetTransform()->LerpPosition(moveSin,_deltaTime*5);
			stageTwoTimer += _deltaTime;
		}
	}
	else if (this->GetComponent<State>()->GetState() == "stage3")
	{
		if (stageThreeTimer > 1.0f)
		{
			this->GetComponent<State>()->SetState("stage1");
			stageThreeTimer = 0;
		}
		else
		{
			this->GetTransform()->LerpPosition(_player->GetTransform()->GetPosition(), _deltaTime);
			stageThreeTimer += _deltaTime;
		}
	}
	GameObject::Update(_deltaTime);
}

void HornetBoss::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void HornetBoss::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
	GameObject::OnCollisionEnter(_other, _normal);
}


HornetBoss::~HornetBoss()
{
}
