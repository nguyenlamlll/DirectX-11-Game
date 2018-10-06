#include "CatScene.h"

using namespace DirectXCore;
using DirectX::SimpleMath::Vector2;

CatScene::CatScene(DxBase* dxBase)
{
	m_dxBase = std::shared_ptr<DxBase>(dxBase);
}

CatScene::~CatScene()
{
}

void CatScene::UpdateScene(float elapsedTime)
{
	MoveSpriteAround(elapsedTime);
}

void CatScene::RenderScene()
{
	m_sprite->RenderSprite();
}

void CatScene::LoadScene()
{
	m_dxBase->CreateSprite(L"cat.png", &m_sprite);
	m_sprite->GetTransform()->SetPosition(Vector2(50, 50));
}

void CatScene::UnloadScene()
{
}

// Move a sprite around 4 corners, clockwise.
void CatScene::MoveSpriteAround(float elapsedTime)
{
	Vector2 currentPosition = m_sprite->GetTransform()->GetPosition();

	// At top left, aiming for top right.
	if (currentPosition.x <= 990 && currentPosition.y <= 710)
	{
		Vector2 newPosition(
			currentPosition.x + 700 * elapsedTime,
			currentPosition.y);

		m_sprite->GetTransform()->SetPosition(newPosition);

	}

	// At top right, aiming for bottom right.
	if (currentPosition.x >= 990 && currentPosition.y <= 710)
	{
		Vector2 newPosition(
			currentPosition.x,
			currentPosition.y + 700 * elapsedTime);

		m_sprite->GetTransform()->SetPosition(newPosition);
	}

	// At bottom right, aiming for bottom left.
	if (currentPosition.x >= 40 && currentPosition.y >= 710)
	{
		Vector2 newPosition(
			currentPosition.x - 700 * elapsedTime,
			currentPosition.y);

		m_sprite->GetTransform()->SetPosition(newPosition);
	}

	// At bottom left, aiming for top left.
	if (currentPosition.x <= 40 && currentPosition.y >= 70)
	{
		Vector2 newPosition(
			currentPosition.x,
			currentPosition.y - 700 * elapsedTime);

		m_sprite->GetTransform()->SetPosition(newPosition);
	}
}