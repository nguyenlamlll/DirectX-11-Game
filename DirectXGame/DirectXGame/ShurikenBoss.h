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

class ShurikenBoss :public GameObject
{
public:
	ShurikenBoss();
	ShurikenBoss(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, SimpleMath::Vector3 _instantiatePosition, SimpleMath::Vector3 _instantiateRotation, SimpleMath::Vector3 _instantiateScale);
	void PreUpdate(float _deltaTime) override;
	void Update(float _deltaTime) override;
	void LateUpdate(float _deltaTime) override;
	~ShurikenBoss();
private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;
};

