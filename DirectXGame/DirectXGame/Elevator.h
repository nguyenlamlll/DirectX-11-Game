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

class Elevator: public DirectXCore::GameObject
{
public:
	Elevator();
	Elevator(std::shared_ptr<DirectXCore::DxBase> _m_dxBase);
	void PreUpdate(float _deltaTime) override;
	void Update(float _deltaTime) override;
	void LateUpdate(float _deltaTime) override;
	void OnCollisionEnter(Collider* _other, Vector3 _normal) override;
	~Elevator();
private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;
};

