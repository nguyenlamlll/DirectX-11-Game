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
class SecondBoss : public GameObject
{
public:
	SecondBoss();
	SecondBoss(std::shared_ptr<DirectXCore::DxBase> _m_dxBase, GameObject* _captain);
	void PreUpdate(float _deltaTime) override;
	void Update(float _deltaTime) override;
	void LateUpdate(float _deltaTime) override;
	void Render() override;
	void OnCollisionEnter(Collider* _other, Vector3 _normal) override;
	void TakeDamage() { hurtTime = 1.0f; }
	~SecondBoss();
private:
	GameObject* captain;
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;
	Vector3 upleftPos, uprightPos, downrighPos;
	int loopDirection = 1;;
	std::vector<Vector3>* positionList;
	int positionIndex = 0;
	float stateTimeCycle = 0, bulletTimer = 0, hurtTime = 0;;
	void AddAnimation();
	void ManageAnimation();
};

