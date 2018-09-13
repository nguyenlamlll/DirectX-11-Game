#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <Audio.h>

namespace DirectXCore 
{
	class DxBase : public IDeviceNotify
	{
	public:
		DxBase() noexcept(false);
		~DxBase();

		// Initialization and management
		void Initialize(HWND window, int width, int height);

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

		std::unique_ptr<DirectX::AudioEngine> m_audioEngine;

		// Rendering loop timer.
		StepTimer m_timer;
	};
}


