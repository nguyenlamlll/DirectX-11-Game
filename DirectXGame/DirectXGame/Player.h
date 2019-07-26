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
class Player : public DirectXCore::GameObject
{
public:
	Player(std::shared_ptr<DirectXCore::DxBase> _m_dxBase);
	void PreUpdate(float _deltaTime) override;
	void Update(float _deltaTime) override;
	void LateUpdate(float _deltaTime) override;
	void OnCollisionEnter(Collider* _other, Vector3 _normal) override;
	~Player();
private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;
	Vector3 lastFrameAcc, lastFrameMove;
	float currentCountTimer = 0, weaponTimer = 0, cutsceneTimer = 0, jumpTime = 0, hurtTime = 0;
	bool shoot = false, cutscene = false;
	Shield* capshield;
};

