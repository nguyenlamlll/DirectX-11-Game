#pragma once
#include "Component.h"

namespace DirectXCore
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		Rigidbody(GameObject* _gameObject);
		void Update();
		void MovePosition(SimpleMath::Vector3 _newPosition);
		void Move(SimpleMath::Vector3 _velocity,float _deltaTime);

		SimpleMath::Vector3 GetVelocity() { return velocity; }
		void SetVelocity(SimpleMath::Vector3 _newVelocity) { velocity = _newVelocity; }
		SimpleMath::Vector3 GetMass() { return mass; }
		void SetMass(SimpleMath::Vector3 _newMass) { mass = _newMass; }
		bool IsKinematic() { return kinematic; }
		void SetKinematic(bool flag) { kinematic = flag; }

		void OnPhysicUpdate(float _delta);
		~Rigidbody();
	private:
		SimpleMath::Vector3 position, velocity, force, impulse,mass,gravity;
		bool kinematic;
	};
}
