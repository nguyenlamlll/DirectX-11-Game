#pragma once
#include "GameObject.h"
#include "DxBase.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Renderer.h"
#include "Animation.h"
#include "State.h"
#include "SecondBoss.h"

class Barrel : public GameObject
{
public:
	Barrel();
	Barrel(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, GameObject* _boss);
	void PreUpdate(float _deltaTime) override;
	void Update(float _deltaTime) override;
	void LateUpdate(float _deltaTime) override;
	void Render() override;
	void OnCollisionEnter(Collider* _other, Vector3 _normal) override;
	~Barrel();
	Vector3 direction;
private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;
	GameObject* boss;
	void Addanimation();
	void ManageAnimation();
};

