#include "stdafx.h"
#include "Text.h"
using Microsoft::WRL::ComPtr;
using namespace DirectXCore;
using namespace DirectX;

Text::Text()
{
}

Text::Text(DeviceResources* _deviceResource, const wchar_t* _fontPath, const wchar_t* _content)
{
	m_font = std::make_unique<SpriteFont>(_deviceResource->GetD3DDevice(), _fontPath);
	m_spriteBatch = std::make_unique<SpriteBatch>(_deviceResource->GetD3DDeviceContext());
	m_content = _content;

	m_screenPosition.x = _deviceResource->GetOutputSize().right / 2;
	m_screenPosition.y = _deviceResource->GetOutputSize().bottom / 2;

	m_origin = m_font->MeasureString(m_content) / 2.f;
}

Text::~Text()
{
}

void Text::RenderText()
{
	m_spriteBatch->Begin();
	m_font->DrawString(m_spriteBatch.get(), m_content, m_screenPosition, Colors::White, 0.f, m_origin);
	m_spriteBatch->End();
}

void DirectXCore::Text::Reset()
{
	m_font.reset();
	m_spriteBatch.reset();
}
