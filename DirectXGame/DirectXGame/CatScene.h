#pragma once
#include "Scene.h"
#include "DxBase.h"

class CatScene :
	public DirectXCore::Scene
{
public:
	CatScene(DirectXCore::DxBase* dxBase);
	~CatScene();

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

	DirectXCore::Sprite* m_sprite;
	DirectXCore::Text* m_text;

	void MoveSpriteAround(float elapsedTime);

};

