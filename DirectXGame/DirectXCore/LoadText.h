#pragma once
#ifndef  __LOAD_TEXT_H__
#define  __LOAD_TEXT_H__

#include "stdafx.h"
#include "DeviceResources.h"
#include <memory>
#include <CommonStates.h>
#include <SpriteFont.h>
#include <SpriteBatch.h>
#include "SimpleMath.h"
#include "DxBase.h"


class LoadText
{
private:	
	DirectX::SimpleMath::Vector2 m_fontPos;
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	//std::unique_ptr<DirectX::SpriteFont> m_font;
	ID3D11Device* m_pDevice;
	
	


public:
	LoadText();
	//LoadText(DirectXCore::DeviceResources* _deviceResource, const wchar_t* _charPath, float _scale = 1.0f);
	~LoadText();

	bool InitText() ;
	void RenderText(float dt) ;

};

#endif // ! __LOAD_TEXT_H__