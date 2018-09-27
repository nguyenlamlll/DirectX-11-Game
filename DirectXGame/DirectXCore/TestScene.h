#pragma once
#include "Scene.h"
class TestScene :
	public DirectXCore::Scene
{
public:
	TestScene();
	~TestScene();

	void RenderScene() override;
	void LoadScene() override;
	void UnloadScene() override;

private:
	//std::vector<DirectXCore::Sound> m_sounds;
	//std::vector<DirectXCore::Sprite> m_sprites;
	//std::vector<DirectXCore::Animation> m_animations;
	//DirectXCore::Sprite m_background;

	//void MoveObjectAround();
};

