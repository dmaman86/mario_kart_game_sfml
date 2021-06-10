#pragma once

#include <SFML/Network.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <sstream>
#include "Macros.h"
#include "UserNetwork.h"

class ServiceThread : public sf::Thread
{
public:
    ServiceThread();
    ~ServiceThread();

private:
    void updatePosition( std::string, float, float );
    void getPosition( std::string, float&, float& );
};