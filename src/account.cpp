#include "account.h"

#include "console.h"
#include <algorithm>
#include <cctype>

using namespace std;

Account::Account(const string& id, const string& region, const string& user, const string& pass) : 
username(user), password(pass), region(region), winrate(), summoner_data(), league_data(){
    summoner_data.name = id;
}

Account::Account(istream& stream) :
username(), password(), region(), winrate(), summoner_data(), league_data(){
    stream >> region;
    stream.ignore();

    getline(stream, summoner_data.name);
    getline(stream, username);
    getline(stream, password);

    username.erase(remove_if(begin(username), end(username), static_cast<int(*)(int)>(isspace)), end(username));
    password.erase(remove_if(begin(password), end(password), static_cast<int(*)(int)>(isspace)), end(password));
}

ostream& operator<<(ostream& stream, const Account& obj){
    stream << obj.summoner_data.name;

    return stream;
}

void Account::update(const string& api_key){
    const string& routing = riot::routing_map.at(region);

    summoner_data = SUMMONER_V4(riot::get_summoner_v4_json(summoner_data.name, api_key, routing));

    if(string league_json = riot::get_league_v4_json(summoner_data.id, api_key, routing); league_json.size() != 2){
        league_data = LEAGUE_V4(league_json);
    }
    else{
        return;
    }

    winrate = ((double)league_data.wins / (league_data.wins + league_data.losses)) * 100;
}

const string& Account::get_id() const{
    return summoner_data.name;
}
const string& Account::get_username() const{
    return username;
}
const string& Account::get_password() const{
    return password;
}

void Account::draw_info() const{
    const uint8_t rank_color = riot::rank_colors.find(league_data.tier)->second;
    const uint8_t winrate_color = winrate > 60 ? riot::etc_colors::wr_high : riot::etc_colors::wr_normal;

    con::set_cursor_pos({24, 0});
    cout << summoner_data.name;

    con::set_cursor_pos({24, 2});
    cout << region;

    con::set_cursor_pos({24, 3});
    cout  << C(rank_color) << league_data.tier << ' ' << league_data.rank << ' ' << league_data.league_points << " LP" << C();

    con::set_cursor_pos({24, 4});
    cout << C(riot::etc_colors::wins) << "Wins: " << league_data.wins << C();

    con::set_cursor_pos({24, 5});
    cout << C(riot::etc_colors::losses) << "Losses: " << league_data.losses << C();

    con::set_cursor_pos({24, 6});
    cout << "WR: " << C(winrate_color) << winrate << '%' << C();

    con::set_cursor_pos({24, 8});
    cout << "Total games: " << league_data.wins + league_data.losses;
}