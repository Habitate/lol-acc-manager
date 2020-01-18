#pragma once

#include <array>
#include <windows.h>
#include <algorithm>

class InputHandler{
	public:
        using size_t = std::array<bool, 255>::size_type;

		InputHandler();

		void update();

		bool pressed(const size_t key);
		bool released(const size_t key);
		bool held(const size_t key);

	private:
		std::array<bool, 255> current_state;
		std::array<bool, 255> prev_state;
};