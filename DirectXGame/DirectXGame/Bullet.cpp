#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(const wchar_t* _path, std::shared_ptr<DirectXCore::DxBase> _m_dxBase, Vector3 _pos, Vector3 _scl, Vector3 _dir)
{
	m_dxBase = _m_dxBase;
	this->GetTransform()->SetPosition(_pos);
	this->GetTransform()->SetScale(Vector3(120, 120, 1));
	this->GetTransform()->SetScreenScale(_scl);
	this->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/rockman.png"));
	this->AddComponent<Animation>(new Animation(this->GetComponent<Renderer>(), 1, 11, 0.1f, 1.0f, true));
	this->GetComponent<Animation>()->ResetAnimation(_path, 1, 16);
	this->AddComponent<Collider>(new Collider(this,this->GetTransform()));
	direction = _dir;
}

void Bullet::PreUpdate(float _deltaTime)
{
	GameObject::PreUpdate(_deltaTime);
}

void Bullet::Update(float _deltaTime)
{
	this->GetTransform()->SetPosition(this->transform->GetPosition() + direction);
	GameObject::Update(_deltaTime);
}

void Bullet::LateUpdate(float _deltaTime)
{
	GameObject::LateUpdate(_deltaTime);
}

void Bullet::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
	if (_other->GetAttachedGameObject()->GetTag() == "Enemy")
	{
		m_dxBase->GetCurrentScene()->GetGameObjectList()->erase(std::remove(m_dxBase->GetCurrentScene()->GetGameObjectList()->begin(), m_dxBase->GetCurrentScene()->GetGameObjectList()->end(),this), m_dxBase->GetCurrentScene()->GetGameObjectList()->end());
	}
}

Bullet::~Bullet()
{
}
