#include "PingPongScene.h"

using namespace DirectXCore;
using DirectX::SimpleMath::Vector2;

PingPongScene::PingPongScene(DirectXCore::DxBase* dxBase)
	: m_isLeftPadMoveDown(false),
	m_isLeftPadMoveUp(false),
	m_isRightPadMoveDown(false),
	m_isRightPadMoveUp(false)
{
	m_dxBase = std::shared_ptr<DxBase>(dxBase);
}


PingPongScene::~PingPongScene()
{
}

#define S_KEY 0x53
#define W_KEY 0x57
#define SPEED 300
void PingPongScene::UpdateScene(float elapsedTime)
{
	if (m_isLeftPadMoveDown)
	{
		Vector2 currentPosition = m_leftPad->GetScreenPosition();
		MovePad(m_leftPad, Vector2(currentPosition.x, currentPosition.y + SPEED * elapsedTime));
	}
	if (m_isLeftPadMoveUp)
	{
		Vector2 currentPosition = m_leftPad->GetScreenPosition();
		MovePad(m_leftPad, Vector2(currentPosition.x, currentPosition.y - SPEED * elapsedTime));
	}

	if (m_isRightPadMoveDown)
	{
		Vector2 currentPosition = m_rightPad->GetScreenPosition();
		MovePad(m_rightPad, Vector2(currentPosition.x, currentPosition.y + SPEED * elapsedTime));
	}
	if (m_isRightPadMoveUp)
	{
		Vector2 currentPosition = m_rightPad->GetScreenPosition();
		MovePad(m_rightPad, Vector2(currentPosition.x, currentPosition.y - SPEED * elapsedTime));
	}
}

void PingPongScene::RenderScene()
{
	m_leftPad->RenderSprite();
	m_rightPad->RenderSprite();
}

void PingPongScene::LoadScene()
{
	m_dxBase->CreateSprite(L"Resources\\button.png", &m_leftPad);
	m_leftPad->SetScreenPosition(Vector2(50, 384));

	m_dxBase->CreateSprite(L"Resources\\button.png", &m_rightPad);
	m_rightPad->SetScreenPosition(Vector2(974, 384));
}

void PingPongScene::UnloadScene()
{
}

void PingPongScene::OnKeyUp(KeyCode key)
{
	if (key == S_KEY)
	{
		m_isLeftPadMoveDown = false;
	}
	if (key == W_KEY)
	{
		m_isLeftPadMoveUp = false;
	}

	if (key == VK_DOWN)
	{
		m_isRightPadMoveDown = false;
	}
	if (key == VK_UP)
	{
		m_isRightPadMoveUp = false;
	}
}

void PingPongScene::OnKeyDown(KeyCode key)
{
	if (key == S_KEY)
	{
		m_isLeftPadMoveDown = true;
	}
	if (key == W_KEY)
	{
		m_isLeftPadMoveUp = true;
	}

	if (key == VK_DOWN)
	{
		m_isRightPadMoveDown = true;
	}
	if (key == VK_UP)
	{
		m_isRightPadMoveUp = true;
	}
}

void PingPongScene::MovePad(Sprite* pad, Vector2 newPosition)
{
	pad->SetScreenPosition(newPosition);
}
