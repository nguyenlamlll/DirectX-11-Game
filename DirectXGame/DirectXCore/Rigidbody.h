#pragma once
#include "Component.h"

namespace DirectXCore
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		void Update();
		void MovePosition(SimpleMath::Vector3 _newPosition);
		void Move(SimpleMath::Vector3 _velocity);
		void OnPhysicUpdate(float _delta);
		~Rigidbody();
	private:
		SimpleMath::Vector3 position, velocity, force, impulse,mass,gravity;
	};
}
