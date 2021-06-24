#pragma once

#include <SFML/Graphics.hpp>
#include <string>

const sf::Rect SKY_LINE_RECT(0, 0, 300, 32);

const sf::Vector2f SKY_LINE_SCALE(4, 4);
const sf::Vector2f SPEED_SCREEN_SCALE(0.65f, 0.5f);
const sf::Vector2f MODE7_SCALE(2, 2);
const sf::Vector2f SPEED_SCREEN_POS(0, 80);
const sf::Vector2f LAP_POS(360, 50);
const sf::Vector2i OBJ_SIZE(17, 3);

const auto HALF = 0.5f;
const auto FIFTY = 50.f;
const auto THIRTY = 30.f;
const auto MAX_OBJ_DIS = 25.f;
const auto HALF_DIS = 12.5f;
const auto TEN_F = 10.f;
const auto SIXTY = 60.f;
const auto CAMERA_HEIGHT = -17.f;
const auto SCREEN_TO_2D = 8.f;
const auto DIS_TO_PLAYER = FIFTY;

const auto TEN = 10;
const auto ONE = 1;
const auto TWO = 2;
const auto CHATACTER_SIZE = 50;
const auto CHAR_TO_INT = 48;
const auto MIDDLE_SKY_BACK = 485;
const auto MIDDLE_SKY_FRONT = 1040;
const auto SIZE_SKY_BACK = 1536;
const auto SIZE_SKY_FRONT = 2560;
const auto SPEED_SCREEN_SIZE = 5;

const auto SKY_B_PNG = "_sky_back.png";
const auto SKY_F_PNG = "_sky_front.png";
const auto TXT = ".txt";
const auto SCORE_TXT = "_scores.txt";

const auto OBJ_TXT = "_objects.txt";
