#include "HostState.h"
#include "Pictures.h"
#include "Fonts.h"
#include "OnlineRace.h"
#include "CareerMenu.h"
#include <iostream>
#include <thread>
#include <chrono>


HostState::HostState(MarioKart::GameDataRef & data): m_data( data ),
                                                     m_background(),
                                                     m_selected(false),
                                                     m_maps(3),
                                                     m_nextState(false),
                                                     m_effectTime(0.0f),
                                                     m_createRoom(false),
                                                     m_pressEnter(false),
                                                     m_errorShow(false),
                                                     m_back_state(),
                                                     m_type_info()
{
    createMaps(m_maps);
}

HostState::HostState(MarioKart::GameDataRef & data, const std::string& state): m_data( data ),
                                                                    m_background(),
                                                                    m_selected(false),
                                                                    m_maps(3),
                                                                    m_nextState(false),
                                                                    m_effectTime(0.0f),
                                                                    m_createRoom(false),
                                                                    m_pressEnter(false),
                                                                    m_errorShow(false),
                                                                    m_back_state(),
                                                                    m_type_info(state)
{
    createMaps(m_maps);
}

void HostState::Init()
{
    sf::Vector2u textureSize;
    m_windowSize = m_data->window->getSize();
    textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();

    m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_background.setScale((float)m_windowSize.x / textureSize.x,
                          (float)m_windowSize.y / textureSize.y);

    m_back = std::make_shared<Button>(Pictures::MenuButtons1);
    m_back->setTextureInRect(0, 563, 180, 63);
    m_back->setCallback([this](){
        m_data->stateStack.RemoveState();
    });

    initTitlesTexts();
    initErrorsTexts();
}

void HostState::HandleEvent(const sf::Event & event)
{
    if(sf::Event::MouseButtonPressed == event.type)
    {
        auto location = m_data->window->mapPixelToCoords(
                {event.mouseButton.x, event.mouseButton.y});

        if (auto res = m_back->validGlobalBound(location); res)
            m_back->updateIfSelected(res);
        else
        {
            for( auto & map : m_maps )
            {
                if(map->m_rect.getGlobalBounds().contains(location))
                {
                    m_data->user.setMapGame(map->map_name);
                    map->selected = !map->selected;
                    break;
                }
            }
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_selected)
        m_pressEnter = true;
}

void HostState::Update(float dt)
{
    for( auto & map : m_maps )
    {
        if(map->selected)
            m_selected = true;
    }
    if(m_back->getIfSelected())
        m_back->initCallback();
    if(m_selected)
    {
        m_effectTime += (float)dt;
        if(m_effectTime >= 0.5f)
        {
            m_selected = !m_selected;
            m_effectTime = 0.0f;
        }
    }
    if(m_pressEnter && m_data->user.getOnline())
    {
        if(m_data->user.getId().size() > 0)
            m_createRoom = m_data->services.updateUser(&m_data->user);
        else
            m_createRoom = m_data->services.createUser(&m_data->user);

        if(!m_createRoom)
            m_errorShow = true;
    }
    if(m_pressEnter && !m_data->user.getOnline())
    {
        if(m_type_info == "CoinRace")
            m_data->stateStack.AddState(StateStack::StateRef( new CoinRace(m_data)), false);
        else if(m_type_info == "DriftKingRace")
            m_data->stateStack.AddState(StateStack::StateRef( new DriftKingRace(m_data)), false);
        else if(m_type_info == "TimeRace")
            m_data->stateStack.AddState(StateStack::StateRef( new TimeRace(m_data)), false);
    }
    if(m_createRoom)
    {
        while(m_data->user.getOtherId().size() < 1 )
        {
            if(!m_data->services.getIdOtherUser(&m_data->user))
            {
                std::cout << "something wrong in host state" << std::endl;
                m_errorShow = true;
                break;
            }
            else if( m_data->user.getOtherId().size() > 1 )
            {
                m_data->stateStack.AddState(StateStack::StateRef( new OnlineRace(m_data)), false);
                break;
            }
        }
    }
}

void HostState::Draw()
{
    sf::RenderWindow& window = *m_data->window;

    window.draw(m_background);
    window.draw(*m_back.get());
    window.draw(m_title);

    if(!m_errorShow)
    {
        for(auto map : m_maps)
            window.draw(map->m_rect);

        if(m_selected)
            window.draw(m_createGame);
    }
    if(m_errorShow)
        window.draw(m_error);
}

void HostState::Resume()
{
    m_validConnection = false;
    m_selected = false;
    m_nextState = false;
    m_createRoom = false;
    m_pressEnter = false;
    for(auto& map : m_maps)
        map->selected = false;
    if(m_data->user.getId().size() > 1)
        m_data->services.deleteUser(&m_data->user);
}

void HostState::initTitlesTexts()
{
    m_title.setFont(Fonts::instance().getFont());
    m_title.setString("Select Map");
    m_title.setFillColor(sf::Color(76, 0, 153));
    m_title.setCharacterSize(100);
    m_title.setPosition((m_windowSize.x / 2) - 500, 100);

    m_createGame.setFont(Fonts::instance().getFont());
    m_createGame.setString("Press Enter to continue");
    m_createGame.setFillColor(sf::Color(76, 0, 153));
    m_createGame.setCharacterSize(60);
    m_createGame.setOrigin(m_createGame.getLocalBounds().width / 2,
                           m_createGame.getLocalBounds().height / 2);
    m_createGame.setPosition(sf::Vector2f(m_windowSize.x * 0.5f,
                                          (m_windowSize.y / 2) + 300));
    m_createGame.setOutlineColor(sf::Color::White);
    m_createGame.setOutlineThickness(5.f);
}

void HostState::initErrorsTexts()
{
    m_error.setFont(Fonts::instance().getFont());
    m_error.setString("Error to connect with serve.");
    m_error.setFillColor(sf::Color::Red);
    m_error.setCharacterSize(70);
    m_error.setOrigin(m_error.getLocalBounds().width / 2,
                      m_error.getLocalBounds().height / 2);
    m_error.setPosition(sf::Vector2f(m_windowSize.x / 2,
                                     m_windowSize.y / 2));

    m_back_state.setFont(Fonts::instance().getFont());
    m_back_state.setString("Sorry, please try again later.");
    m_back_state.setFillColor(sf::Color::Red);
    m_back_state.setCharacterSize(70);
    m_back_state.setOrigin(m_error.getLocalBounds().width / 2,
                           m_error.getLocalBounds().height / 2);
    m_back_state.setPosition(sf::Vector2f(m_windowSize.x / 2,
                                          m_windowSize.y / 2));
}

void HostState::createMaps(HostState::VectorMaps & maps)
{
    maps[0] = std::make_shared<Map>();
    maps[0]->map_name = Pictures::mario_circuit_2;
    maps[1] = std::make_shared<Map>();
    maps[1]->map_name = Pictures::donut_plains_1;
    maps[2] = std::make_shared<Map>();
    maps[2]->map_name = Pictures::mario_circuit_2;

    for(size_t i{0}, j{0}; i < maps.size(); i++, j += 5)
    {
        maps[i]->tex = sf::Texture();
        maps[i]->tex.loadFromImage(Pictures::instance().getMapTex(maps[i]->map_name));
        maps[i]->m_rect = sf::RectangleShape();
        maps[i]->m_rect.setSize(sf::Vector2f(200, 200));
        maps[i]->m_rect.setTexture(&maps[i]->tex);
        maps[i]->m_rect.setPosition(300 + ( j * 80 ), (maps[i]->m_rect.getGlobalBounds().height / 2) + 100);
        maps[i]->selected = false;
    }
}