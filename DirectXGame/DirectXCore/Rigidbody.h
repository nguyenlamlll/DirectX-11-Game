#pragma once
#include "Component.h"

namespace DirectXCore
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		Rigidbody(GameObject* _gameObject);
		void PreUpdate(float _deltaTime);
		void Update(float _deltaTime);
		void LateUpdate(float _deltaTime);
		void MovePosition(SimpleMath::Vector3 _newPosition);
		void Move(SimpleMath::Vector3 _velocity);
		void AddForce(SimpleMath::Vector3 _force);

		SimpleMath::Vector3 GetAcceleration() { return acceleration; }
		SimpleMath::Vector3 GetVelocity() { return velocity; }
		void SetVelocity(SimpleMath::Vector3 _newVelocity) { velocity = _newVelocity; }
		SimpleMath::Vector3 GetMass() { return mass; }
		void SetMass(SimpleMath::Vector3 _newMass) { mass = _newMass; }
		bool IsKinematic() { return kinematic; }
		void SetKinematic(bool flag) { kinematic = flag; }

		void OnPhysicUpdate(float _delta);
		~Rigidbody();
	private:
		SimpleMath::Vector3 move,acceleration,position, velocity, force, impulse, mass, gravity = SimpleMath::Vector3(0, 9.8f, 0);
		bool kinematic;
		float accumulatedTime = 0.0f;
	};
}
