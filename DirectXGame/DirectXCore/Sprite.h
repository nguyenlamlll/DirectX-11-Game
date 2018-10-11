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
		void RenderSprite();
		void RenderSprite(DirectX::SimpleMath::Vector2 _newPosition);
		void Reset();

		void SetSpriteRect(RECT* _newSpriteRect);
		RECT GetSpriteRect() { return *spriterect; }
		void SetCenter(DirectX::SimpleMath::Vector2 _pivot) { pivot = _pivot; }
		DirectX::SimpleMath::Vector2 GetCenter() { return pivot; }

		Vector2 GetWorldToScreenScale();

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		std::unique_ptr<DirectX::CommonStates> m_states;
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		DirectX::SimpleMath::Vector2 pivot;
		RECT *spriterect;
	};
}


