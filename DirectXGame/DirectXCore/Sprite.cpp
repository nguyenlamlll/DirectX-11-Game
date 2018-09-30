#include "stdafx.h"
#include "Sprite.h"
using Microsoft::WRL::ComPtr;
using namespace DirectXCore;

Sprite::Sprite()
{

}

Sprite::Sprite(DirectXCore::DeviceResources * _deviceResource, const wchar_t * _charPath,float _scale)
{
	ComPtr<ID3D11Resource> resource;
	DirectXCore::ThrowIfFailed(DirectX::CreateWICTextureFromFile(_deviceResource->GetD3DDevice(), _charPath, resource.GetAddressOf(), m_texture.ReleaseAndGetAddressOf()));
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(_deviceResource->GetD3DDeviceContext());
	m_states = std::make_unique<DirectX::CommonStates>(_deviceResource->GetD3DDevice());

	ComPtr<ID3D11Texture2D> cat;
	CD3D11_TEXTURE2D_DESC spriteDesc;
	DirectXCore::ThrowIfFailed(resource.As(&cat));
	cat->GetDesc(&spriteDesc);
	m_center.x = float(spriteDesc.Width / 2);
	m_center.y = float(spriteDesc.Height / 2);
	m_screenPos.x = _deviceResource->GetOutputSize().right / 2;
	m_screenPos.y = _deviceResource->GetOutputSize().bottom / 2;

	m_tileRect = new RECT();
	m_tileRect->left = m_tileRect->top = 0;
	m_tileRect->right = spriteDesc.Width;
	m_tileRect->bottom = spriteDesc.Height;

	scale = _scale;
}


Sprite::~Sprite()
{
}
void Sprite::RenderSprite()
{
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, m_tileRect, DirectX::Colors::White, 0.f, m_center,scale);
	m_spriteBatch->End();
}

void Sprite::Reset()
{
	m_texture.Reset();
	m_states.reset();
}
