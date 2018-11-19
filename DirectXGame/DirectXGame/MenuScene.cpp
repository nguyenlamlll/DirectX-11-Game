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
	if (m_currentTimer >= 0.5f) {
		m_currentTimer = 0;
		isAcceptingPress = true;
	}
	else m_currentTimer += elapsedTime;


	if (m_dxBase->GetInputManager()->IsKeyUp("S") && isAcceptingPress)
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

	if (m_dxBase->GetInputManager()->IsKeyUp("W") && isAcceptingPress)
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
}
