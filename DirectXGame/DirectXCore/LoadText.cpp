#include "stdafx.h"
#include "LoadText.h"
using Microsoft::WRL::ComPtr;
using namespace DirectXCore;


LoadText::LoadText()
{
	//m_dxBase = std::shared_ptr<DxBase>(dxBase);
}


LoadText::~LoadText()
{
}

bool LoadText::InitText()
{
	//CREATE SPRITEFONT OBJECT
	m_spriteFont.reset(new DirectX::SpriteFont(m_pDevice, L"myfile.spritefont"));
	
	return true;
}

void LoadText::RenderText(float dt)
{
	m_spriteBatch->Begin();
	//DRAW FONT
	m_spriteFont->DrawString(m_spriteBatch.get(), L"Game Start", DirectX::SimpleMath::Vector2(300, 300));
	m_spriteFont->DrawString(m_spriteBatch.get(), L"Option", DirectX::SimpleMath::Vector2(300, 300));

	m_spriteBatch->End();
}