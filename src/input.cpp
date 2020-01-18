#include "input.h"

InputHandler::InputHandler() : current_state(), prev_state(){
	update();
}

void InputHandler::update(){
	std::copy(std::begin(current_state), std::end(current_state), std::begin(prev_state));

    for(size_t i = 0; i < 255; ++i){
		current_state[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

bool InputHandler::pressed(const size_t key){
	return current_state[key] && !prev_state[key];
}
bool InputHandler::released(const size_t key){
	return !current_state[key] && prev_state[key];
}
bool InputHandler::held(const size_t key){
	return current_state[key] && prev_state[key];
}