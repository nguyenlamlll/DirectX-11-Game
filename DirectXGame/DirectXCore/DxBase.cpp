#include "stdafx.h"
#include "DxBase.h"

using Microsoft::WRL::ComPtr;
using namespace DirectXCore;
using namespace DirectX;

DxBase::DxBase() noexcept(false)
{
	m_deviceResources = std::make_unique<DeviceResources>();
	m_deviceResources->RegisterDeviceNotify(this);

	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | AudioEngine_Debug;
#endif
	m_audioEngine = std::make_shared<AudioEngine>(eflags);
}

DirectXCore::DxBase::~DxBase()
{
	if (m_audioEngine)
	{
		m_audioEngine->Suspend();
	}
}

// Initialize the Direct3D resources required to run.
void DxBase::Initialize(HWND window, int width, int height)
{
	m_deviceResources->SetWindow(window, width, height);

	m_deviceResources->CreateDeviceResources();
	CreateDeviceDependentResources();

	m_deviceResources->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
}

#pragma region Frame Update
// Executes the basic game loop.
void DxBase::Tick()
{
	m_timer.Tick([&]()
	{
		Update(m_timer);
	});

	Render();
}

// Updates the world.
void DxBase::Update(StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	// TODO: Add your game logic here.
	animation->Update(elapsedTime);

	if (!m_audioEngine->Update())
	{
		// ...
	}

	elapsedTime;
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void DxBase::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	m_deviceResources->PIXBeginEvent(L"Render");
	auto context = m_deviceResources->GetD3DDeviceContext();

	// TODO: Add your rendering code here.
	//sprite->RenderSprite();
	animation->Render();
	context;

	m_deviceResources->PIXEndEvent();

	// Show the new frame.
	m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void DxBase::Clear()
{
	m_deviceResources->PIXBeginEvent(L"Clear");

	// Clear the views.
	auto context = m_deviceResources->GetD3DDeviceContext();
	auto renderTarget = m_deviceResources->GetRenderTargetView();
	auto depthStencil = m_deviceResources->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, DirectX::Colors::CornflowerBlue);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// Set the viewport.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void DxBase::OnActivated()
{
	// TODO: Game is becoming active window.
}

void DxBase::OnDeactivated()
{
	// TODO: Game is becoming background window.
}

void DxBase::OnSuspending()
{
	// TODO: Game is being power-suspended (or minimized).

	m_audioEngine->Suspend();
}

void DxBase::OnResuming()
{
	m_timer.ResetElapsedTime();

	// TODO: Game is being power-resumed (or returning from minimize).

	m_audioEngine->Resume();
}

void DxBase::OnWindowMoved()
{
	auto r = m_deviceResources->GetOutputSize();
	m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void DxBase::OnWindowSizeChanged(int width, int height)
{
	if (!m_deviceResources->WindowSizeChanged(width, height))
		return;

	CreateWindowSizeDependentResources();

	// TODO: Game window is being resized.
}

// Properties
void DxBase::GetDefaultSize(int& width, int& height) const
{
	// TODO: Change to desired default window size (note minimum size is 320x200).
	width = 1024;
	height = 768;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void DxBase::CreateDeviceDependentResources()
{
	auto device = m_deviceResources->GetD3DDevice();

	// TODO: Initialize device dependent objects here (independent of window size).
	//
	device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void DxBase::CreateWindowSizeDependentResources()
{
	// TODO: Initialize windows-size dependent objects here.
}

// Load every sound we're asked to.
void DirectXCore::DxBase::CreateSoundAndMusic(const wchar_t* soundFileName)
{
	auto sound = new Sound(m_audioEngine.get(), soundFileName);
	sound->Play();
}


void DirectXCore::DxBase::CreateSprite(const wchar_t * spriteName)
{
	//sprite = new Sprite(m_deviceResources.get(), L"scott.png");
	animation = new Animation(2, 8, new Sprite(m_deviceResources.get(), L"scott.png"), 0.1f);
}


void DxBase::OnDeviceLost()
{
	// TODO: Add Direct3D resource cleanup here.
	sprite->Reset();
}

void DxBase::OnDeviceRestored()
{
	CreateDeviceDependentResources();

	CreateWindowSizeDependentResources();
}
#pragma endregion