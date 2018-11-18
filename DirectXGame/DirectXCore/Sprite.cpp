#include "stdafx.h"
#include "Sprite.h"
using Microsoft::WRL::ComPtr;
using namespace DirectXCore;

Sprite::Sprite()
{

}

Sprite::Sprite(DirectXCore::DeviceResources * _deviceResource, const wchar_t * _charPath, float _scale)
{
	//pivot.x = float(spriteDesc.Width / 2);
	pivot.x = 0;
	//pivot.y = float(spriteDesc.Height / 2);
	pivot.y = 0;
	transform = new Transform(Vector3(_deviceResource->GetOutputSize().right / 2, _deviceResource->GetOutputSize().bottom / 2, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));

	spriterect = new RECT();
	transform->SetRotation(Vector3(0,0,0));
	transform->SetScale(SimpleMath::Vector3(_scale, _scale, 1));
	if (!GetComponent<Renderer>()) {
		AddComponent<Renderer>(new Renderer(_deviceResource, _charPath, this));
		SetSpriteRect(GetComponent<Renderer>()->GetRECT());
		spriterect = GetComponent<Renderer>()->GetRECT();
	}
	transform->SetScreenScale(SimpleMath::Vector3(spriterect->right, spriterect->bottom, 1));
}


Sprite::~Sprite()
{
}

void Sprite::Update()
{
	for (size_t i = 0; i < componentList->size(); i++)
	{
		componentList->at(i)->Update();
	}
	Collider *collider = GetComponent<Collider>();
	if (collider)
	{
		collider->SetColliderScale(Vector3(transform->GetScale().x * spriterect->right, transform->GetScale().y * spriterect->bottom, 1));
		collider->SetColliderPosition(transform->GetPosition());
		int a = 1;
	}
}

void Sprite::Render()
{
	for (size_t i = 0; i < componentList->size(); i++)
	{
		componentList->at(i)->Render();
	}
}

void Sprite::SetSpriteRect(RECT * _newSpriteRect)
{
	spriterect->top = _newSpriteRect->top;
	spriterect->bottom = _newSpriteRect->bottom;
	spriterect->left = _newSpriteRect->left;
	spriterect->right = _newSpriteRect->right;
}

