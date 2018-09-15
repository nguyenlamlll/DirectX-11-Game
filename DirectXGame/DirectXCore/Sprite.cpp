#include "stdafx.h"
#include "Sprite.h"
using Microsoft::WRL::ComPtr;

Sprite::Sprite()
{

}

Sprite::Sprite(DirectXCore::DeviceResources * _deviceResource, const wchar_t * _charPath)
{
	DirectXCore::ThrowIfFailed(DirectX::CreateWICTextureFromFile(_deviceResource->GetD3DDevice(),_charPath, nullptr, m_texture.ReleaseAndGetAddressOf()));
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(_deviceResource->GetD3DDeviceContext());
	ComPtr<ID3D11Resource> resource;
	DirectXCore::ThrowIfFailed(DirectX::CreateWICTextureFromFile(_deviceResource->GetD3DDevice(), _charPath, resource.GetAddressOf(), m_texture.ReleaseAndGetAddressOf()));
	ComPtr<ID3D11Texture2D> cat;
	DirectXCore::ThrowIfFailed(resource.As(&cat));
	CD3D11_TEXTURE2D_DESC catDesc;
	cat->GetDesc(&catDesc);
	m_origin.x = float(catDesc.Width / 2) - 100;
	m_origin.y = float(catDesc.Height / 2) - 100;
}


Sprite::~Sprite()
{
}

void Sprite::CreateSprite(DirectXCore::DeviceResources *dev)
{
	DirectXCore::ThrowIfFailed(DirectX::CreateWICTextureFromFile(dev->GetD3DDevice(), L"cat.png", nullptr, m_texture.ReleaseAndGetAddressOf()));
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(dev->GetD3DDeviceContext());
	ComPtr<ID3D11Resource> resource;
	DirectXCore::ThrowIfFailed(DirectX::CreateWICTextureFromFile(dev->GetD3DDevice(), L"cat.png", resource.GetAddressOf(), m_texture.ReleaseAndGetAddressOf()));
	ComPtr<ID3D11Texture2D> cat;
	DirectXCore::ThrowIfFailed(resource.As(&cat));
	CD3D11_TEXTURE2D_DESC catDesc;
	cat->GetDesc(&catDesc);
	m_origin.x = float(catDesc.Width / 2) - 100;
	m_origin.y = float(catDesc.Height / 2) - 100;
}

void Sprite::RenderSprite(DirectXCore::DeviceResources *dev)
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, DirectX::Colors::White, 0.f, m_origin);
	m_spriteBatch->End();
}

void Sprite::Reset()
{
	m_texture.Reset();
}
