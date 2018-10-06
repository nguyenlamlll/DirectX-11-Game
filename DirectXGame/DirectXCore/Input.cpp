#include "stdafx.h"
#include "Input.h"

using namespace DirectXCore;

const Input::KeyMapping Input::sKeyMap{
	{ "A", 0x41 },
	{ "B", 0x42 },
	{ "C", 0x43 },
	{ "D", 0x44 },
	{ "E", 0x45 },
	{ "F", 0x46 },
	{ "G", 0x47 },
	{ "H", 0x48 },
	{ "I", 0x49 },
	{ "J", 0x4A },
	{ "K", 0x4B },
	{ "L", 0x4C },
	{ "M", 0x4D },
	{ "N", 0x4E },
	{ "O", 0x4F },
	{ "P", 0x50 },
	{ "Q", 0x51 },
	{ "R", 0x52 },
	{ "S", 0x53 },
	{ "T", 0x54 },
	{ "U", 0x55 },
	{ "V", 0x56 },
	{ "W", 0x57 },
	{ "X", 0x58 },
	{ "Y", 0x59 },
	{ "Z", 0x5A },

	{"Left Arrow", 0x25},
	{"Up Arrow", 0x26},
	{"Right Arrow", 0x27},
	{"Down Arrow", 0x28}
};

Input::Input()
{

}


Input::~Input()
{
}

void DirectXCore::Input::KeyDown(KeyCode key)
{

}

void DirectXCore::Input::KeyUp(KeyCode key)
{
}

bool DirectXCore::Input::IsKeyDown(KeyCode key) const
{
	auto state = m_keyStates[key];
	return state;
}

bool DirectXCore::Input::IsKeyUp(KeyCode key) const
{
	return false;
}
