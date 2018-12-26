#include "MenuScene.h"

using namespace DirectXCore;
using DirectX::SimpleMath::Vector3;

MenuScene::MenuScene(DirectXCore::DxBase* dxBase)
{
	m_dxBase = std::shared_ptr<DxBase>(dxBase);
}


MenuScene::~MenuScene()
{
}

void MenuScene::UpdateScene(float elapsedTime)
{
	// TIMER
	if (m_currentTimer >= 0.5f) {
		m_currentTimer = 0;
		isAcceptingPress = true;
	}
	else m_currentTimer += elapsedTime;


	if (m_dxBase->GetInputManager()->IsKeyDown("S") && isAcceptingPress)
	{
		if (m_currentlySelectedOption >= 3)
		{
			m_currentlySelectedOption = 1;
		}
		else
		{
			m_currentlySelectedOption += 1;
		}
		isAcceptingPress = false;
	}
	else
	{

	}

	if (m_dxBase->GetInputManager()->IsKeyDown("W") && isAcceptingPress)
	{
		if (m_currentlySelectedOption <= 1)
		{
			m_currentlySelectedOption = 3;
		}
		else
		{
			m_currentlySelectedOption -= 1;
		}
		isAcceptingPress = false;
	}
	else
	{

	}

	switch (m_currentlySelectedOption)
	{
	case 1:
	{
		m_GameStartText->SetColor(DirectX::Colors::Orange);
		m_PassWordText->SetColor(DirectX::Colors::White);
		m_OptionModeText->SetColor(DirectX::Colors::White);
		break;
	}
	case 2:
	{
		m_GameStartText->SetColor(DirectX::Colors::White);
		m_PassWordText->SetColor(DirectX::Colors::Orange);
		m_OptionModeText->SetColor(DirectX::Colors::White);
		break;
	}
	case 3:
	{
		m_GameStartText->SetColor(DirectX::Colors::White);
		m_PassWordText->SetColor(DirectX::Colors::White);
		m_OptionModeText->SetColor(DirectX::Colors::Orange);
		break;
	}
	}
	m_logoGameObject->Update(elapsedTime);

	if (m_dxBase->GetInputManager()->IsKeyDown("Enter"))
	{
		m_dxBase->SwitchToScene(1);
	}
	else
	{

	}
}

void MenuScene::RenderScene()
{
	m_GameStartText->RenderText();
	m_PassWordText->RenderText();
	m_OptionModeText->RenderText();

	//m_logoSprite->Render();
	Vector3 worldToScreenShift = Vector3(m_camera->GetBound().right / 2 - m_camera->GetPosition().x, m_camera->GetBound().bottom / 2 - m_camera->GetPosition().y, 0);
	m_logoGameObject->GetTransform()->SetWorldToScreenPosition(worldToScreenShift);
	m_logoGameObject->Render();
}

void MenuScene::LoadScene()
{
	m_dxBase->CreateText(L"myfileb.spritefont", L"GAME START", &m_GameStartText);
	m_GameStartText->SetScreenPosition(Vector2(500, 500));
	m_GameStartText->SetColor(DirectX::Colors::Orange);

	m_dxBase->CreateText(L"myfileb.spritefont", L"PASS WORD", &m_PassWordText);
	m_PassWordText->SetScreenPosition(Vector2(500, 550));

	m_dxBase->CreateText(L"myfileb.spritefont", L"OPTION MODE", &m_OptionModeText);
	m_OptionModeText->SetScreenPosition(Vector2(500, 600));

	m_dxBase->CreateSoundAndMusic(L"Resources/Music/01 Introduction.wav", &m_introductionMusic);
	m_introductionMusic->Play();

	//m_dxBase->CreateSprite(L"Resources/Megaman_x3_logo.jpg", &m_logoSprite);
	//m_logoSprite->GetTransform()->SetPosition(Vector3(500, 200, 0));

	m_dxBase->CreateCamera(&m_camera);
	m_tilemap = new TileMap(m_dxBase->GetDeviceResource(), L"Resources/untitled.tmx");
	m_tilemap->SetCamera(m_camera);

	m_logoGameObject = new GameObject();
	m_logoGameObject->GetTransform()->SetPosition(Vector3(500.f, 220.f, 0));
	m_logoGameObject->GetTransform()->SetScreenScale(Vector3(0.4f, 0.4f, 0.4f));
	//m_logoGameObject->GetTransform()->SetScreenScale(Vector3(1, 1, 1));
	m_logoGameObject->AddComponent<Renderer>(new Renderer(m_dxBase->GetDeviceResource(), L"Resources/Megaman_x3_logo.jpg"));
}

void MenuScene::UnloadScene()
{
	if (m_GameStartText)
	{
		delete m_GameStartText;
	}

	if (m_PassWordText)
	{
		delete m_PassWordText;
	}

	if (m_OptionModeText)
	{
		delete m_OptionModeText;
	}

	if (m_introductionMusic)
	{

		delete m_introductionMusic;
	}
	if (m_logoGameObject)
	{
		delete m_logoGameObject;
	}
}
