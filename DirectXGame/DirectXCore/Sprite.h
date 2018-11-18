#pragma once
#include "stdafx.h"
#include "DeviceResources.h"
#include "GameObject.h"
#include "Renderer.h"
#include <CommonStates.h>

namespace DirectXCore 
{
	class Sprite : public GameObject
	{
	public:
		Sprite();
		Sprite(DirectXCore::DeviceResources* _deviceResource, const wchar_t* _charPath, float _scale = 1.0f);
		~Sprite();
		void Update() override;
		void Render();


		void SetSpriteRect(RECT* _newSpriteRect);
		RECT GetSpriteRect() { return *spriterect; }
		void SetCenter(DirectX::SimpleMath::Vector3 _pivot) { pivot = _pivot; }
		DirectX::SimpleMath::Vector3 GetCenter() { return pivot; }


	private:
		DirectX::SimpleMath::Vector3 pivot;
		RECT *spriterect;
		Renderer* spriteRenderer;
	};
}


