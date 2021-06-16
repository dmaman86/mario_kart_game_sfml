#pragma once

#include <SFML/Network.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

#include "Macros.h"
#include "User.h"
#include "PlayerBase.h"

namespace pt = boost::property_tree;

class Services
{
public:
    Services();
    ~Services();

    bool createUser(User* );
    bool updateUser(User* );
    bool getUser(User*, const std::string );
    bool deleteUser(User* );
    bool getIdOtherUser(User* );
    bool createRace(User* );
    bool getUsers(std::vector<User>&, const std::string );
    void updatePosition(User*, PlayerBase*, std::mutex* );
    void getPosition(User*, PlayerBase*, std::mutex* );


private:
    sf::Http m_http;
    sf::Http::Request m_request_post;
    sf::Http::Request m_request_get;
    sf::Http::Request m_request_put;
    sf::Http::Request m_request_del;
    sf::Http::Response m_response;
    std::stringstream m_stream;
    std::ostringstream m_ostream;

    void buildVecUsers( std::vector<User>&,
                        const std::string,
                        boost::property_tree::ptree const& );
};

