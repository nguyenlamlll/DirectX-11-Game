#pragma once
#include "DirectXCore.h"
#include "Player.h"
#include "Enemy.h"

class PittsburghScene : public DirectXCore::Scene
{
public:
	PittsburghScene();
	PittsburghScene(DxBase* _dxBase);
	// Logic that requires elapsedTime and game logic.
	void UpdateScene(float elapsedTime) override;

	// Logics for rendering only.
	void RenderScene() override;

	// Initialize necessary resources (loading sprites, animations, sounds, and music tracks...)
	void LoadScene() override;

	// Scene is probably inactive but the game is yet over. To save memory, unload this scene completely.
	void UnloadScene() override;

	void OnKeyUp(KeyCode) override { }
	void OnKeyDown(KeyCode) override { }
	~PittsburghScene();
private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;
	DirectXCore::Camera* camera;
	TileMap* tilemap;
	Player* player;
	Grid* grid;
};

