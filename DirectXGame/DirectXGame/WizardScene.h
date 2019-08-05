#pragma once
#include "DirectXCore.h"
#include "Player.h"
#include "Enemy.h"
#include "WizardBoss.h"

class WizardScene : public DirectXCore::Scene
{
public:
	WizardScene();
	WizardScene(DxBase* _dxBase);
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
	~WizardScene();
private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;
	DirectXCore::Camera* camera;
	TileMap* bossTilemap;
	Player* player;
	Grid* mapGrid;
};

