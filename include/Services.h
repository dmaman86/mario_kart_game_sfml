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
#include <pthread.h>

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
    bool deleteUser(User*);
    bool resetUser(User*);
    bool getIdOtherUser(User* );
    bool createRace(User* );
    bool getUsers(std::vector<User>&, const std::string );
    void updatePosition(User*, PlayerBase*, std::mutex*, bool* );
    void getPosition(User*, PlayerBase*, std::mutex*, bool* );


private:
    std::stringstream m_stream;
    std::ostringstream m_ostream;

    void buildVecUsers( std::vector<User>&,
                        const std::string,
                        boost::property_tree::ptree const& );
};

