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
		if (d3dContext_ == 0)
			return;

		float clearColor[4] = { 0.0f, 0.0f, 0.25f, 1.0f };
		d3dContext_->ClearRenderTargetView(backBufferTarget_, clearColor);

		swapChain_->Present(0, 0);
	}
}
