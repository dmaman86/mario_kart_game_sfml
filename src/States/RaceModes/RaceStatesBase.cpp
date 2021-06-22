#include "RaceStatesBase.h"
#include "Pictures.h"
#include <cmath>
#include "CollisionHandling.h"
#include "Utilities.h"
#include "mode7.h"
#include "TraficLight.h"
#include "StartCloud.h"
#include "Sounds.h"
#include "Fonts.h"

//========================== Constructor / Destructor =========================
RaceStatesBase::RaceStatesBase(MarioKart::GameDataRef& data) : m_data(data),
                                                    m_status(*data->window),
                                                    m_player(sf::Vector2f(WITDH_G*2 / 2,HIGHT_G*2 - 50),
                                                             sf::Vector2f(112,56),
                                                             m_data->user.getSprite(), m_data->user.getIfSound()),
                                                    m_map_race( m_data->user.getMapGame())
	, m_sky("can we delete this constructor ?? !! please! !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
{

}


RaceStatesBase::RaceStatesBase(MarioKart::GameDataRef& data,const  std::string& map): m_data(data),
                                                                     m_status(*data->window),
                                                                     m_player(sf::Vector2f(WITDH_G*2 / 2,HIGHT_G*2 - 50),
                                                                              sf::Vector2f(112, 56),
                                                                              m_data->user.getSprite(), m_data->user.getIfSound()),
                                                                     m_map_race( m_data->user.getMapGame()),
	m_view(sf::FloatRect(0.f, 0.f, WITDH_G * 2, HIGHT_G * 2)),
	m_sky(map), m_speed_scr(),m_first(true)// 1000.f, 600.f));
{
	m_win_s = sf::Sound(Sounds::instance().getSoundBuffer(Sounds::win));
	m_lose_s = sf::Sound(Sounds::instance().getSoundBuffer(Sounds::lose));
}

//=============================================================================
RaceStatesBase::~RaceStatesBase()
{
}

//========================= Init section ======================================
void RaceStatesBase::Init()
{
	RaceStatesBase::InitPlayerLoc();
    InitMap();
    InitSky();
    m_player.setLastScorePos(m_board.getFloorScore(m_player.getLocation().y, m_player.getLocation().x));
    m_clock.restart();
	m_view.setViewport(sf::FloatRect(0.25f, 0.05, 0.5f, 0.5f));


    m_musicMap.openFromFile(Sounds::vanillaLakeMap);
    m_musicMap.setLoop(true);
    m_data->menuMusic.stop();

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
void RaceStatesBase::InitPlayerLoc()
{
    std::string name = m_data->user.getMapGame().substr(0,m_data->user.getMapGame().find('.'));
    auto locations = readFromFile<float>(name+"_start_position.txt",3,2);
    m_player.setFinishLine(locations[2][0]);
		m_player.setLocation(sf::Vector2f(locations[0][0],locations[0][1]));


//	else if (m_data->user.getMapGame() == "ghost_valley.png")
//		m_player.setLocation(sf::Vector2f(950 / 8, 600 / 8));
}
//=============================================================================
void RaceStatesBase::InitSky()
{
	auto textureSize = Pictures::instance().getTexture(Pictures::menuBackground).getSize();
	m_background.setTexture(Pictures::instance().getTexture(Pictures::menuBackground));
	m_background.setScale((float)m_data->window->getSize().x / textureSize.x,
		(float)m_data->window->getSize().y / textureSize.y);

	m_game_boy.setTexture(Pictures::instance().getTexture(Pictures::game_boy));
	m_game_boy.setScale(1.5, 1);
	m_game_boy.setPosition(150,0);
}


//============================== Handle Event ==================================
void RaceStatesBase::HandleEvent(const sf::Event&)
{
    m_player.updateDir();
}

//================================= Update =====================================
void RaceStatesBase::Update(float deltatime) {

	if (m_first)
		m_first = false;
	else	{
		UpdatePlayer(deltatime);
		m_sky.Update();
		UpdateMap();
		HandleCollision(deltatime);
		this->updateAnimation(deltatime);
	}
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
	
	m_data->window->draw(m_background);
	m_data->window->draw(m_game_boy);
	auto v = m_data->window->getView();
	m_data->window->setView(m_view);
	m_data->window->draw(m_map.getSprite());
	m_data->window->draw(m_sky.getBack());
	m_data->window->draw(m_sky.getFront());
	drawStaticObjects();
	m_speed_scr.Draw(*m_data->window, m_player.getSpeed(), m_player.getCoefficient());
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
        if (obj.second.get()->getIsInAngle() && m_player.collisionWith(*obj.second))
        {
            if(obj.second->getIsActive() && m_data->user.getIfSound())
            obj.second->playSound();

            processCollision(m_player, *obj.second);
        }

    processCollision(m_player, m_board(m_player.getIntLocation().y, m_player.getIntLocation().x));
}

//=============================================================================
bool RaceStatesBase::correctDirection()
{
    bool currect = false;

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
    sf::Time delta{};;
    sf::Clock lira;
    UpdateMap();
    if (m_data->user.getIfSound())
        trafficlight.playSound();
    while (m_clock.getElapsedTime().asSeconds() < 4)
    {
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
    if (m_data->user.getIfMusic())
        m_musicMap.play();

}

void RaceStatesBase::finishRase(const bool w_or_l)
{
	m_data->user.updateInGame(false);
	m_data->stateStack.RemoveState();
	sf::Text txt;
	txt.setFont(Fonts::instance().Fonts::getFontMario());
	txt.setPosition(50, 50);
	(w_or_l) ? txt.setString("Win") :
		txt.setString("Lose");

	if (m_data->user.getIfSound())
		(w_or_l) ? m_win_s.play() :
		m_lose_s.play();

	auto cur_t = m_clock.getElapsedTime().asSeconds();
	while (cur_t + 3.f > m_clock.getElapsedTime().asSeconds())
	{
		m_data->window->clear();
		m_cameraY -= 3;
		RaceStatesBase::Draw();
		RaceStatesBase::UpdateMap();
		m_data->window->draw(txt);
		m_data->window->display();
	}
}

void RaceStatesBase::updateAnimation(float time) {
    m_board.updateAnimation(time);

}

