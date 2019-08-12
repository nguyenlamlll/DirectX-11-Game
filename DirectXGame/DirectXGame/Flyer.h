#pragma once
#include "GameObject.h"
#include "DxBase.h"
#include "GameObject.h"
#include "Rigidbody.h"
#include "Renderer.h"
#include "Animation.h"
#include "State.h"
#include "Bullet.h"
#include "PittsburghScene.h"

using namespace DirectXCore;
class Flyer : public DirectXCore::GameObject
{
public:
public:
	Flyer();
	Flyer(std::shared_ptr<DirectXCore::DxBase> _m_dxBase);
	void PreUpdate(float _deltaTime) override;
	void Update(float _deltaTime) override;
	void LateUpdate(float _deltaTime) override;
	void OnCollisionEnter(Collider* _other, Vector3 _normal) override;

	void AssignPlayer(GameObject* _player) { player = _player; }
	~Flyer();
private:
	void AddAnimators();
	void ManageAnimators();
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;
	float shootTime;
	bool death;
	GameObject* player;
	Vector3* direction;
	std::vector<Vector3>* positionList;
	int positionIndex = 0;
};

