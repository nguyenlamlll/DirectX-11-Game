#pragma once
#include "Scene.h"
#include "DxBase.h"

class MenuScene :
	public DirectXCore::Scene
{
public:
	MenuScene(DirectXCore::DxBase* dxBase);
	~MenuScene();

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

private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;

	float m_currentTimer = 0;
	bool isAcceptingPress = true;
	unsigned int m_currentlySelectedOption = 1;

	DirectXCore::Sound* m_introductionMusic;

	DirectXCore::Sprite* m_logoSprite;

	DirectXCore::Text* m_GameStartText;
	DirectXCore::Text* m_PassWordText;
	DirectXCore::Text* m_OptionModeText;

	DirectXCore::GameObject* m_logoGameObject;
	DirectXCore::Camera* m_camera;
	DirectXCore::TileMap* m_tilemap;
};

