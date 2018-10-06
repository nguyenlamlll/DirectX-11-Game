#pragma once
#include <unordered_map>
using KeyCode = unsigned int;
#define NUMBER_OF_KEYS 254 // From 0x01 to 0xFE
namespace DirectXCore
{
	class Input
	{
		using KeyMapping = std::unordered_map<const char*, KeyCode>;
		static const KeyMapping sKeyMap;

	public:
		Input();
		~Input();

		void KeyDown(KeyCode);
		void KeyUp(KeyCode);

		bool IsKeyDown(KeyCode) const;;
		bool IsKeyDown(const char*) const;
		bool IsKeyUp(KeyCode) const;


	private:
		bool m_keyStates[NUMBER_OF_KEYS];
	};
}


