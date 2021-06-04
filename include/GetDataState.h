#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "State.h"
#include "MarioKart.h"
#include "Macros.h"
#include <cmath>
#include <vector>
#include <map>

namespace pt = boost::property_tree;

class GetDataState : public State
{
public:
    GetDataState(MarioKart::GameDataRef);
    ~GetDataState() = default;

    void Init() override;
    void HandleEvent(const sf::Event&) override;
    void Update(float) override;
    void Draw() override;
private:
    sf::Sprite m_background;
    MarioKart::GameDataRef m_data;
    using Pair = std::pair< std::string, sf::Sprite>;

    sf::String m_playerInput;
    sf::Sprite m_back;
    sf::Text m_playerText;
    sf::Text m_message;
    sf::Text m_save;
    std::vector< Pair > m_drivers;

    const int m_limit = 15;
    std::string* m_name;
    bool m_save_data = false;
    sf::Http::Request m_request_post;
    bool m_validConnection;
    bool m_backMenu;

    void centerOrigin(sf::Text&);
    void inputLogic(int charTyped);
    void deleteLastChar();
    void saveUser();
    void initVectorSprites(const sf::Vector2u&);
};
