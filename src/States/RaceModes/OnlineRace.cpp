#include "States/RaceModes/OnlineRace.h"
#include "Pictures.h"
#include <cmath>
#include "CollisionHandling.h"
#include "Utilities.h"
#include <thread>

//========================== Constructor / Destructor =========================
OnlineRace::OnlineRace(MarioKart::GameDataRef data) : RaceStatesBase(data ,data->user.getMapGame() ),
                                                      m_userJoin(data->user.getOnline() ? new User() : nullptr ),
                                                      m_time_update(0.0f),
                                                      m_mutex_player1(),
                                                      m_mutex_player2(),
                                                      m_thread_up(),
                                                      m_thread_get(),
                                                      m_services(),
                                                      m_finish(false)
{
    if(m_userJoin)
		 m_data->services.getUser(m_userJoin, m_data->user.getOtherId());
}
//=============================================================================
OnlineRace::~OnlineRace()
{
    delete m_userJoin;
}

//========================= Init section ======================================
void OnlineRace::Init()
{
    RaceStatesBase::Init();
	InitNetwork();

}

//=============================================================================
void OnlineRace::InitNetwork()
{
	if (m_userJoin)
	{
		if (m_data->user.getIfHost())
		{
			m_player.setLocation(sf::Vector2f(112, 56));
			m_player2 = PlayerOnline(m_userJoin->getSprite(),
				sf::Vector2f(WITDH_G / 2.f + 100, HIGHT_G - 50), sf::Vector2f(117, 59));
            m_board.addObjects(117 * 8, 59 * 8, &m_player2);

        }
	
		else
		{	
			m_player.setLocation(sf::Vector2f(117, 59));
			m_player2 = PlayerOnline(m_userJoin->getSprite(),
				sf::Vector2f(WITDH_G / 2.f + 100, HIGHT_G - 50), sf::Vector2f(112, 56));
            m_board.addObjects(112*8, 56 * 8, &m_player2);

        }
		
        m_thread_up = std::thread(&Services::updatePosition, &m_data->services, &m_data->user, &m_player, &m_mutex_player1, &m_finish);
        m_thread_get = std::thread(&Services::getPosition, &m_data->services, m_userJoin, &m_player2, &m_mutex_player2, &m_finish);
	}
}



//============================== Handle Event ==================================
void OnlineRace::HandleEvent(const sf::Event& ev)
{
    RaceStatesBase::HandleEvent(ev);
    if(sf::Event::KeyPressed)
    {
        if(ev.key.code == sf::Keyboard::N)
        {
            m_finish = true;
            m_thread_get.detach();
            m_thread_up.detach();
            m_data->stateStack.RemoveState();
        }
    }
}

//================================= Update =====================================
void OnlineRace::Update(float deltatime) {
	
    RaceStatesBase::Update(deltatime);
	UpdateNetwork(deltatime);
}

//=============================================================================
void OnlineRace::UpdateNetwork(float deltatime)
{
	m_time_update += deltatime;

	if (m_userJoin)
	{
		m_time_update += deltatime;
		if (m_time_update > 0.1f)
		{
		    m_mutex_player2.lock();
            updateDynamic();
		    m_mutex_player2.unlock();
			m_time_update = 0.0f;
		}
	}

}



//=============================================================================
void OnlineRace::updateDynamic()
{
	m_board.updateObjects(m_player2.getLastLocation().x*8,
							m_player2.getLastLocation().y*8,
                            (m_player2.getLocation().x * 8),
                            (m_player2.getLocation().y * 8));
}

