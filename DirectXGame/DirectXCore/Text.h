#pragma once
#include "stdafx.h"
#include "DeviceResources.h"
#include <memory>
#include <SpriteFont.h>
#include <SpriteBatch.h>

namespace DirectXCore
{
	class Text
	{
	public:
		Text();
		Text(DeviceResources* _deviceResource, const wchar_t* _fontPath, const wchar_t* _content);
		~Text();

		void RenderText();
		void Reset();

		void SetScreenPosition(DirectX::SimpleMath::Vector2 newPosition) { m_screenPosition = newPosition; }

	private:
		// Position of the text to be drawn on screen.
		DirectX::SimpleMath::Vector2 m_screenPosition;

		DirectX::SimpleMath::Vector2 m_origin;

		// Content of this text.
		const wchar_t* m_content;

		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		std::unique_ptr<DirectX::SpriteFont> m_font;
	};
}

