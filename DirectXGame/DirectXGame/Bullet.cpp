#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, Vector3 _pos)
{
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetPosition(_pos);
	this->GetTransform()->SetScale(Vector3(50, 50, 1));
	this->GetTransform()->SetScreenScale(Vector3(2,2,1));
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Captain/Animations/enemy/shooter_bullet.png"));
}

Bullet::Bullet(const wchar_t* _path, std::shared_ptr<DirectXCore::DxBase> _m_dxBase, Vector3 _pos, Vector3 _scl, Vector3 _dir)
{
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetPosition(_pos);
	this->GetTransform()->SetScale(Vector3(1, 1, 1));
	this->GetTransform()->SetScreenScale(_scl);
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), _path));
	//this->AddComponent<Animation>(new Animation(this->GetComponent<Renderer>(), 1, 4, 0.03f, 1.0f, true));
	//this->GetComponent<Animation>()->ResetAnimation(_path, 1, 4);
	this->AddComponent<Collider>(new Collider(this, this->GetTransform()));
	direction = _dir;
}

void Bullet::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void Bullet::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	//if (this->GetName() == "BruteBullet") this->GetTransform()->LerpPosition(target, _deltaTime);
	this->GetTransform()->SetPosition(this->GetTransform()->GetPosition() + direction);
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
