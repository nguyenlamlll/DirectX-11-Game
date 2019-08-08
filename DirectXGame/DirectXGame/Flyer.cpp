#include "Flyer.h"



Flyer::Flyer()
{
}

Flyer::Flyer(std::shared_ptr<DirectXCore::DxBase> _m_dxBase)
{
	m_dxBase = _m_dxBase;
	direction = NULL;
	player = NULL;
	bulletTimer = 0;
	death = false;
	positionIndex = 0;

	positionList = new std::vector<Vector3>();
	transform->SetPosition(Vector3(800, 550, 0));
	positionList->push_back(transform->GetPosition() + Vector3(-600, 0, 0));
	positionList->push_back(transform->GetPosition());
	this->GetTransform()->SetScale(Vector3(93, 141, 1));
	this->GetTransform()->SetScreenScale(Vector3(3, 3, 1));
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/enemy/shooter_sit.png"));
	this->AddComponent<Rigidbody>(new Rigidbody(this));
	//this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	this->AddComponent<Animator>(new Animator(this->GetComponent<Renderer>()));
	AddAnimators();
	this->SetTag("Enemy");
}

void Flyer::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void Flyer::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	if (Vector3::Distance(this->GetTransform()->GetPosition(), positionList->at(positionIndex)) < 10)
		positionIndex = (positionIndex == positionList->size() - 1) ? 0 : positionIndex + 1;
	else
	{
		Vector3 transformVector = positionList->at(positionIndex) - this->GetTransform()->GetPosition();
		this->GetTransform()->SetRotation(Vector3(0, transformVector.x > 0 ? 360 : 0, 0));
		transformVector.Normalize();
		transformVector.y = 0;
		this->GetComponent<Rigidbody>()->Move(transformVector * 100);
	}

	if (bulletTimer > 2.5f && this->GetComponent<Collider>()->GetCollisionStatus())
	{
		//shooting code
		float directionX = player->GetTransform()->GetPosition().x - this->GetTransform()->GetPosition().x;
		if (directionX > 10) directionX = 400;
		else if (directionX < -10) directionX = -400;
		else directionX = 0;
		Bullet* bullet = new Bullet(L"Resources/Captain/Animations/mini_boss/bullet.png", m_dxBase, this->GetTransform()->GetPosition(), Vector3(3, 3, 1), Vector3(directionX, 0, 0));
		bullet->SetTag("EnemyBullet");
		bullet->AddComponent<Rigidbody>(new Rigidbody(bullet));
		bullet->GetComponent<Rigidbody>()->SetKinematic(true);
		if (player->GetTransform()->GetPosition().x - bullet->GetTransform()->GetPosition().x > 0) bullet->GetTransform()->SetRotation(Vector3(0, 360, 0));
		else this->GetTransform()->SetRotation(Vector3(0, 0, 0));
		m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->push_back(bullet);
		//this->AddChild(bullet);
		bulletTimer = 0;
	}
}

void Flyer::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void Flyer::OnCollisionEnter(Collider * _other, Vector3 _normal)
{

}


Flyer::~Flyer()
{
}

void Flyer::AddAnimators()
{
	Animation* flyAnim = new Animation(L"Resources/Captain/Animations/enemy/shooter_move.png", "Move", this->GetComponent<Renderer>(), 1, 3, 0.1f, 1.0f, true);
	this->GetComponent<Animator>()->AddAnimation(flyAnim);
	this->GetComponent<Animator>()->SetCurrentAnimation(flyAnim);
}

void Flyer::ManageAnimators()
{

}
