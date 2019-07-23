#pragma once
#include "GameObject.h"
#include "DxBase.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Renderer.h"
#include "Animation.h"
#include "State.h"
#include "Bullet.h"
#include "Shield.h"

using namespace DirectXCore;
class Enemy : public DirectXCore::GameObject
{
public:
	Enemy();
	Enemy(std::shared_ptr<DirectXCore::DxBase> _m_dxBase);
	void PreUpdate(float _deltaTime) override;
	void Update(float _deltaTime) override;
	void LateUpdate(float _deltaTime) override;
	void OnCollisionEnter(Collider* _other, Vector3 _normal) override;

	void AssignPlayer(GameObject* _player) { player = _player; }
	~Enemy();
private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;
	float bulletTimer,deathTimer,attackTimer;
	bool death;
	GameObject* player;
};

