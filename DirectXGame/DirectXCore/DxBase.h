#pragma once
#include "DeviceResources.h"
#include "StepTimer.h"
#include "Sound.h"
#include <Audio.h>
#include "Sprite.h"
#include "Animation.h"
#include "TileMap.h"
#include "Scene.h"
#include "Text.h"
#include "Input.h"

namespace DirectXCore 
{
	class DxBase : public IDeviceNotify
	{
	public:
		DxBase() noexcept(false);
		~DxBase();

		// Initialization and management
		void Initialize(HWND window, int width, int height);

		void CreateSoundAndMusic(const wchar_t* soundFileName);
		DeviceResources* GetDeviceResource() { return m_deviceResources.get(); }
		void CreateCamera(Camera** returnCamera);
		void CreateTilemap(const wchar_t * tilemapSpriteName, TileMap** returnTilemap);
		void CreateSprite(const wchar_t* spriteName, Sprite** returnSprite);

		void CreateText(const wchar_t* fontPath, const wchar_t* content, Text** returnText);

		void SwitchToScene(wchar_t* name);
		void SwitchToScene(int index);
		void AddScene(Scene* scene);

		// Basic game loop
		void Tick();

		// IDeviceNotify
		virtual void OnDeviceLost() override;
		virtual void OnDeviceRestored() override;

		// Messages
		void OnActivated();
		void OnDeactivated();
		void OnSuspending();
		void OnResuming();
		void OnWindowMoved();
		void OnWindowSizeChanged(int width, int height);

		void OnKeyUp(KeyCode);
		void OnKeyDown(KeyCode);

		// Recommended way to handle input (comparing with OnKeyUp and OnKeyDown).
		// Each scene should get the input manager and ask for key states during UpdateScene method.
		Input* GetInputManager() { return m_input.get(); }
		
		// Properties
		void GetDefaultSize(int& width, int& height) const;

	private:
		void Update(StepTimer const& timer);
		void Render();
		void Clear();

		void CreateDeviceDependentResources();
		void CreateWindowSizeDependentResources();

		// Device resources.
		std::unique_ptr<DeviceResources> m_deviceResources;

		std::shared_ptr<DirectX::AudioEngine> m_audioEngine;
		std::vector<DirectXCore::Sound> m_sounds;

		//Sprite *sprite;
		//Animation *animation;
		TileMap *tilemap;
		Camera* mainCamera;


		// Rendering loop timer.
		StepTimer m_timer;

		// Scenes
		void InitializeScenes();
		std::vector<Scene*> m_scenes;
		Scene* m_activeScene;

		std::unique_ptr<Input> m_input;
	};
}


