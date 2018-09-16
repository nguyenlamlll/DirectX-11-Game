#pragma once
#include "stdafx.h"
#include "DeviceResources.h"

class Sprite
{
public:
	Sprite();
	Sprite(DirectXCore::DeviceResources* _deviceResource,const wchar_t* _charPath);
	~Sprite();
	void RenderSprite();
	void Reset();
	void SetSpriteRect(RECT _newSpriteRect) {
		*m_tileRect = _newSpriteRect;
	}
	RECT GetSpriteRect() {
		return *m_tileRect;
	}
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;
	RECT *m_tileRect;
};

