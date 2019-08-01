#include "stdafx.h"
#include "Renderer.h"
#include "Sprite.h"

using namespace DirectXCore;
using Microsoft::WRL::ComPtr;

DirectXCore::Renderer::Renderer()
{
}

DirectXCore::Renderer::Renderer(DeviceResources * _deviceResource, Sprite * _sprite)
{
}

DirectXCore::Renderer::Renderer(DeviceResources * _deviceResource, const wchar_t * _charPath)
{
	deviceResource = _deviceResource;
	ComPtr<ID3D11Resource> resource;
	ThrowIfFailed(CreateWICTextureFromFile(deviceResource->GetD3DDevice(), _charPath, resource.GetAddressOf(), m_texture.ReleaseAndGetAddressOf()));
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceResource->GetD3DDeviceContext());
	m_states = std::make_unique<DirectX::CommonStates>(deviceResource->GetD3DDevice());

	ComPtr<ID3D11Texture2D> texture;
	CD3D11_TEXTURE2D_DESC spriteDesc;
	ThrowIfFailed(resource.As(&texture));
	texture->GetDesc(&spriteDesc);
	pivot = Vector3(0, 0, 0);
	pivot = Vector3(spriteDesc.Width / 2, spriteDesc.Height / 2, 0);

	spriterect = new RECT();
	spriterect->top = spriterect->left = 0;
	spriterect->bottom = spriteDesc.Height;
	spriterect->right = spriteDesc.Width;
}

DirectXCore::Renderer::Renderer(DeviceResources * _deviceResource, const wchar_t * _charPath, Sprite * _sprite)
{
	sprite = _sprite;
	ComPtr<ID3D11Resource> resource;
	ThrowIfFailed(CreateWICTextureFromFile(_deviceResource->GetD3DDevice(), _charPath, resource.GetAddressOf(), m_texture.ReleaseAndGetAddressOf()));
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(_deviceResource->GetD3DDeviceContext());
	m_states = std::make_unique<DirectX::CommonStates>(_deviceResource->GetD3DDevice());

	ComPtr<ID3D11Texture2D> texture;
	CD3D11_TEXTURE2D_DESC spriteDesc;
	ThrowIfFailed(resource.As(&texture));
	texture->GetDesc(&spriteDesc);
	pivot = Vector3(0, 0, 0);
	pivot = Vector3(spriteDesc.Width / 2, spriteDesc.Height / 2, 0);

	spriterect = new RECT();
	spriterect->top = spriterect->left = 0;
	spriterect->bottom = spriteDesc.Height;
	spriterect->right = spriteDesc.Width;
}

void DirectXCore::Renderer::LoadTexture(const wchar_t * _charPath)
{
	ComPtr<ID3D11Resource> resource;
	ThrowIfFailed(CreateWICTextureFromFile(deviceResource->GetD3DDevice(), _charPath, resource.GetAddressOf(), m_texture.ReleaseAndGetAddressOf()));
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceResource->GetD3DDeviceContext());
	m_states = std::make_unique<DirectX::CommonStates>(deviceResource->GetD3DDevice());

	ComPtr<ID3D11Texture2D> texture;
	CD3D11_TEXTURE2D_DESC spriteDesc;
	ThrowIfFailed(resource.As(&texture));
	texture->GetDesc(&spriteDesc);
	pivot = Vector3(0, 0, 0);

	spriterect = new RECT();
	spriterect->top = spriterect->left = 0;
	spriterect->bottom = spriteDesc.Height;
	spriterect->right = spriteDesc.Width;

	//sprite->SetSpriteRect(spriterect);
}

void DirectXCore::Renderer::Render()
{
	DirectX::SpriteEffects effect = (attachedGameObject->GetTransform()->GetRotation().y == 0) ? DirectX::SpriteEffects_None : DirectX::SpriteEffects_FlipHorizontally;
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_spriteBatch->Draw(m_texture.Get(), attachedGameObject->GetTransform()->GetWorldToScreenPosition(), spriterect, Colors::White, attachedGameObject->GetTransform()->GetRotation().x, pivot, attachedGameObject->GetTransform()->GetScreenScale(), effect);
	m_spriteBatch->End();
}

void DirectXCore::Renderer::Render(SimpleMath::Vector3 _newPos)
{
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_spriteBatch->Draw(m_texture.Get(), _newPos, spriterect, Colors::White, 0.f, pivot, attachedGameObject->GetTransform()->GetScreenScale(), DirectX::SpriteEffects_None);
	m_spriteBatch->End();
}

void DirectXCore::Renderer::Render(SimpleMath::Vector3 _newPos, SimpleMath::Vector3 _newRot, SimpleMath::Vector3 _newScl)
{
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_spriteBatch->Draw(m_texture.Get(), _newPos, spriterect, Colors::White, _newRot.z, pivot, _newScl, DirectX::SpriteEffects_None);
	m_spriteBatch->End();
}

void DirectXCore::Renderer::Reset()
{
	m_texture.Reset();
	m_states.reset();
}

void DirectXCore::Renderer::SetRECT(RECT _newRECT)
{
	spriterect->top = _newRECT.top;
	spriterect->bottom = _newRECT.bottom;
	spriterect->left = _newRECT.left;
	spriterect->right = _newRECT.right;
}

void DirectXCore::Renderer::SetPivot(SimpleMath::Vector3 _newPivot)
{
	pivot.x = _newPivot.x;
	pivot.y = _newPivot.y;
	pivot.z = _newPivot.z;
}


DirectXCore::Renderer::~Renderer()
{
}
