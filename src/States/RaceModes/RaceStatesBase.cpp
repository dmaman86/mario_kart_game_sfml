#include "RaceStatesBase.h"
#include "Pictures.h"
#include <cmath>
#include "CollisionHandling.h"
#include "Utilities.h"
#include "mode7.h"
#include "TraficLight.h"
#include "StartCloud.h"
//========================== Constructor / Destructor =========================
RaceStatesBase::RaceStatesBase(MarioKart::GameDataRef data) : m_data(data),
                                                    m_status(*data->window),
                                                    m_player(sf::Vector2f(WITDH_G*2 / 2,HIGHT_G*2 - 50),
                                                             sf::Vector2f(112,56),
                                                             m_data->user.getSprite()),
                                                    m_map_race( m_data->user.getMapGame())
{

}


RaceStatesBase::RaceStatesBase(MarioKart::GameDataRef data,const  std::string& map): m_data(data),
                                                                     m_status(*data->window),
                                                                     m_player(sf::Vector2f(WITDH_G*2 / 2,HIGHT_G*2 - 50),
                                                                              sf::Vector2f(112, 56),
                                                                              m_data->user.getSprite()),
                                                                     m_map_race( m_data->user.getMapGame()),
	m_view(sf::FloatRect(0.f, 0.f, WITDH_G * 2, HIGHT_G * 2))// 1000.f, 600.f));
{

}

//=============================================================================
RaceStatesBase::~RaceStatesBase()
{
}

//========================= Init section ======================================
void RaceStatesBase::Init()
{
    InitMap();
    InitSky();
    m_player.setLastScorePos(m_board.getFloorScore(m_player.getLocation().y, m_player.getLocation().x));
    m_clock.restart();
	m_view.setViewport(sf::FloatRect(0.25f, 0.05, 0.5f, 0.5f));

   // m_status.printGameStatus(m_clock, m_player.getLap(), 0, 0, correctDirection());
    //m_map.initThread(m_board.m_vec_obj);
    //m_build_map_thread = std::thread(&Mode7::calc, &m_map,std::ref(m_board.m_vec_obj));
    startRaceScreen();

}



//=============================================================================
void RaceStatesBase::InitMap()
{
	m_camera.InitCamera(m_player.getIntLocation());
	m_cameraY = -17;
    m_map = Mode7(m_map_race, WITDH_G, HIGHT_G, m_player.getAngle(), 300.0);
    m_board.fillMap(m_map_race);
    m_board.fillObjectMap(m_map_race);
}
//=============================================================================
void RaceStatesBase::InitSky()
{
	m_game_boy.setTexture(Pictures::instance().getTexture(Pictures::game_boy));
	m_game_boy.setScale(1.5, 1);
	m_game_boy.setPosition(150,0);

    m_sky_back.setTexture(Pictures::instance().getTexture(Pictures::sky_back));
	m_sky_back.setTextureRect(sf::Rect(0, 0, 300, 32));
	m_sky_back.setScale(4, 4);
	m_sky_back.setPosition(0, m_data->window->getSize().y / 10);

	m_sky_front.setTexture(Pictures::instance().getTexture(Pictures::sky_front));
	m_sky_front.setTextureRect(sf::Rect(0, 0, 300, 32));
	m_sky_front.setScale(4, 4);
    m_sky_front.setPosition(0, m_data->window->getSize().y / 10);
}


//============================== Handle Event ==================================
void RaceStatesBase::HandleEvent(const sf::Event&)
{
    m_player.updateDir();
}

//================================= Update =====================================
void RaceStatesBase::Update(float deltatime) {

    UpdatePlayer(deltatime);
    this->updateSky();
    UpdateMap();
    HandleCollision(deltatime);
}


//=============================================================================
void RaceStatesBase::UpdateMap()
{
	m_camera.setCamera(m_player.getLocation(), m_player.getAngle(), m_cameraY);
    m_map.setTheta(m_player.getAngle());
    m_map.UpdateImg(m_board.getObjData(), m_camera);
}

//=============================================================================
void RaceStatesBase::UpdatePlayer(float deltatime)
{
    m_player.Update(deltatime, m_board.getFloorScore(m_player.getLocation().y, m_player.getLocation().x));
    m_player.CheckLap(m_board.getFloorScore(m_player.getLocation().y, m_player.getLocation().x));
    m_player.updateAnimation(deltatime);
}

//=============================================================================
void RaceStatesBase::Draw() {

	m_data->window->draw(m_game_boy);
	auto v = m_data->window->getView();
	m_data->window->setView(m_view);
	m_data->window->draw(m_map.getSprite());
	m_data->window->draw(m_sky_back);
    m_data->window->draw(m_sky_front);
	drawStaticObjects();
	m_player.draw(*m_data->window);
	m_data->window->setView(v);
}

//=============================================================================
void RaceStatesBase::drawStaticObjects() {

    for (auto& x : m_board.getObjData())
        if (x.second->getIsInAngle())
        {
            x.second->draw(*m_data->window);
            x.second->setInAngle(false);
        }

}

//=============================================================================
void RaceStatesBase::HandleCollision(float deltatime)
{
    for (auto& obj : m_board.getObjData())
        if(obj.second.get()->getIsInAngle() && m_player.collisionWith(*obj.second))
            processCollision(m_player, *obj.second);
    processCollision(m_player, m_board(m_player.getIntLocation().y, m_player.getIntLocation().x));
}

//=============================================================================
void RaceStatesBase::updateSky()
{
    auto x = m_sky_front.getTextureRect();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        x.left += 1;

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (x.left <= 10)
            x.left = 1040;
        x.left -= 1;
    }
    x.left %= 2560;
    m_sky_front.setTextureRect(x);
}

//=============================================================================
bool RaceStatesBase::correctDirection()
{
    bool currect = false;
    //std::cout << m_board.getFloorScore(m_player.getLocation().y, m_player.getLocation().x) << " "  << m_player.getLastScorePos() << "\n";


    if (m_board.getFloorScore(m_player.getLocation().y, m_player.getLocation().x) <= m_player.getLastScorePos())
        currect = false;
    else if (m_board.getFloorScore(m_player.getLocation().y, m_player.getLocation().x) >= m_player.getLastScorePos())
        currect = true;


    return currect;
}
//=============================================================================
void RaceStatesBase::startRaceScreen() {
    auto trafficlight = TraficLight();
    auto cloud = StartCloud();
    sf::Time delta {};;
    sf::Clock lira;
	UpdateMap();

    while(m_clock.getElapsedTime().asSeconds() < 4)
    {
		//m_data->window->draw(m_map.getSprite());
        m_data->window->clear();
		RaceStatesBase::Draw();
        delta = lira.restart();
		auto v = m_data->window->getView();
		m_data->window->setView(m_view);
        trafficlight.updateAnimation(delta.asSeconds());
        cloud.updateAnimation(delta.asSeconds());
        cloud.draw(*m_data->window);
        trafficlight.draw(*m_data->window);
        m_data->window->display();
		m_data->window->setView(v);

    }
	m_clock.restart();

}

