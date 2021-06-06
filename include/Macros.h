#pragma once

#include <string>


const int WITDH = 1444;
const int HIGHT = 812;

const int WITDH_G = 1024;
const int HIGHT_G = 512;

const int ROADW = 2000;
const int SEGMENT_LENGTH = 200; 
const float CAMERA_DEPTH = 0.84;
const float MAX_SPEED = 15 ;
const float EPSILON_SPEED = 1.5;

const int MAPSIZE = 1024;
const int PIPE = 7;

namespace HttpNetwork
{
    const std::string url = "http://us-central1-fb-api-server-mario.cloudfunctions.net";
    const std::string url_local = "http://localhost:5000/fb-api-server-mario/us-central1/app";

    const std::string path = "/app/api/users";
}

namespace SpecialKeyboard
{
    const int DELETE_KEY = 8;
    const int ENTER_KEY = 13;
    const int ESCAPE_KEY = 27;
    const int MAX = 128;
}