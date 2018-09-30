#pragma once
#include "stdafx.h"

namespace DirectXCore
{
	class Camera
	{
	public:
		Camera();
		Camera(int _x, int _y);
		void SetPosition(int _x, int _y);
		void SetPosition(DirectX::SimpleMath::Vector2 _pos) { camPosition = _pos; }
		DirectX::SimpleMath::Vector2 GetPosition() { return camPosition; }
		RECT GetBound();
		DirectX::SimpleMath::Matrix GetView() { return DirectX::XMMatrixLookAtRH(this->GetPosition(), DirectX::SimpleMath::Vector3::Forward, DirectX::SimpleMath::Vector3::Up); }
		int GetWidth() { return camViewport.Width; }
		int GetHeight() { return camViewport.Height; }
		bool IsContain(DirectX::SimpleMath::Vector2 _objectPosition);

		void SetViewPort(int _upperX, int _upperY, int _wid, int _hei);
		void InitializeOthoMatrix(int _wid, int _hei, float _near, float _far);
		void InitializeProjectionMatrix(float _fov, float _aspect, float _near, float _far);
		~Camera();
	private:
		DirectX::SimpleMath::Vector2 camPosition;
		D3D11_VIEWPORT camViewport;
		DirectX::SimpleMath::Vector4 view;
		DirectX::SimpleMath::Vector4 projection;
		DirectX::SimpleMath::Vector4 ortho;
	};
}

