#pragma once
using namespace DirectX::SimpleMath;

namespace DirectXCore
{
	class Transform
	{
	public:
		Transform();
		Transform(Vector2 _pos,Vector2 _rot, Vector2 _scl);
		Vector2 GetPosition() { return position; }
		Vector2 GetWorldToCameraPosition(Vector2 _cameraPosition) { return position + _cameraPosition; }
		void SetPosition(Vector2 _newPosition);
		void LerpPosition(Vector2 _newPosition,float _deltatime) { position.Lerp(position,_newPosition,_deltatime); }

		Vector2 GetRotation() { return rotation; }
		void SetRotation(Vector2 _newRotation) { rotation = _newRotation; }

		Vector2 GetScale() { return scale; }
		void SetScale(Vector2 _newScale) { scale = _newScale; }

		~Transform();
	private:
		Vector2 position, rotation, scale;
	};
}

