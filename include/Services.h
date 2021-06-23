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

// boost library help to read JSON from server
namespace pt = boost::property_tree;

/* this class connect a game with firebase serve */
class Services
{
public:
    // constructor & destructor
    Services();
    ~Services();

    // public functions
    bool createUser(User* );
    bool updateUser(User* );
    bool getUser(User*, const std::string );
    bool deleteUser(User*);
    bool resetUser(User*);
    bool getIdOtherUser(User* );
    bool createRace(User* );
    bool getUsers(std::vector<User>&, const std::string );
    void updatePosition(User*, PlayerBase*, std::mutex*, bool* );
    void updateWin(User*, PlayerBase*);
    void getPosition(User*, PlayerBase*, std::mutex*, bool* );


private:
    // private members
    std::stringstream m_stream;
    std::ostringstream m_ostream;
    // private functions
    void buildVecUsers( std::vector<User>&,
                        const std::string,
                        boost::property_tree::ptree const& );
};

