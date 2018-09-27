#pragma once
#include "Scene.h"
#include "DxBase.h"
class CatScene :
	public DirectXCore::Scene
{
public:
	CatScene(DirectXCore::DxBase* dxBase);
	~CatScene();

	void RenderScene() override;
	void LoadScene() override;
	void UnloadScene() override;

private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;

	DirectXCore::Sprite* m_sprite;
};

