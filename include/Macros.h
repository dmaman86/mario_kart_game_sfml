#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

namespace DimensionWindow
{
    const int WIDTH = 1440;
    const int HEIGHT = 810;
}

// dimension game
namespace DimensionGame
{
    const int WIDTH_G = 400;
    const int HEIGHT_G = 200;
    const int DEF_SIZE = 128;
}

namespace PlayerDefinitions
{
    const auto MAX_SPEED = 15.f ;
    const auto EPSILON_SPEED = 3.f;
    const int SCALE_PLAYER = 3;
}

namespace HttpNetwork
{
    // url path server
    const std::string url = "http://us-central1-fb-api-server-mario.cloudfunctions.net";
    const std::string path_user = "/app/api/users";
    const std::string path_player = "/app/api/player";
    const std::string path_delete = "/app/api/update_to_delete/";
    const std::string path_reset = "/app/api/reset_user/";
    const std::string path_createRace = "/app/api/create_race/";
}

// to read from keyboard
namespace SpecialKeyboard
{
    const int DELETE_KEY = 8;
    const int ENTER_KEY = 13;
    const int ESCAPE_KEY = 27;
    const int MAX = 128;
}

namespace PositionButtons
{
    const sf::IntRect letPlay(0, 250, 414, 64);
    const sf::IntRect settings( 0, 717, 360, 65);
    const sf::IntRect about( 0, 640, 255, 60);
    const sf::IntRect help( 0, 330, 187, 62);
    const sf::IntRect online( 0, 0, 265, 55);
    const sf::IntRect carer( 0, 485, 265, 70);
    const sf::IntRect logo( 0, 410, 250, 63);
    const sf::IntRect back( 0, 563, 180, 63);
    const sf::IntRect newGame( 0, 75, 405, 66);
    const sf::IntRect loadGame( 0, 160, 428, 67);
    const sf::IntRect save( 500, 0, 212, 54);
    const sf::IntRect createGame( 500, 155, 600, 60);
    const sf::IntRect joinGame( 500, 238, 600, 60);
    const sf::IntRect carerTitle( 0, 485, 270, 60);
    const sf::IntRect timeRace( 0, 875, 453, 60);
    const sf::IntRect collectionCoinsRace( 0, 955, 562, 57);
    const sf::IntRect dkRace( 0, 795, 522, 66);
    const sf::IntRect garage( 520, 80, 280, 62);
}

namespace PositionDrive
{
    const sf::IntRect start(62, 0, 33, 30);
    const sf::IntRect select( 95, 0, 33, 30);
}

namespace PositionDrivers
{
    const sf::IntRect bowser( 360, 5, 33, 33);
    const sf::IntRect dk( 360, 45, 33, 33);
    const sf::IntRect mario( 360, 80, 33, 33);
    const sf::IntRect koopa( 360, 115, 33, 33);
    const sf::IntRect luigi( 360, 150, 33, 33);
    const sf::IntRect peach( 360, 190, 33, 33);
    const sf::IntRect toad( 360, 225, 33, 33);
    const sf::IntRect yoshi( 360, 260, 33, 33);
}




namespace Color 
{
    const sf::Color REGULARCOLOR(255, 255, 255, 250);
    const sf::Color TRANSPARENCYCOLOR(255, 255, 255, 120);
    const sf::Color GRAYCOLOR(0, 0, 0, 100);
}
const int SIZETEXT = 50;

const float THICK = 5.f;


