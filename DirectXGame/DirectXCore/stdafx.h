// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers



// TODO: reference additional headers your program requires here

#include <d3d11_1.h>
#pragma comment(lib,"d3d11.lib")
#include <wrl.h>

#if defined(NTDDI_WIN10_RS2)
#include <dxgi1_6.h>
#else
#include <dxgi1_5.h>
#endif
#pragma comment(lib,"dxgi.lib")

#ifdef _DEBUG
#include <dxgidebug.h>
#pragma comment(lib,"dxguid.lib")
#endif

#include <memory>
#include <algorithm>
#include <stdexcept>

#include <DirectXMath.h>
#include <DirectXColors.h>
#include <SpriteBatch.h>
#include <SimpleMath.h>
#include <WICTextureLoader.h>
#include <vector>

#include <DirectXCollision.h>
#include <VertexTypes.h>
#include <Effects.h>
#include <PrimitiveBatch.h>

#include "MapReader/tmx.h.in"

#ifdef _DEBUG
#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define new new
#endif

namespace DirectXCore
{
	// Helper class for COM exceptions
	class com_exception : public std::exception
	{
	public:
		com_exception(HRESULT hr) : result(hr) {}

		virtual const char* what() const override
		{
			static char s_str[64] = {};
			sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
			return s_str;
		}

	private:
		HRESULT result;
	};

	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			// Set a breakpoint on this line to catch DirectX API errors
			throw std::exception();
		}
	}
}