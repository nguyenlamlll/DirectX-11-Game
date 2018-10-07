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

#define BALL_RADIUS 30
#define PIXELS_TO_LONG_EDGE 20
bool hitRight = true;
bool hitLeft = false;
float bounceAngle = 0.0f;
void PingPongScene::UpdateScene(float elapsedTime)
{
	bool isLeftPadDown, isLeftPadUp;
	if (m_dxBase->GetInputManager()->IsKeyDown("S"))
	{
		isLeftPadDown = true;
		Vector2 currentPosition = m_leftPad->GetScreenPosition();
		MoveSprite(m_leftPad, Vector2(currentPosition.x, currentPosition.y + SPEED * elapsedTime));
	}
	else 
	{
		isLeftPadDown = false;
	}
	if (m_dxBase->GetInputManager()->IsKeyDown("W"))
	{
		isLeftPadUp = true;
		Vector2 currentPosition = m_leftPad->GetScreenPosition();
		MoveSprite(m_leftPad, Vector2(currentPosition.x, currentPosition.y - SPEED * elapsedTime));
	}
	else
	{
		isLeftPadUp = false;
	}

	bool isRightPadDown, isRightPadUp;
	if (m_isRightPadMoveDown)
	{
		isRightPadDown = true;
		Vector2 currentPosition = m_rightPad->GetScreenPosition();
		MoveSprite(m_rightPad, Vector2(currentPosition.x, currentPosition.y + SPEED * elapsedTime));
	}
	else
	{
		isRightPadDown = false;
	}
	if (m_isRightPadMoveUp)
	{
		isRightPadUp = true;
		Vector2 currentPosition = m_rightPad->GetScreenPosition();
		MoveSprite(m_rightPad, Vector2(currentPosition.x, currentPosition.y - SPEED * elapsedTime));
	}
	else
	{
		isRightPadUp = false;
	}

	Vector2 ballCurrentPosition = m_ball->GetScreenPosition();
	Vector2 rightPadCurrentPosition = m_rightPad->GetScreenPosition();
	Vector2 leftPadCurrentPosition = m_leftPad->GetScreenPosition();
	if (hitRight == true)
	{
		MoveSprite(m_ball.get(), Vector2(
			ballCurrentPosition.x - SPEED * 0.75 * elapsedTime,
			ballCurrentPosition.y + bounceAngle * elapsedTime
		));

		if ((ballCurrentPosition.x - BALL_RADIUS) <= (leftPadCurrentPosition.x + PIXELS_TO_LONG_EDGE))
		{
			hitRight = false;
			hitLeft = true;
			if (isLeftPadDown)
			{
				bounceAngle = SPEED * 0.2;
			}
			if (isLeftPadUp)
			{
				bounceAngle = -SPEED * 0.2;
			}
		}
	}
	if (hitLeft == true)
	{
		MoveSprite(m_ball.get(), Vector2(
			ballCurrentPosition.x + SPEED * 0.75 * elapsedTime,
			ballCurrentPosition.y + bounceAngle * elapsedTime
		));

		if ((ballCurrentPosition.x + BALL_RADIUS) >= (rightPadCurrentPosition.x - PIXELS_TO_LONG_EDGE))
		{
			hitRight = true;
			hitLeft = false;
			if (isRightPadDown)
			{
				bounceAngle = SPEED * 0.2;
			}
			if (isRightPadUp)
			{
				bounceAngle = -SPEED * 0.2;
			}
		}
	}

}

void PingPongScene::RenderScene()
{
	m_leftPad->RenderSprite();
	m_rightPad->RenderSprite();
	m_ball->RenderSprite();
}

void PingPongScene::LoadScene()
{
	m_dxBase->CreateSprite(L"Resources\\button.png", &m_leftPad);
	m_leftPad->SetScreenPosition(Vector2(50, 384));

	m_dxBase->CreateSprite(L"Resources\\button.png", &m_rightPad);
	m_rightPad->SetScreenPosition(Vector2(974, 384));

	m_ball = std::make_unique<Sprite>();
	auto temp = m_ball.get();
	m_dxBase->CreateSprite(L"Resources\\neon-circle.png", &temp);
	m_ball.reset(temp);
	m_ball->SetScale(0.5, 0.5);
}

void PingPongScene::UnloadScene()
{
}

void PingPongScene::OnKeyUp(KeyCode key)
{
	//if (key == S_KEY)
	//{
	//	m_isLeftPadMoveDown = false;
	//}
	//if (key == W_KEY)
	//{
	//	m_isLeftPadMoveUp = false;
	//}

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
	//if (key == S_KEY)
	//{
	//	m_isLeftPadMoveDown = true;
	//}
	//if (key == W_KEY)
	//{
	//	m_isLeftPadMoveUp = true;
	//}

	if (key == VK_DOWN)
	{
		m_isRightPadMoveDown = true;
	}
	if (key == VK_UP)
	{
		m_isRightPadMoveUp = true;
	}
}

void PingPongScene::MoveSprite(Sprite* sprite, Vector2 newPosition)
{
	sprite->SetScreenPosition(newPosition);
}
