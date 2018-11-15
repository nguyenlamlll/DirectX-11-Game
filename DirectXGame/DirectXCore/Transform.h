#pragma once
#include "Component.h"

using namespace DirectX::SimpleMath;

namespace DirectXCore
{

	class Transform :public Component
	{
	public:
		Transform();
		Transform(Vector3 _pos,Vector3 _rot, Vector3 _scl);
		Vector3 GetPosition() { return position; }
		Vector3 GetWorldToCameraPosition() { return screenPosition; }
		void SetWorldToCameraPosition(Vector3 _cameraShift);
		void SetPosition(Vector3 _newPosition);
		void LerpPosition(Vector3 _newPosition,float _deltatime) { position.Lerp(position,_newPosition,_deltatime); }

		Vector3 GetRotation() { return rotation; }
		void SetRotation(Vector3 _newRotation);

		Vector3 GetScale() { return scale; }
		void SetScale(Vector3 _newScale);

		~Transform();
	private:
		Vector3 position, rotation, scale;

		Vector3 screenPosition;
	};
}

