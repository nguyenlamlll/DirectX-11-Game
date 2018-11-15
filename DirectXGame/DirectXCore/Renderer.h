#pragma once
#include "Component.h"
#include <CommonStates.h>
#include "DeviceResources.h"

using namespace DirectX;
namespace DirectXCore
{
	class Sprite;
	class Renderer : public Component
	{
	public:
		Renderer();
		Renderer(DeviceResources* _deviceResource, Sprite* _sprite);
		Renderer(DeviceResources* _deviceResource, const wchar_t* _charPath);
		Renderer(DeviceResources* _deviceResource, const wchar_t* _charPath,Sprite* _sprite);
		void Render() ;
		void Render(DirectX::SimpleMath::Vector3 _newPos);
		void Reset();
		void SetRECT(RECT _newRECT);
		RECT* GetRECT() { return spriterect; }
		~Renderer();
	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
		std::unique_ptr<CommonStates> m_states;
		std::unique_ptr<SpriteBatch> m_spriteBatch;
		SimpleMath::Vector3 pivot;
		RECT *spriterect;
		Sprite* sprite;
	};
}
