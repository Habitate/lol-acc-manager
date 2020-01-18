#pragma once

#include "color.h"
#include "windows.h"

namespace con{
    const HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    void set_title(const std::string& title);
    void set_cursor_pos(const COORD position);

    void set_dimensions(const int width, const int height);

    void show_cursor(const bool show);
    void draw_text(COORD pos, const std::string& text, uint8_t color = C::DEFAULT);

    void draw_vertical_line(const COORD starting_pos, const short length, const char ch);
}