#pragma once
#include "Component.h"
#include "Transform.h"

namespace DirectXCore
{
	class Collider : public Component
	{
	public:
		Collider();
		Collider(GameObject* _attachedGameObject, Transform* _gameObjectTransform);
		Collider(GameObject* _attachedGameObject,Vector3 _pos,Vector3 _rot, Vector3 _scl);
		void PreUpdate(float _deltaTime);
		void Update(float _deltaTime);
		void LateUpdate(float _deltaTime);

		void SetCollisionStatus(bool _col) { collided = _col; }
		bool GetCollisionStatus() { return collided; }
		BoundingBox* GetCollider() { return collider; }
		Vector3 GetColliderPosition() { return collider->Center; }
		Vector3 GetColliderScale() { return collider->Extents * 2; }
		void SetColliderPosition(Vector3 _newPosition);
		void SetColliderScale(Vector3 _newScale);
		void SetColliderTransform(Transform* _newTransform);
		void OnCollisionEnter(Collider* _other,SimpleMath::Vector3 _normal);
		void SetTrigger(bool _trigger) { isTrigger = _trigger; }
		bool IsTrigger() { return isTrigger; }
		~Collider();
	private:
		BoundingBox* collider;
		bool collided;
		bool isTrigger;
	};
}

