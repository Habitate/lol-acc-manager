#pragma once

#include <iostream>
#include <string>
#include "riot.h"

class Account{
    public:
        Account(const std::string& id, const std::string& region, const std::string& user, const std::string& pass);
        Account(std::istream& stream);

        friend std::ostream& operator<<(std::ostream& stream, const Account& obj);

        void update(const std::string& api_key);

        const std::string& get_id() const;
        const std::string& get_username() const;
        const std::string& get_password() const;

        void draw_info() const;

    private:
        std::string username;
        std::string password;

        std::string region; 
        
        int winrate;

        SUMMONER_V4 summoner_data;
        LEAGUE_V4 league_data;
};