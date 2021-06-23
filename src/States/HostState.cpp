#include "HostState.h"
#include "Pictures.h"
#include "Fonts.h"
#include "OnlineRace.h"
#include "CareerMenu.h"
#include <iostream>
#include <thread>
#include <chrono>

//========================== Constructor =========================
HostState::HostState(MarioKart::GameDataRef & data): m_data( data ),
                                                     m_background(),
                                                     m_selected(false),
                                                     m_maps(),
                                                     m_nextState(false),
                                                     m_effectTime(0.0f),
                                                     m_createRoom(false),
                                                     m_pressEnter(false),
                                                     m_errorShow(false),
                                                     m_back_state(),
                                                     m_type_info(),
                                                     m_options_offline()
{
    createMaps();
    initOptionsOffline();
}

//========================== Constructor =========================
HostState::HostState(MarioKart::GameDataRef & data, const std::string& state): m_data( data ),
                                                                               m_background(),
                                                                               m_selected(false),
                                                                               m_maps(),
                                                                               m_nextState(false),
                                                                               m_effectTime(0.0f),
                                                                               m_createRoom(false),
                                                                               m_pressEnter(false),
                                                                               m_errorShow(false),
                                                                               m_back_state(),
                                                                               m_type_info(state),
                                                                               m_options_offline()
{
    createMaps();
    initOptionsOffline();
}

//========================= Init section ======================================
void HostState::Init()
{
    sf::Vector2u textureSize;
    m_windowSize = m_data->window->getSize();
    textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();

    m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_background.setScale((float)m_windowSize.x / textureSize.x,
                          (float)m_windowSize.y / textureSize.y);

    m_back = std::make_shared<Button>(Pictures::MenuButtons1);
    m_back->setTextureInRect(PositionButtons::back);
    m_back->setCallback([this](){
        m_data->stateStack.RemoveState();
    });

    initTitlesTexts();
    initErrorsTexts();
}

//============================== Handle Event ==================================
void HostState::HandleEvent(const sf::Event & event)
{
    if(sf::Event::MouseButtonPressed == event.type)
    {
        auto location = m_data->window->mapPixelToCoords(
                {event.mouseButton.x, event.mouseButton.y});

        if (m_back->validGlobalBound(location))
            m_back->initCallback();
        else
        {
            for( auto & map : m_maps )
            {
                if(map.second->m_rect.getGlobalBounds().contains(location))
                {
                    m_data->user.setMapGame(map.second->map_name);
                    map.second->m_rect.setOutlineColor(sf::Color::Blue);
                    map.second->selected = !map.second->selected;
                    resetOutLineColor(map.first);
                    break;
                }
            }
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_selected)
        m_pressEnter = true;
}

//================================= Update =====================================
void HostState::Update(float dt)
{
    for( auto & map : m_maps )
    {
        if(map.second->selected)
            m_selected = true;
    }
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
        m_options_offline[m_type_info]();
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
                m_data->stateStack.AddState(StateStack::StateRef( new
                                        OnlineRace(m_data)), false);
                break;
            }
        }
    }
}

//================================= Draw =====================================
void HostState::Draw()
{
    sf::RenderWindow& window = *m_data->window;

    window.draw(m_background);
    window.draw(*m_back.get());
    window.draw(m_title);

    if(!m_errorShow)
    {
        for(auto map : m_maps)
        {
            window.draw(map.second->m_rect);
            window.draw(map.second->map_name_tex);
        }

        if(m_selected)
            window.draw(m_createGame);
    }
    if(m_errorShow)
        window.draw(m_error);
}

//================================= Resume =====================================
void HostState::Resume()
{
    m_validConnection = false;
    m_selected = false;
    m_nextState = false;
    m_createRoom = false;
    m_pressEnter = false;
    for(auto& map : m_maps)
        map.second->selected = false;
    if(m_data->user.getId().size() > 1)
        m_data->services.resetUser(&m_data->user);
}

