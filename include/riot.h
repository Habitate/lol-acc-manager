#pragma once

#include <string>
#include <map>

struct SUMMONER_V4{
    SUMMONER_V4();
    SUMMONER_V4(const std::string& json);

    int profile_icon_id;
    std::string name;
    std::string puuid;
    int summoner_level;
    std::string account_id;
    std::string id;
    std::string revision_date;
};

struct LEAGUE_V4{
    LEAGUE_V4();
    LEAGUE_V4(const std::string& json);

    std::string queue_type;
    std::string summoner_name;
    bool hot_streak;
    int wins;
    bool veteran;
    int losses;
    std::string rank;
    std::string tier;
    bool inactive;
    bool fresh_blood;
    std::string league_id;
    std::string summoner_id;
    int league_points;
};

namespace riot{
    enum etc_colors : uint8_t{
        wins = 3,
        losses = 12,
        wr_normal = 7,
        wr_high = 4
    };

    const std::map<std::string, uint8_t> rank_colors{
        {"UNKNOWN"    , 95},
        {"UNRANKED"   , 7 },
        {"IRON"       , 7 },
        {"BRONZE"     , 6 },
        {"SILVER"     , 8 },
        {"GOLD"       , 14},
        {"PLATINUM"   , 11},
        {"DIAMOND"    , 3 },
        {"MASTERS"    , 13},
        {"GRANDMASTER", 2 },
        {"CHALLANGER" , 12} 
    };

    const std::map<std::string, std::string> routing_map{
        {"BR"  , "br1.api.riotgames.com" },
        {"EUNE", "eun1.api.riotgames.com"},
        {"EUW" , "euw1.api.riotgames.com"},
        {"JP"  , "jp1.api.riotgames.com" },
        {"KR"  , "kr.api.riotgames.com"  },
        {"LA1" , "la1.api.riotgames.com" },
        {"LA2" , "la2.api.riotgames.com" },
        {"NA"  , "na1.api.riotgames.com" },
        {"OC"  , "oc1.api.riotgames.com" },
        {"TR"  , "tr1.api.riotgames.com" },
        {"RU"  , "ru.api.riotgames.com"  }
    };

    std::string get_summoner_v4_json(const std::string& summoner, const std::string& api_key, const std::string& platform_routing);
    std::string get_league_v4_json(const std::string& encrypted_id, const std::string& api_key, const std::string& platform_routing);
}