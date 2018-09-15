#pragma once
#include "stdafx.h"
#include "DeviceResources.h"

class Sprite
{
public:
	Sprite();
	Sprite(DirectXCore::DeviceResources* _deviceResource,const wchar_t* _charPath);
	~Sprite();
	void CreateSprite(DirectXCore::DeviceResources* dev);
	void RenderSprite(DirectXCore::DeviceResources *dev);
	void Reset();
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	DirectX::SimpleMath::Vector2 m_screenPos;
	DirectX::SimpleMath::Vector2 m_origin;
};

