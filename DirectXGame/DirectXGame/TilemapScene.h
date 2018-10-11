#pragma once
#include "Scene.h"
#include "DxBase.h"
#include "GameObject.h"


class TilemapScene :
	public DirectXCore::Scene
{
public:
	TilemapScene(DirectXCore::DxBase* dxBase);
	~TilemapScene();

	// Logic that requires elapsedTime and game logic.
	void UpdateScene(float elapsedTime) override;

	// Logics for rendering only.
	void RenderScene() override;

	// Initialize necessary resources (loading sprites, animations, sounds, and music tracks...)
	void LoadScene() override;

	// Scene is probably inactive but the game is yet over. To save memory, unload this scene completely.
	void UnloadScene() override;

private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;

	DirectXCore::TileMap* tilemap;

};