//========================= Private Functions ================================
void HostState::initTitlesTexts()
{
    m_title.setFont(Fonts::instance().getFont());
    m_title.setString("Select Map");
    m_title.setFillColor(sf::Color(76, 0, 153));
    m_title.setCharacterSize(70);
    m_title.setPosition((m_windowSize.x / 2) - 300, (m_windowSize.y / 2) - 300);

    m_createGame.setFont(Fonts::instance().getFont());
    m_createGame.setString("Press Enter to continue");
    m_createGame.setFillColor(sf::Color(76, 0, 153));
    m_createGame.setCharacterSize(50);
    m_createGame.setOrigin(m_createGame.getLocalBounds().width / 2,
                           m_createGame.getLocalBounds().height / 2);
    m_createGame.setPosition(sf::Vector2f(m_windowSize.x * 0.5f,
                                          (m_windowSize.y / 2) + 300));
    m_createGame.setOutlineColor(sf::Color::White);
    m_createGame.setOutlineThickness(5.f);
}

//=============================================================================
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

//=============================================================================
void HostState::createMaps()
{
    auto rainbow = std::make_shared<Map>();
    rainbow->map_name = Pictures::rainbow_road;
    rainbow->map_name_tex = sf::Text();
    rainbow->map_name_tex.setString(rainbow->map_name.substr(0,
                                               rainbow->map_name.find('.')));

    auto donut = std::make_shared<Map>();
    donut->map_name = Pictures::donut_plains_1;
    donut->map_name_tex = sf::Text();
    donut->map_name_tex.setString(donut->map_name.substr(0,
                                               donut->map_name.find('.')));

    auto ghost = std::make_shared<Map>();
    ghost->map_name = Pictures::ghost_valley;
    ghost->map_name_tex = sf::Text();
    ghost->map_name_tex.setString(ghost->map_name.substr(0,
                                               ghost->map_name.find('.')));

    m_maps[MapNames::RainBow] = rainbow;
    m_maps[MapNames::Donut] = donut;
    m_maps[MapNames::Ghost] = ghost;

    size_t j = 0;
    for(auto it = m_maps.begin(); it != m_maps.end(); it++, j += 5)
    {
        initTexture(it->second->tex, it->second->map_name);
        initRectangleShape(it->second->m_rect, it->second->tex, j);
        initText(it->second->map_name_tex, j, it->second->m_rect);
        it->second->selected = false;
    }
}

//=============================================================================
void HostState::initTexture(sf::Texture& tex, const std::string& map_name)
{
    tex = sf::Texture();
    tex.loadFromImage(Pictures::instance().getMapTex(map_name));
}

//=============================================================================
void HostState::initRectangleShape(sf::RectangleShape& rect, sf::Texture& tex, size_t pos)
{
    rect = sf::RectangleShape();
    rect.setSize(sf::Vector2f(250, 250));
    rect.setTexture(&tex);
    rect.setPosition(200 + ( pos * 80 ), (rect.getGlobalBounds().height / 2) + 100);
    rect.setOutlineThickness(5.f);
}

//=============================================================================
void HostState::initText(sf::Text& text, size_t pos, const sf::RectangleShape& rect)
{
    text.setCharacterSize(40);
    text.setFont(Fonts::instance().getFont());
    text.setFillColor(sf::Color::Red);
    text.setOutlineThickness(5.f);
    text.setPosition(160 + ( pos * 90 ), (rect.getGlobalBounds().height / 2) + 400);
}

//=============================================================================
void HostState::resetOutLineColor(MapNames index)
{
    for(auto it = m_maps.begin(); it != m_maps.end(); it++)
    {
        if(it->first != index)
            it->second->m_rect.setOutlineColor(sf::Color::White);
    }
}

//=============================================================================
void HostState::initOptionsOffline()
{
    m_options_offline["CoinRace"] = [this](){
        m_data->stateStack.AddState(StateStack::StateRef( new CoinRace(m_data)),
                                    false);
    };
    m_options_offline["DriftKingRace"] = [this](){
        m_data->stateStack.AddState(StateStack::StateRef( new DriftKingRace(m_data)),
                                    false);
    };
    m_options_offline["TimeRace"] = [this](){
        m_data->stateStack.AddState(StateStack::StateRef( new TimeRace(m_data)),
                                    false);
    };
}