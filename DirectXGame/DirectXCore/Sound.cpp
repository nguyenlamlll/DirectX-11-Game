#include "stdafx.h"
#include "Sound.h"

using namespace DirectXCore;
using namespace DirectX;

Sound::Sound(DirectX::AudioEngine* audioEngine, const wchar_t* fileName)

{
	m_soundEffect = new SoundEffect(audioEngine, fileName);
}


Sound::~Sound()
{
	if (m_soundEffect)
		delete m_soundEffect;
}

void DirectXCore::Sound::Play()
{
	if (m_soundEffect)
	{
		m_soundEffect->Play();
	}
}

void DirectXCore::Sound::Loop()
{
}
