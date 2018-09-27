#include "CatScene.h"

using namespace DirectXCore;

CatScene::CatScene(DxBase * dxBase)
{
	m_dxBase = std::shared_ptr<DxBase>(dxBase);
}

CatScene::~CatScene()
{
}

void CatScene::RenderScene()
{
	m_sprite->RenderSprite();
}

void CatScene::LoadScene()
{
	m_dxBase->CreateSprite(L"cat.png", &m_sprite);
}

void CatScene::UnloadScene()
{
}
