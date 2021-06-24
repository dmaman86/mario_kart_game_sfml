#include "ShowUsersDataBase.h"
#include "Pictures.h"
#include "Fonts.h"
#include "OnlineRace.h"
#include "Services.h"
#include <iostream>

//========================== Constructor ===========================
ShowUsersDataBase::ShowUsersDataBase(MarioKart::GameDataRef& data):
                                                         m_data( data ),
                                                         m_background(),
                                                         m_backMenu(false),
                                                         m_back(),
                                                         m_users(),
                                                         m_selectedUser(false),
                                                         m_get_users(false),
                                                         m_thread_get_users(),
                                                         m_mutex(),
                                                         m_time_refresh(0.f)
{
    m_thread_get_users = std::thread(&Services::getUsers, &m_data->services,
                                     &m_users, &m_get_users, &m_mutex);
}

//========================== Init ===========================
void ShowUsersDataBase::Init()
{
    sf::Vector2u textureSize;
    m_windowSize = m_data->window->getSize();
    textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();

    m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
    m_background.setScale((float)m_windowSize.x / textureSize.x,
                          (float)m_windowSize.y / textureSize.y);

    m_back.setTexture(Pictures::instance().getTexture(Pictures::MenuButtons1));
    m_back.setTextureRect(sf::Rect(0,563,180,63));

    m_title.setFont(Fonts::instance().getFont());
    m_title.setString("Online Drivers");
    m_title.setFillColor(sf::Color(76, 0, 153));
    m_title.setCharacterSize(70);
    m_title.setPosition(float((m_windowSize.x / 2) - 300), float((m_windowSize.y / 2) - 300));

    buildList(m_windowSize);
}

//========================== Handle Event ===========================
void ShowUsersDataBase::HandleEvent(const sf::Event & event)
{
    if(sf::Event::MouseButtonPressed == event.type)
    {
        auto location = m_data->window->mapPixelToCoords(
                {event.mouseButton.x, event.mouseButton.y});

        if (m_back.getGlobalBounds().contains(location))
            m_backMenu = !m_backMenu;

        else
        {
            for( size_t i{ 0 }; i < m_users_rectangle.size(); i++ )
            {
                auto rec = m_users_rectangle[ i ];
                if( rec.validGlobalBound(location))
                {
                    m_data->user.setIdOther(rec.getId());
                    m_selectedUser = true;
                    break;
                }
            }
        }
    }
}

//========================== Update ===========================
void ShowUsersDataBase::Update(const float dt)
{
    if (m_backMenu)
    {
        finishThread();
        m_data->stateStack.RemoveState();
    }
    if(m_selectedUser)
    {
        std::cout << "go to race state\n";
        finishThread();
        if(m_data->services.createRace(&m_data->user))
            m_data->stateStack.AddState(StateStack::StateRef( new OnlineRace(m_data)), false);
    }
    m_time_refresh += dt;
    if (m_time_refresh > 1.5f)
    {
        buildList( m_windowSize );
        m_time_refresh = 0.f;
    }
}

//========================== Draw ===========================
void ShowUsersDataBase::Draw()
{
    sf::RenderWindow& window = *m_data->window;

    window.draw(m_background);
    window.draw(m_back);
    window.draw(m_title);

    for( auto & rec : m_users_rectangle )
        window.draw(rec);

    for( auto& txt: m_list_text )
        window.draw( txt );

    for( auto & spt : m_list_sprites )
        window.draw( spt );
}

//========================== Resume ===========================
void ShowUsersDataBase::Resume()
{
    m_selectedUser = false;
    m_get_users = false;
    deleteUser(m_data->user.getOtherId());
    if(m_data->user.getId().size() > 1)
        m_data->services.resetUser(&m_data->user);
    m_thread_get_users = std::thread(&Services::getUsers, &m_data->services, &m_users,
                                     &m_get_users, &m_mutex);
}

//========================== Private Functions ===========================
void ShowUsersDataBase::centerOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                   std::floor(bounds.top + bounds.height / 2.f));
}

//==================================================================
void ShowUsersDataBase::buildList( const sf::Vector2u& windowSize )
{
    size_t i = 0;
    m_mutex.lock();
    m_list_text.clear();
    m_list_sprites.clear();
    m_users_rectangle.clear();
    for( auto itr = m_users.begin(); itr != m_users.end(); itr++, i++ )
    {
        auto button = Button( itr->getId(), Pictures::rectangle);
        sf::Text text;
        sf::Sprite sprite;

        text.setFont(Fonts::instance().getFont());
        text.setFillColor(sf::Color(76, 0, 153));
        text.setCharacterSize(60);
        text.setStyle(sf::Text::Bold);
        text.setString( itr->getName() );
        text.setPosition(sf::Vector2f(float((windowSize.x / 2.5) - 100),
                                      (float(windowSize.y / 3) + (i * 100))));
        m_list_text.push_back(text);
        sprite.setTexture(Pictures::instance().getTexture(itr->getSprite()));
        sprite.setTextureRect(sf::Rect(95, 0, 33,30 ));
        sprite.scale(2, 2);
        sprite.setPosition(sf::Vector2f(float((windowSize.x / text.getPosition().x) + 1200),
                                        float((windowSize.y / 3 ) + (i * 100))));
        m_list_sprites.push_back(sprite);

        button.setInPosition(sf::Vector2f(float((windowSize.x / 3) - 150),
                                          float((windowSize.y / 3) + (i * 100))));
        button.setInScale(1.2f, 0.2f);
        button.setFillInColor(Color::GRAYCOLOR);
        m_users_rectangle.emplace_back(button);
    }
    m_mutex.unlock();
}

//==================================================================
void ShowUsersDataBase::finishThread()
{
    m_get_users = true;
    m_thread_get_users.detach();
}

//==================================================================
void ShowUsersDataBase::deleteUser(const std::string & otherId)
{
    m_users.erase(std::remove_if(m_users.begin(), m_users.end(),
                                 [&otherId](User& user) {
                                     return user.compareId(otherId);
                                 }));
}