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

#include "Macros.h"
#include "UserNetwork.h"
#include "PlayerBase.h"

namespace pt = boost::property_tree;

class Services
{
public:
    Services();
    ~Services();

    bool createUser( UserNetwork* );
    bool updateUser( UserNetwork* );
    bool getUser( UserNetwork*, const std::string );
    bool deleteUser( UserNetwork* );
    bool getIdOtherUser(UserNetwork* );
    bool createRace( UserNetwork* );
    bool getUsers( std::vector<UserNetwork>&, const std::string );
    bool updatePosition( std::string, PlayerBase );
    bool getPosition( std::string, PlayerBase* );


private:
    sf::Http m_http;
    sf::Http::Request m_request_post;
    sf::Http::Request m_request_get;
    sf::Http::Request m_request_put;
    sf::Http::Request m_request_del;
    sf::Http::Response m_response;
    std::stringstream m_stream;
    std::ostringstream m_ostream;

    void buildVecUsers( std::vector<UserNetwork>&,
                        const std::string,
                        boost::property_tree::ptree const& );
};

