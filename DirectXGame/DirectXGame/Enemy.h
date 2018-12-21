#pragma once
#include "GameObject.h"
#include "DxBase.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Renderer.h"
#include "Animation.h"
#include "State.h"

using namespace DirectXCore;
class Enemy : public DirectXCore::GameObject
{
public:
	Enemy();
	Enemy(std::shared_ptr<DirectXCore::DxBase> _m_dxBase);
	Enemy(std::shared_ptr<DirectXCore::DxBase> _m_dxBase,SimpleMath::Vector3 _instantiatePosition);
	Enemy(std::shared_ptr<DirectXCore::DxBase> _m_dxBase,SimpleMath::Vector3 _instantiatePosition,SimpleMath::Vector3 _instantiateRotation,SimpleMath::Vector3 _instantiateScale);
	void PreUpdate(float _deltaTime) override;
	void Update(float _deltaTime) override;
	void LateUpdate(float _deltaTime) override;
	~Enemy();
private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;
};

