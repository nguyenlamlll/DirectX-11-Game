#pragma once
#include "Scene.h"
#include "DxBase.h"

class PingPongScene :
	public DirectXCore::Scene
{
public:
	PingPongScene(DirectXCore::DxBase* dxBase);
	~PingPongScene();

	void UpdateScene(float elapsedTime) override;
	void RenderScene() override;
	void LoadScene() override;
	void UnloadScene() override;

	void OnKeyUp(KeyCode) override;
	void OnKeyDown(KeyCode) override;

private:
	std::shared_ptr<DirectXCore::DxBase> m_dxBase;

	DirectXCore::Sprite* m_leftPad;
	DirectXCore::Sprite* m_rightPad;

	std::shared_ptr<DirectXCore::Sprite> m_ball;

	bool m_isLeftPadMoveDown;
	bool m_isLeftPadMoveUp;

	bool m_isRightPadMoveDown;
	bool m_isRightPadMoveUp;

	void MoveSprite(DirectXCore::Sprite* pad, DirectX::SimpleMath::Vector2 newPosition);
};

