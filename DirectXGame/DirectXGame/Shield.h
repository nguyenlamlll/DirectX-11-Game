#pragma once
#include "GameObject.h"
#include "DxBase.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Renderer.h"
#include "Animation.h"
#include "State.h"

//using namespace DirectXCore;

class Shield : public GameObject
{
public:
	Shield();
	Shield(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, GameObject* _captain);
	~Shield();
	void PreUpdate(float _deltaTime) override;
	void Update(float _deltaTime) override;
	void LateUpdate(float _deltaTime) override;
	void Render() override;
	void OnCollisionEnter(Collider* _other, Vector3 _normal) override;
	void SetTarget(Vector3 _target);
private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;
	GameObject* captain;
	Vector3 captainPosition;
	Vector3 direction, target;
};

