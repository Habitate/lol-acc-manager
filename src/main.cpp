#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <array>
#include <functional>
#include <thread>
#include <chrono>
#include <sstream>
#include <iterator>
#include <map>

#include <curlpp/cURLpp.hpp>

#include "json.h"
#include "color.h"
#include "input.h"
#include "menu.h"
#include "riot.h"
#include "account.h"
#include "console.h"

#include <windows.h>

using namespace std;

const chrono::milliseconds PASTE_TIMEOUT{150};
const string API_FILE{"apikey.txt"};

void to_clipboard(const std::string& string){
	OpenClipboard(0);
	EmptyClipboard();

    HANDLE mem = GlobalLock(GlobalAlloc(GMEM_MOVEABLE, string.size() + 1));
	memcpy(mem, string.c_str(), string.size() + 1);

	GlobalUnlock(mem);
	SetClipboardData(CF_TEXT, mem);

	GlobalFree(mem);
	
	CloseClipboard();
}

vector<Account> parse_stream(istream&& stream){
    vector<Account> accounts;

    //? Extract accounts
    while(stream.peek() != EOF){
        //* Clear the stream of space like characters
        while(isspace(stream.peek())){
            stream.ignore();
        }

        accounts.emplace_back(Account(stream));
    }

    return accounts;
}

string read_api_key(const string& file_name){
    ifstream api_file("apikey.txt");

    return *istream_iterator<string>{api_file};
}

void assert_api_status(const string& api_key){
    const string url = "https://euw1.api.riotgames.com/lol/status/v3/shard-data?api_key=" + api_key;

    cout << "Checking api status...\n";

    if(json::parse_for(json::recieve_from(url), "status_code") == "403"){
        cout << "API Key has expired!\n";
        system("pause");
        terminate();
    }
}

int main(){
    cURLpp::initialize();

    vector<Account> accounts = parse_stream(ifstream{"accounts.txt"});
    InputHandler input;

    //* Init interface
    system("cls");
    con::show_cursor(false);
    con::set_dimensions(44, accounts.size() > 5 ? accounts.size() + 2 : 9);
    con::set_title("Found " + to_string(accounts.size()) + " accounts!");
    
    //* Get the api key and assert it's correctness
    const string api_key = read_api_key(API_FILE);
    assert_api_status(api_key);
    
    //* Retrieve the data about all the accounts in separate threads
    cout << "Retrieving data..."; 
    vector<thread> updater_threads(accounts.size());
    transform(begin(accounts), end(accounts), begin(updater_threads), [&api_key](auto& account){ return thread{&Account::update, &account, api_key}; });
    for_each(begin(updater_threads), end(updater_threads), [](auto& t){ t.join(); });
 
    //* Create a menu with the summoner names
    Menu menu(begin(accounts), end(accounts), [](const auto& acc){ return acc.get_id(); });

    const char vertical_line = 179;
    const short line_length = accounts.size() < 9 ? 9 : accounts.size();
    const COORD line_starting_point = {22, 0};

    const COORD last_row_pos = {0, static_cast<short>(accounts.size() > 5 ? accounts.size() + 1 : 8)};

    while(true){
        system("cls");

        cout << menu;
        con::draw_vertical_line(line_starting_point, line_length, vertical_line);

        const Account& selected_acc = accounts[menu.get_selection()];
        selected_acc.draw_info();

        to_clipboard(selected_acc.get_username());
        con::draw_text(last_row_pos, "Copied username!", C::GREEN);

        while(true){
            input.update();

            //* Move menu up
            if(input.pressed(VK_DOWN)){
                menu.mv_down();
                break;
            }
            //* Move menu down
            if(input.pressed(VK_UP)){
                menu.mv_up();
                break;
            }
            //* Exit
            if(input.pressed(VK_ESCAPE)){
                return 0;
            }
            //* Re-copy the username
            if(input.pressed('R')){
                to_clipboard(selected_acc.get_username());
                con::draw_text(last_row_pos, "Copied username!", C::GREEN);
            }
            //* Copy the password
            if(input.held(VK_CONTROL) && input.pressed('V')){
                con::draw_text(last_row_pos, "Copied password!", C::RED);

                this_thread::sleep_for(PASTE_TIMEOUT);
                to_clipboard(selected_acc.get_password());
            }
        }
    }

    return 0;
}