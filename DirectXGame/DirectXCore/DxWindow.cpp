#include "stdafx.h"
#include "DxWindow.h"

namespace DirectXCore
{
	DxWindow::DxWindow()
	{
	}


	DxWindow::~DxWindow()
	{
	}


	bool DxWindow::LoadContent()
	{
		return true;
	}


	void DxWindow::UnloadContent()
	{

	}


	void DxWindow::Update(float dt)
	{

	}


	void DxWindow::Render()
	{
		if (!m_d3dContext.Get())
			return;
		
		float clearColor[4] = { 0.0f, 0.0f, 0.25f, 1.0f };
		m_d3dContext.Get()->ClearRenderTargetView(m_backBufferTarget.Get(), clearColor);

		m_swapChain.Get()->Present(0, 0);
	}
}
