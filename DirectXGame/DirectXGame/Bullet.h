#pragma once
#include "GameObject.h"
#include "GameObject.h"
#include "DxBase.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Renderer.h"
#include "Animation.h"
#include "State.h"

using namespace DirectXCore;

class Bullet :	public GameObject
{
public:
	Bullet();
	Bullet(const wchar_t* _path, std::shared_ptr<DirectXCore::DxBase> _m_dxBase, Vector3 _pos, Vector3 _scl, Vector3 _dir);
	void PreUpdate(float _deltaTime) override;
	void Update(float _deltaTime) override;
	void LateUpdate(float _deltaTime) override;
	void OnCollisionEnter(Collider* _other, Vector3 _normal) override;
	~Bullet();
private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;
	Vector3 direction;
};

