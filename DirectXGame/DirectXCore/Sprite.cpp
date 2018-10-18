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
	//transform.SetPosition(SimpleMath::Vector3(_deviceResource->GetOutputSize().right / 2, _deviceResource->GetOutputSize().bottom / 2));
	transform = new Transform(Vector3(_deviceResource->GetOutputSize().right / 2, _deviceResource->GetOutputSize().bottom / 2, 1), Vector3(0, 0, 1), Vector3(1, 1, 1));

	spriterect = new RECT();
	spriterect->left = spriterect->top = 0;
	spriterect->right = spriteDesc.Width;
	spriterect->bottom = spriteDesc.Height;


	//scale.x = _scale;
	//scale.y = _scale;
	transform->SetScale(SimpleMath::Vector3(_scale, _scale, 1));
}


Sprite::~Sprite()
{
}
void Sprite::Update()
{
	Vector3* colliderCenter = new Vector3(transform->GetPosition().x + transform->GetScale().x / 2, transform->GetPosition().y + transform->GetScale().y / 2, 1);
	boxCollider->Center = Vector3(colliderCenter->x, colliderCenter->y, 1);
	boxCollider->Extents = Vector3(transform->GetScale().x / 2 + spriterect->right / 2, transform->GetScale().y / 2 + spriterect->bottom / 2, 1);
}
void Sprite::Render()
{
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_spriteBatch->Draw(m_texture.Get(), transform->GetPosition(), spriterect, DirectX::Colors::White, 0.f, pivot, transform->GetScale());
	m_spriteBatch->End();
}
void Sprite::Render(DirectX::SimpleMath::Vector3 _newPosition)
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

void Sprite::SetSpriteRect(RECT * _newSpriteRect)
{
	spriterect->top = _newSpriteRect->top;
	spriterect->bottom = _newSpriteRect->bottom;
	spriterect->left = _newSpriteRect->left;
	spriterect->right = _newSpriteRect->right;
}

Vector3 Sprite::GetWorldToScreenScale()
{
	Vector3 screenScale = this->GetTransform()->GetScale();
	screenScale.x += spriterect->right / 2;
	screenScale.y += spriterect->bottom / 2;
	return screenScale;
}
