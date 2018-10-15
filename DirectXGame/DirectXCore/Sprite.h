#pragma once
#include "stdafx.h"
#include "DeviceResources.h"
//#include "Object.h"
#include "GameObject.h"
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
		void Render(DirectX::SimpleMath::Vector3 _newPosition);
		void Reset();

		void SetSpriteRect(RECT* _newSpriteRect);
		RECT GetSpriteRect() { return *spriterect; }
		void SetCenter(DirectX::SimpleMath::Vector3 _pivot) { pivot = _pivot; }
		DirectX::SimpleMath::Vector3 GetCenter() { return pivot; }

		Vector3 GetWorldToScreenScale();

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		std::unique_ptr<DirectX::CommonStates> m_states;
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		DirectX::SimpleMath::Vector3 pivot;
		RECT *spriterect;
	};
}


