#pragma once
#include "stdafx.h"
#include "DeviceResources.h"
#include <CommonStates.h>

namespace DirectXCore 
{
	class Sprite
	{
	public:
		Sprite();
		Sprite(DirectXCore::DeviceResources* _deviceResource, const wchar_t* _charPath);
		~Sprite();
		void RenderSprite();
		void Reset();


		void SetSpriteRect(RECT _newSpriteRect) { *m_tileRect = _newSpriteRect; }
		RECT GetSpriteRect() { return *m_tileRect; }
		void SetCenter(DirectX::SimpleMath::Vector2 _center) { m_center = _center; }
		DirectX::SimpleMath::Vector2 GetCenter() { return m_center; }
		void SetScreenPosition(DirectX::SimpleMath::Vector2 _screenPos) { m_screenPos = _screenPos; }
		DirectX::SimpleMath::Vector2 GetScreenPOs() { return m_screenPos; }

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		std::shared_ptr<DirectX::CommonStates> m_states;
		std::shared_ptr<DirectX::SpriteBatch> m_spriteBatch;
		DirectX::SimpleMath::Vector2 m_screenPos;
		DirectX::SimpleMath::Vector2 m_center;
		RECT *m_tileRect;
	};
}


