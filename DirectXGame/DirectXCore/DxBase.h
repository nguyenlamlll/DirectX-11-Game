#pragma once
namespace DirectXCore 
{
	class DxBase
	{
	public:
		DxBase();
		virtual ~DxBase();

		bool Initialize(HINSTANCE hInstance, HWND hwnd);
		void Shutdown();

		virtual bool LoadContent();
		virtual void UnloadContent();

		virtual void Update(float dt) = 0;
		virtual void Render() = 0;

	protected:
		HINSTANCE hInstance_;
		HWND hwnd_;

		D3D_DRIVER_TYPE driverType_;
		D3D_FEATURE_LEVEL featureLevel_;

		ID3D11Device* d3dDevice_;
		ID3D11DeviceContext* d3dContext_;
		IDXGISwapChain* swapChain_;
		ID3D11RenderTargetView* backBufferTarget_;
	};
}


