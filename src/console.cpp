#include "console.h"

#include <sstream>
#include <iostream>
#include "color.h"

using namespace std;

void con::set_title(const string& title){
    ostringstream stream;
    stream << "title " << title;

    system(stream.str().c_str());
}

void con::set_cursor_pos(const COORD position){
    SetConsoleCursorPosition(con::console, position);
}

void con::set_dimensions(const int width, const int height){
    stringstream stream;
    stream << "mode con:cols=" << width << "lines=" << height;

    system(stream.str().c_str());
}

void con::show_cursor(const bool show){
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(con::console, &cursorInfo);

    cursorInfo.bVisible = show;
    SetConsoleCursorInfo(con::console, &cursorInfo);
}

void con::draw_text(COORD pos, const string& text, uint8_t color){
    con::set_cursor_pos(pos);
    cout << C(color) << text << C();
}

void con::draw_vertical_line(const COORD starting_pos, const short length, const char ch){
    for(short i = 0; i < length; ++i){
        con::set_cursor_pos({starting_pos.X, static_cast<short>(starting_pos.Y + i)});
        cout << ch;
    }
}