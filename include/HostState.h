#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <cmath>
#include <vector>

#include "State.h"
#include "MarioKart.h"
#include "Macros.h"
#include "UserNetwork.h"

namespace pt = boost::property_tree;

class HostState : public State
{
public:
    HostState(MarioKart::GameDataRef&);
    ~HostState() = default;

    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override;
    void Draw() override;
private:
    using Pair = std::pair<std::string, std::pair<sf::RectangleShape, bool >>;
    using VectorMaps = std::vector< Pair >;
    using VectorTextures = std::vector< sf::Texture >;

    sf::Sprite m_background;
    MarioKart::GameDataRef m_data;
    sf::Sprite m_back;
    sf::Text m_title;
    sf::Text m_createGame;
    sf::Vector2u m_windowSize;
    VectorMaps m_maps;
    VectorTextures m_textures;

    sf::Http::Request m_request_post;
    sf::Http::Request m_request_put;
    bool m_validConnection;
    bool m_backMenu;
    bool m_createPressed;
    bool m_nextState;
    bool m_createRoom;
    float m_effectTime;

    void centerOrigin(sf::Text&);
    void initVectorMaps();
    bool createUser();
    bool updateUser();
};
