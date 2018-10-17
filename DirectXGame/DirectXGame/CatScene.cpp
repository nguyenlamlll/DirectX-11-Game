#include "CatScene.h"

using namespace DirectXCore;
using DirectX::SimpleMath::Vector3;

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
	m_sprite->Render();
	m_text->RenderText();
}

void CatScene::LoadScene()
{
	m_dxBase->CreateSprite(L"cat.png", &m_sprite);
	m_sprite->GetTransform()->SetPosition(Vector3(50, 50, 1));

	m_dxBase->CreateText(L"myfileb.spritefont", L"Hello!", &m_text);
	m_text->SetScreenPosition(Vector2(500, 500));

}

void CatScene::UnloadScene()
{
}

void CatScene::OnKeyUp(KeyCode)
{
}

void CatScene::OnKeyDown(KeyCode)
{
}

// Move a sprite around 4 corners, clockwise.
void CatScene::MoveSpriteAround(float elapsedTime)
{
	Vector3 currentPosition = m_sprite->GetTransform()->GetPosition();

	// At top left, aiming for top right.
	if (currentPosition.x <= 990 && currentPosition.y <= 710)
	{
		Vector3 newPosition(
			currentPosition.x + 700 * elapsedTime,
			currentPosition.y,
			1);

		m_sprite->GetTransform()->SetPosition(newPosition);

	}

	// At top right, aiming for bottom right.
	if (currentPosition.x >= 990 && currentPosition.y <= 710)
	{
		Vector3 newPosition(
			currentPosition.x,
			currentPosition.y + 700 * elapsedTime,
			1);

		m_sprite->GetTransform()->SetPosition(newPosition);
	}

	// At bottom right, aiming for bottom left.
	if (currentPosition.x >= 40 && currentPosition.y >= 710)
	{
		Vector3 newPosition(
			currentPosition.x - 700 * elapsedTime,
			currentPosition.y,
			1);

		m_sprite->GetTransform()->SetPosition(newPosition);
	}

	// At bottom left, aiming for top left.
	if (currentPosition.x <= 40 && currentPosition.y >= 70)
	{
		Vector3 newPosition(
			currentPosition.x,
			currentPosition.y - 700 * elapsedTime,
			1);

		m_sprite->GetTransform()->SetPosition(newPosition);
	}
}