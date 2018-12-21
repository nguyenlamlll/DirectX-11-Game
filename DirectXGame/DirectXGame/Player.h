#pragma once
#include "GameObject.h"
#include "DxBase.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Renderer.h"
#include "Animation.h"
#include "State.h"
#include "Bullet.h"


using namespace DirectXCore;
class Player : public DirectXCore::GameObject
{
public:
	Player(std::shared_ptr<DirectXCore::DxBase> _m_dxBase);
	void PreUpdate(float _deltaTime) override;
	void Update(float _deltaTime) override;
	void LateUpdate(float _deltaTime) override;
	~Player();
private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;
	Vector3 lastFrameAcc, lastFrameMove;
	float currentCountTimer = 0;
};

