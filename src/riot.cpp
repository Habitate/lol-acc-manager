#include "riot.h"

#include "json.h"
#include <sstream>

using namespace std;

SUMMONER_V4::SUMMONER_V4() : profile_icon_id(), name(), puuid(), summoner_level(), account_id(), id(), revision_date(){}

SUMMONER_V4::SUMMONER_V4(const string& json) : profile_icon_id(stoi(json::parse_for(json, "profileIconId"))),
                                                    name           (json::parse_for(json, "name")),
                                                    puuid          (json::parse_for(json, "puuid")),
                                                    summoner_level (stoi(json::parse_for(json, "summonerLevel"))),
                                                    account_id     (json::parse_for(json, "accountId")),
                                                    id             (json::parse_for(json, "id")),
                                                    revision_date  (json::parse_for(json, "revisionDate")){
           
}


LEAGUE_V4::LEAGUE_V4() : queue_type(), summoner_name(), hot_streak(), wins(), veteran(), losses(), rank(), tier("UNRANKED"), inactive(), fresh_blood(), league_id(), summoner_id(), league_points(){}
    
LEAGUE_V4::LEAGUE_V4(const string& json) : queue_type(json::parse_for(json, "queueType")),
                                                summoner_name(json::parse_for(json, "summonerName")),
                                                hot_streak(),
                                                wins(stoi(json::parse_for(json, "wins"))),
                                                veteran(),
                                                losses(stoi(json::parse_for(json, "losses"))),
                                                rank(json::parse_for(json, "rank")),
                                                tier(json::parse_for(json, "tier")),
                                                inactive(),
                                                fresh_blood(),
                                                league_id(json::parse_for(json, "leagueId")),
                                                summoner_id(json::parse_for(json, "summonerId")),
                                                league_points(stoi(json::parse_for(json, "leaguePoints"))){
    istringstream(json::parse_for(json, "hotStreak"))  >> boolalpha >> hot_streak;
    istringstream(json::parse_for(json, "veteran"))    >> boolalpha >> veteran;
    istringstream(json::parse_for(json, "inactive"))   >> boolalpha >> inactive;
    istringstream(json::parse_for(json, "freshBlood")) >> boolalpha >> fresh_blood;
}

string riot::get_summoner_v4_json(const string& summoner, const string& api_key, const string& platform_routing){
    const string request = "https://" + platform_routing + "/lol/summoner/v4/summoners/by-name/" + summoner + "?api_key=" + api_key;

    return json::recieve_from(request);
}
string riot::get_league_v4_json(const string& encrypted_id, const string& api_key, const string& platform_routing){
    const string request = "https://" + platform_routing + "/lol/league/v4/entries/by-summoner/" + encrypted_id + "?api_key=" + api_key;

    return json::recieve_from(request);
}