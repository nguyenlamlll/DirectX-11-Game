#include "stdafx.h"
#include "Sound.h"

using namespace DirectXCore;
using namespace DirectX;

Sound::Sound(DirectX::AudioEngine* audioEngine, const wchar_t* fileName)

{
	m_soundEffect = std::make_unique<SoundEffect>(audioEngine, fileName);
}


Sound::~Sound()
{
	m_soundInstance->Pause();
	//m_soundEffect.reset();
}

void DirectXCore::Sound::Play()
{
	if (m_soundEffect)
	{
		m_soundInstance = m_soundEffect->CreateInstance();
		m_soundInstance->Play();
	}
}

void DirectXCore::Sound::Play(DirectX::AudioEngine* audioEngine, const wchar_t * fileName)
{
	if (m_fileName != fileName) m_fileName = fileName;
	m_soundEffect = std::make_unique<SoundEffect>(audioEngine, fileName);
	m_soundInstance = m_soundEffect->CreateInstance();
	m_soundInstance->Play();
}

void DirectXCore::Sound::Loop()
{
}

