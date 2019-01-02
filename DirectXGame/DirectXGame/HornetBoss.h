#pragma once
#include "GameObject.h"
#include "DxBase.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Renderer.h"
#include "Animation.h"
#include "State.h"
#include "Bullet.h"
#include <cmath>

using namespace DirectXCore;

class HornetBoss : public GameObject
{
public:
	HornetBoss();
	HornetBoss(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, SimpleMath::Vector3 _position, SimpleMath::Vector3 _rotation, SimpleMath::Vector3 _scale);
	void PreUpdate(float _deltaTime) override;
	void Update(float _deltaTime) override;
	void LateUpdate(float _deltaTime) override;
	void OnCollisionEnter(Collider* _other, Vector3 _normal) override;
	~HornetBoss();
private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;
	Vector3 direction, force;
	float currentBossTimer = 0.0f, stageTwoTimer, stageOneTimer, stageThreeTimer;
	bool Grounded = false;
	Vector3 leftPos, rightPos, originPos;
	float angle = 0;
	GameObject* _player;
};

