#include "TilemapScene.h"

using namespace DirectXCore;
using DirectX::SimpleMath::Vector2;

TilemapScene::TilemapScene(DxBase* dxBase)
{
	m_dxBase = std::shared_ptr<DxBase>(dxBase);
}

TilemapScene::~TilemapScene()
{
}

void TilemapScene::UpdateScene(float elapsedTime)
{
	tilemap->Update();
}

void TilemapScene::RenderScene()
{
	tilemap->Render();
}

void TilemapScene::LoadScene()
{
	m_dxBase->CreateTilemap(L"Resources/marioworld1-1.tmx" , &tilemap);
	//mainCamera = new Camera(m_deviceResources->GetOutputSize().right / 2, m_deviceResources->GetOutputSize().bottom);
	//tilemap = new TileMap(, L"Resources/untitled.tmx");
	//tilemap->SetCamera(mainCamera);
}

void TilemapScene::UnloadScene()
{
}