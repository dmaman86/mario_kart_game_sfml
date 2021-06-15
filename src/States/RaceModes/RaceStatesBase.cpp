#include "RaceStatesBase.h"
#include "Pictures.h"
#include <cmath>
#include "CollisionHandling.h"
#include "Utilities.h"

//========================== Constructor / Destructor =========================
RaceStatesBase::RaceStatesBase(MarioKart::GameDataRef data) : m_data(data),
                                                    m_status(*data->window),
                                                    m_player(sf::Vector2f(WITDH_G*2 / 2,HIGHT_G*2 - 50),
                                                             sf::Vector2f(112,56),
                                                             m_data->user.getSprite()),
                                                    m_map_race( "mario_circuit_2.png")
{

}


RaceStatesBase::RaceStatesBase(MarioKart::GameDataRef data,const  std::string& map): m_data(data),
                                                                     m_status(*data->window),
                                                                     m_player(sf::Vector2f(WITDH_G*2 / 2,HIGHT_G*2 - 50),
                                                                              sf::Vector2f(63,110),
                                                                              m_data->user.getSprite()),
                                                                     m_map_race( "mario_circuit_2.png") {

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
    m_player.setLastScorePos(m_int_map.getFloorScore(m_player.getLocation().y, m_player.getLocation().x));
    m_clock.restart();
    m_status.printGameStatus(m_clock, m_player.getLap(), 0, 0, correctDirection());

}



//=============================================================================
void RaceStatesBase::InitMap()
{
    m_cameraX = m_player.getIntLocation().x * 8;
    m_cameraY = -17;
    m_cameraZ = m_player.getIntLocation().y * 8;;
    m_map = Mode7(m_map_race, WITDH_G, HIGHT_G, m_cameraX, m_cameraY, m_cameraZ, m_player.getAngle(), 300.0);
    m_int_map.fillMap(m_map_race);
    m_int_map.fillObjectMap(m_map_race);
}
//=============================================================================
void RaceStatesBase::InitSky()
{
    m_sky_back.setTexture(Pictures::instance().getTexture(Pictures::sky_back));
	m_sky_back.setTextureRect(sf::Rect(0, 0, 300, 32));
	m_sky_back.setScale(4, 4);
	m_sky_back.setPosition(0, m_data->window->getSize().y / 6.33);

	m_sky_front.setTexture(Pictures::instance().getTexture(Pictures::sky_front));
	m_sky_front.setTextureRect(sf::Rect(0, 0, 300, 32));
	m_sky_front.setScale(4, 4);
    m_sky_front.setPosition(0, m_data->window->getSize().y / 6.33);
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
    m_cameraX = m_player.getIntLocation().x * 8 - 50 * calcSinDegree(m_player.getAngle());
    m_cameraZ = m_player.getIntLocation().y * 8 + 50 * calcCosDegree(m_player.getAngle());
    m_theta = m_player.getAngle();
    m_map.setCamera(m_cameraX, m_cameraY, m_cameraZ);
    m_map.setTheta(m_player.getAngle());
    m_map.calc(m_int_map.m_vec_obj, m_player.getIntLocation());
}

//=============================================================================
void RaceStatesBase::UpdatePlayer(float deltatime)
{
    m_player.Update(deltatime, m_int_map.getFloorScore(m_player.getLocation().y, m_player.getLocation().x));
    m_player.CheckLap(m_int_map.getFloorScore(m_player.getLocation().y, m_player.getLocation().x));
}

//=============================================================================
void RaceStatesBase::Draw() {

    m_player.updateAnimation();
    m_data->window->draw(m_map.getSprite());
    m_data->window->draw(m_sky_back);
    m_data->window->draw(m_sky_front);
    drawStaticObjects();
    m_player.draw(*m_data->window);
    m_status.printGameStatus(m_clock, m_player.getLap(), 0, 0, correctDirection());
}

//=============================================================================
void RaceStatesBase::drawStaticObjects() {

    for (auto& x : m_int_map.m_vec_obj)
        if (x.second->getIsInAngle())
        {
            x.second->draw(*m_data->window);
            x.second->setInAngle(false);
        }

}

//=============================================================================
void RaceStatesBase::HandleCollision(float deltatime)
{
    for (auto& obj : m_int_map.m_vec_obj)
        if(obj.second.get()->getIsInAngle() && m_player.collisionWith(*obj.second))
            processCollision(m_player, *obj.second);
    processCollision(m_player, m_int_map(m_player.getIntLocation().y, m_player.getIntLocation().x));
}

//=============================================================================
void RaceStatesBase::updateObjLocation()
{
    float obj_length, camera_length;
    unsigned int xs, ys;
    for (auto& d : m_int_map.m_vec_obj)
    {
        //if (m_map.calcInAngle( ys, xs,d.first.first, d.first.second))
        //{
        //    obj_length = calcLength(sf::Vector2f(d.second->getIntLocation().x, d.second->getIntLocation().y),
        //                            sf::Vector2f(m_player.getIntLocation().x, m_player.getIntLocation().y));

        //    camera_length = (calcLength(sf::Vector2f(d.first.second, d.first.first),sf::Vector2f(m_cameraZ, m_cameraX))) / 8.f;

        //    d.second->setPosition(sf::Vector2f(xs, ys));

        //    if (camera_length < 10) // x < 10
        //    {
        //        d.second->setScale(3, 3);
        //        d.second->setPosition(sf::Vector2f(xs, ys - 20));
        //    }
        //    else if (camera_length < 15)// 10 < x < 15
        //    {
        //        d.second->setScale(2, 2);
        //        d.second->setPosition(sf::Vector2f(xs, ys - 15));
        //    }
        //    else if (camera_length < 20)// 15 < x < 20
        //    {
        //        d.second->setScale(1.5, 1.5);
        //        d.second->setPosition(sf::Vector2f(xs, ys - 10));
        //    }
        //    else if (camera_length < 25)// 20 < x < 25
        //    {
        //        d.second->setScale(1, 1);
        //        d.second->setPosition(sf::Vector2f(xs, ys - 5));
        //    }
        //    else if (camera_length < 30)// 25 < x < 30
        //    {
        //        d.second->setScale(0.5, 0.5);
        //    }

        //    d.second->setInAngle(true);

        //    if (camera_length < 5.0 || camera_length > 30)
        //        d.second->setInAngle(false);
        //}
    }
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
    //std::cout << m_int_map.getFloorScore(m_player.getLocation().y, m_player.getLocation().x) << " "  << m_player.getLastScorePos() << "\n";


    if (m_int_map.getFloorScore(m_player.getLocation().y, m_player.getLocation().x) <= m_player.getLastScorePos())
        currect = false;
    else if (m_int_map.getFloorScore(m_player.getLocation().y, m_player.getLocation().x) >= m_player.getLastScorePos())
        currect = true;


    return currect;
}
