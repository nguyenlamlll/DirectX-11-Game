#include "stdafx.h"
#include "Sprite.h"
using Microsoft::WRL::ComPtr;
using namespace DirectXCore;

Sprite::Sprite()
{

}

Sprite::Sprite(DirectXCore::DeviceResources * _deviceResource, const wchar_t * _charPath, float _scale)
{
	ComPtr<ID3D11Resource> resource;
	DirectXCore::ThrowIfFailed(DirectX::CreateWICTextureFromFile(_deviceResource->GetD3DDevice(), _charPath, resource.GetAddressOf(), m_texture.ReleaseAndGetAddressOf()));
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(_deviceResource->GetD3DDeviceContext());
	m_states = std::make_unique<DirectX::CommonStates>(_deviceResource->GetD3DDevice());

	ComPtr<ID3D11Texture2D> cat;
	CD3D11_TEXTURE2D_DESC spriteDesc;
	DirectXCore::ThrowIfFailed(resource.As(&cat));
	cat->GetDesc(&spriteDesc);
	pivot.x = float(spriteDesc.Width / 2);
	pivot.y = float(spriteDesc.Height / 2);
	//position.x = _deviceResource->GetOutputSize().right / 2;
	//position.y = _deviceResource->GetOutputSize().bottom / 2;
	//transform.SetPosition(SimpleMath::Vector2(_deviceResource->GetOutputSize().right / 2, _deviceResource->GetOutputSize().bottom / 2));
	transform = new Transform(Vector2(_deviceResource->GetOutputSize().right / 2, _deviceResource->GetOutputSize().bottom / 2), Vector2(0, 0), Vector2(1, 1));

	spriterect = new RECT();
	spriterect->left = spriterect->top = 0;
	spriterect->right = spriteDesc.Width;
	spriterect->bottom = spriteDesc.Height;


	//scale.x = _scale;
	//scale.y = _scale;
	transform->SetScale(SimpleMath::Vector2(_scale, _scale));
}


Sprite::~Sprite()
{
}
void Sprite::RenderSprite()
{
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_spriteBatch->Draw(m_texture.Get(), transform->GetPosition(), spriterect, DirectX::Colors::White, 0.f, pivot, transform->GetScale());
	m_spriteBatch->End();
}
void Sprite::RenderSprite(DirectX::SimpleMath::Vector2 _newPosition)
{
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_spriteBatch->Draw(m_texture.Get(), _newPosition, spriterect, DirectX::Colors::White, 0.f, pivot, transform->GetScale());
	m_spriteBatch->End();
}

void Sprite::Reset()
{
	m_texture.Reset();
	m_states.reset();
}

void DirectXCore::Sprite::SetSpriteRect(RECT * _newSpriteRect)
{
	spriterect->top = _newSpriteRect->top;
	spriterect->bottom = _newSpriteRect->bottom;
	spriterect->left = _newSpriteRect->left;
	spriterect->right = _newSpriteRect->right;
}
