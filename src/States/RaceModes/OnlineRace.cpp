#include "OnlineRace.h"
#include "Pictures.h"
#include <cmath>
#include "CollisionHandling.h"
#include "Utilities.h"
#include "Coin.h"
#include "MacrosRaceModes.h"

//========================== Constructor / Destructor =========================
OnlineRace::OnlineRace(MarioKart::GameDataRef& data) : RaceStatesBase(data ,data->user.getMapGame() ),
                                                       m_userJoin(new User()),
                                                       m_time_update(0.0f),
                                                       m_mutex_player1(),
                                                       m_mutex_player2(),
                                                       m_thread_up(),
                                                       m_thread_get(),
                                                       m_finish(false)
{
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
    std::string name = m_data->user.getMapGame().substr(0,m_data->user.getMapGame().find('.'));
    auto locations = readFromFile<int>(name + START_POS_TXT, OBJ_DATA_SIZE.x, OBJ_DATA_SIZE.y);
    m_player.setFinishLine(float(locations[2][0]));

    if (m_data->user.getIfHost())
        initPositionLikeHost(locations);
    else
        initPositionLikeJoin(locations);

    m_thread_up = std::thread(&Services::updatePosition, &m_data->services,
                              &m_data->user, &m_player, &m_mutex_player1, &m_finish);
    m_thread_get = std::thread(&Services::getPosition, &m_data->services,
                               m_userJoin, &m_player2, &m_mutex_player2, &m_finish);
}

//============================== Handle Event ==================================
void OnlineRace::HandleEvent(const sf::Event& ev)
{
    RaceStatesBase::HandleEvent(ev);
}

//================================= Update =====================================
void OnlineRace::Update(const float deltatime)
{
	try {
		RaceStatesBase::Update(deltatime);
		UpdateNetwork(deltatime);
		if (m_player.getLap() == max_lap)
			finishOnline(true);
		if (m_player2.getLap() == max_lap)
			finishOnline(false);
	}
	catch (...) {
		finishOnline(false);
	}
}

//=============================================================================
void OnlineRace::UpdateNetwork(float deltatime)
{
    m_time_update += deltatime;
    if (m_time_update > TENTH)
    {
        m_mutex_player2.lock();
        updateDynamic();
        m_mutex_player2.unlock();
        m_time_update = 0.0f;
    }
}

//=============================================================================
void OnlineRace::updateDynamic()
{
    m_board.updateObjects(m_player2.getLastLocation().x* EIGHT,
                          m_player2.getLastLocation().y* EIGHT,
                          (m_player2.getLocation().x * EIGHT),
                          (m_player2.getLocation().y * EIGHT));
}

//=============================================================================
void OnlineRace::initPositionLikeHost( const std::vector<std::vector<int>>& locations )
{
    m_player.setLocation(sf::Vector2f(float(locations[0][0]), float(locations[0][1])));
    m_player2 = PlayerOnline(m_userJoin->getSprite(),
                             sf::Vector2f(DimensionGame::WIDTH_G / 2.f + HUNDRED,
                                          DimensionGame::HEIGHT_G - FIFTHY),
							 sf::Vector2f(float(locations[1][0]), float(locations[1][1])));
    m_board.addObjects(float(locations[1][0])* EIGHT, float(locations[1][1])* EIGHT, &m_player2);
}

//=============================================================================
void OnlineRace::initPositionLikeJoin( const std::vector<std::vector<int>>& locations )
{
    m_player.setLocation(sf::Vector2f(float(locations[1][0]), float(locations[1][1])));

    m_player2 = PlayerOnline(m_userJoin->getSprite(),
                             sf::Vector2f(DimensionGame::WIDTH_G / 2.f + HUNDRED,
                                          DimensionGame::HEIGHT_G - FIFTHY),
		sf::Vector2f(float(locations[0][0]), float(locations[0][1])));
    m_board.addObjects(float(locations[0][1])* EIGHT, float(locations[0][1])* EIGHT, &m_player2);
}

//=============================================================================
void OnlineRace::Draw()
{
	RaceStatesBase::Draw();
	m_status.printGameStatus
	(sf::seconds(m_clock.getElapsedTime().asSeconds()),
		m_player.getLap(), Coin::getCollected(), Coin::getCount(), 1);
}

//=============================================================================
void OnlineRace::finishOnline(bool option)
{
    finishThread();
    if(option)
        m_data->services.updateWin(&m_data->user, &m_player);
    finishRase(option);
}

//=============================================================================
void OnlineRace::finishThread()
{
    m_finish = true;
    m_thread_get.detach();
    m_thread_up.detach();
}
