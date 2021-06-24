#pragma once

#include <string>
#include <vector>

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
    const std::vector<int> letPlay = { 0, 250, 414, 64};
    const std::vector<int> settings = { 0, 717, 360, 65};
    const std::vector<int> about = { 0, 640, 255, 60};
    const std::vector<int> help = { 0, 330, 187, 62};
    const std::vector<int> online = { 0, 0, 265, 55};
    const std::vector<int> carer = { 0, 485, 265, 70};
    const std::vector<int> logo = { 0, 410, 250, 63};
    const std::vector<int> back = { 0, 563, 180, 63};
    const std::vector<int> newGame = { 0, 75, 405, 66};
    const std::vector<int> loadGame = { 0, 160, 428, 67};
    const std::vector<int> save = { 500, 0, 212, 54};
    const std::vector<int> createGame = { 500, 155, 600, 60};
    const std::vector<int> joinGame = { 500, 238, 600, 60};
    const std::vector<int> carerTitle = { 0, 485, 270, 60};
    const std::vector<int> timeRace = { 0, 875, 453, 60};
    const std::vector<int> collectionCoinsRace = { 0, 955, 562, 57};
    const std::vector<int> dkRace = { 0, 795, 522, 66};
    const std::vector<int> garage = { 520, 80, 280, 62};
}

namespace PositionDrive
{
    const std::vector<int> start = { 62, 0, 33, 30};
    const std::vector<int> select = { 95, 0, 33, 30};
}

namespace PositionDrivers
{
    const std::vector<int> bowser = { 360, 5, 33, 33};
    const std::vector<int> dk = { 360, 45, 33, 33};
    const std::vector<int> mario = { 360, 80, 33, 33};
    const std::vector<int> koopa = { 360, 115, 33, 33};
    const std::vector<int> luigi = { 360, 150, 33, 33};
    const std::vector<int> peach = { 360, 190, 33, 33};
    const std::vector<int> toad = { 360, 225, 33, 33};
    const std::vector<int> yoshi = { 360, 260, 33, 33};
}

