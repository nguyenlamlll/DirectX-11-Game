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
		void Update(float _deltaTime);

		BoundingBox* GetCollider() { return collider; }
		Vector3 GetColliderPosition() { return collider->Center; }
		Vector3 GetColliderScale() { return collider->Extents * 2; }
		void SetColliderPosition(Vector3 _newPosition);
		void SetColliderScale(Vector3 _newScale);
		void SetColliderTransform(Transform* _newTransform);
		~Collider();
	private:
		BoundingBox* collider;
	};
}

