#include "ShowUsersDataBase.h"
#include "Pictures.h"
#include "Fonts.h"
#include "OnlineRace.h"
#include <iostream>

ShowUsersDataBase::ShowUsersDataBase(MarioKart::GameDataRef& data):
                                                         m_data( data ),
                                                         m_background(),
                                                         m_backMenu(false),
                                                         m_back(),
                                                         m_users(),
                                                         m_selectedUser(false)
{

}

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
    m_title.setPosition((m_windowSize.x / 2.f) - 500, 100);

    m_data->services.getUsers( m_users, m_data->user.getId() );
    buildList( m_windowSize );
}

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
                    //std::cout << m_users.at( i ).getId() << " " << m_users.at( i ).getName() << std::endl;
                    m_data->user.setIdOther(rec.getId());
                    m_selectedUser = true;
                    break;
                }
            }
        }
    }
}

void ShowUsersDataBase::Update(float dt)
{
    if (m_backMenu)
    {
        m_data->stateStack.RemoveState();
        m_backMenu = false;
    }
    if(m_selectedUser)
    {
        std::cout << "go to race state\n";
        if(m_data->services.createRace(&m_data->user))
            m_data->stateStack.AddState(StateStack::StateRef( new OnlineRace(m_data)), false);
    }
    m_data->services.getUsers( m_users, m_data->user.getId() );
    buildList( m_windowSize );
}

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

// private functions
void ShowUsersDataBase::centerOrigin(sf::Text& text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                   std::floor(bounds.top + bounds.height / 2.f));
}

void ShowUsersDataBase::buildList( const sf::Vector2u& windowSize )
{
    size_t i = 0;
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
        text.setString( (*itr).getName() );
        text.setPosition(sf::Vector2f((windowSize.x / 2.5) - 100,
                                      (windowSize.y / 3) + (i * 100)));
        m_list_text.push_back(text);
        sprite.setTexture(Pictures::instance().getTexture(itr->getSprite()));
        sprite.setTextureRect((sf::Rect(95, 0, 33,30 )));
        sprite.scale(2, 2);
        sprite.setPosition(sf::Vector2f((windowSize.x / text.getPosition().x) + 1200,
                                        (windowSize.y / 3 ) + (i * 100)));
        m_list_sprites.push_back(sprite);

        button.setInPosition(sf::Vector2f((windowSize.x / 3) - 150,
                                          (windowSize.y / 3) + (i * 100)));
        button.setInScale(1.2f, 0.2f);
        button.setFillInColor(0, 0, 0, 120);
        m_users_rectangle.emplace_back(button);
    }
}