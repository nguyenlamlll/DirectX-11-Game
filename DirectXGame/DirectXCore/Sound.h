#pragma once

#include <Audio.h>
//For reference: https://github.com/Microsoft/DirectXTK/wiki/Creating-and-playing-sounds
//and https://github.com/Microsoft/DirectXTK/wiki/SoundEffect
namespace DirectXCore
{
	class Sound
	{
	public:
		Sound(DirectX::AudioEngine* audioEngine, const wchar_t* fileName);
		~Sound();

		void Play();
		void Play(DirectX::AudioEngine* audioEngine, const wchar_t* fileName);
		void Loop();

	private:
		std::unique_ptr<DirectX::SoundEffect> m_soundEffect;
		std::unique_ptr<DirectX::SoundEffectInstance> m_soundInstance;
		const wchar_t* m_fileName;
	};
}


