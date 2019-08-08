#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, Vector3 _pos)
{
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetPosition(_pos);
	this->GetTransform()->SetScale(Vector3(16, 16, 1));
	this->GetTransform()->SetScreenScale(Vector3(3,3,1));
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/enemy/shooter_bullet.png"));
}

Bullet::Bullet(const wchar_t* _path, std::shared_ptr<DirectXCore::DxBase> _m_dxBase, Vector3 _pos, Vector3 _scl, Vector3 _dir)
{
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetPosition(_pos);
	this->GetTransform()->SetScale(Vector3(16*_scl.x, 16*_scl.y, 1));
	this->GetTransform()->SetScreenScale(_scl);
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), _path));
	//this->AddComponent<Animation>(new Animation(this->GetComponent<Renderer>(), 1, 4, 0.03f, 1.0f, true));
	//this->GetComponent<Animation>()->ResetAnimation(_path, 1, 4);
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	//this->GetComponent<Collider>()->SetTrigger(true);
	direction = _dir;
}

void Bullet::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void Bullet::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	this->GetComponent<Rigidbody>()->Move(direction);
	alivetime -= _deltaTime;
	if (alivetime < 0)
	{
		m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->erase(std::remove(m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->begin(), m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->end(), this), m_dxBase->GetCurrentScene()->GetDynamicGameObjectList()->end());
		delete this;
	}
}

void Bullet::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void Bullet::Render()
{
	GameObject::Render();
}

void Bullet::OnCollisionEnter(Collider * _other, Vector3 _normal)
{/*
	if (this->GetTag() == "PlayerBullet" && (_other->GetAttachedGameObject()->GetTag() == "Enemy" || _other->GetAttachedGameObject()->GetTag() == "Shuriken"))
	{
		m_dxBase->GetCurrentScene()->GetGameObjectList()->erase(std::remove(m_dxBase->GetCurrentScene()->GetGameObjectList()->begin(), m_dxBase->GetCurrentScene()->GetGameObjectList()->end(), this), m_dxBase->GetCurrentScene()->GetGameObjectList()->end());
	}
	else if (this->GetTag() == "EnemyBullet")
	{
		if ((_other->GetAttachedGameObject()->GetTag() == "Wall" && _normal.y < 0) || _other->GetAttachedGameObject()->GetTag() == "Player")
			m_dxBase->GetCurrentScene()->GetGameObjectList()->erase(std::remove(m_dxBase->GetCurrentScene()->GetGameObjectList()->begin(), m_dxBase->GetCurrentScene()->GetGameObjectList()->end(), this), m_dxBase->GetCurrentScene()->GetGameObjectList()->end());
	}*/
	if (_other->GetAttachedGameObject()->GetTag() == "Player" && (tag == "EnemyBullet" || tag == "BossBullet"))
	{
		Player* a = (Player*)(_other->GetAttachedGameObject());
		a->TakeDamage();
	}
	else if (_other->GetAttachedGameObject()->GetTag() == "Shield" && tag == "EnemyBullet")
	{
		direction = Vector3(0, -400, 0);
	}
}

void Bullet::SetTarget(Vector3 _target)
{
	target.x = _target.x;
	target.y = _target.y;
	target.z = _target.z;
}

Bullet::~Bullet()
{
}
