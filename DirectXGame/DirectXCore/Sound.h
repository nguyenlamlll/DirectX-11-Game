#pragma once

#include <Audio.h>

namespace DirectXCore
{
	class Sound
	{
	public:
		Sound(DirectX::AudioEngine* audioEngine, const wchar_t* fileName);
		~Sound();

		void Play();
		void Loop();

	private:
		DirectX::SoundEffect* m_soundEffect;
		wchar_t m_fileName;
	};
}


