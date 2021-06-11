#include "RaceState.h"
#include "Pictures.h"
#include <cmath>
#include "CollisionHandling.h"
#include "Utilities.h"

RaceState::RaceState(MarioKart::GameDataRef data) : m_data(data),
                        pipe(sf::Vector2f(150, 230), sf::Vector2f(50, 50)),
                        m_userJoin( data->user.getOnline()? new UserNetwork() : nullptr ),
                        m_player(sf::Vector2f(WITDH_G / 2,HIGHT_G - 50),sf::Vector2f(63,124),m_data->user.getSprite()),
                        m_time_update(
                                0.0f),
                        m_map_race( data->user.getIfHost() ? data->user.getMapGame() : "mario_circuit_2.png")
{
	if(m_userJoin)
		 m_data->services.getUser(m_userJoin, m_data->user.getOtherId());
}

RaceState::~RaceState()
{
    delete m_userJoin;
}

void RaceState::Init()
{
	m_window.setFramerateLimit(60);
	
	if (m_userJoin)
	{
		m_player2 = PlayerOnline(m_userJoin->getSprite(),
			sf::Vector2f(WITDH_G / 2.f + 100, HIGHT_G - 50), sf::Vector2f(63, 110));

		m_int_map.addObjects(63 * 8, 110 * 8, &m_player2);
	}
	m_cameraX = m_player.getIntLocation().x * 8;
	m_cameraY = -17;
	m_cameraZ = m_player.getIntLocation().y * 8;;

	m_map = Mode7(m_map_race, WITDH_G, HIGHT_G, m_cameraX, m_cameraY, m_cameraZ, m_player.getAngle(), 300.0);
	m_int_map.fillMap(m_map_race);
	m_int_map.fillObjectMap(m_map_race);
    m_player.setLastScorePos( m_int_map.getFloorScore(m_player.getLocation().y,m_player.getLocation().x));


	m_clock.restart();

}
void RaceState::Draw() {

    m_player.updateAnimation();
	m_data->window->draw(m_map.getSprite());
	drawStaticObjects();
	m_player.draw(*m_data->window);

}

void RaceState::Update(float deltatime) {

	m_player.updateSpeed(deltatime);
	processCollision(m_player, m_int_map(m_player.getIntLocation().y, m_player.getIntLocation().x));
	m_player.setLastScorePos(m_int_map.getFloorScore(m_player.getLocation().y,m_player.getLocation().x));
	m_player.updateLocation(deltatime);
    if(m_int_map.getFloorScore(m_player.getLocation().y,m_player.getLocation().x) - m_player.getLastScorePos() >= 400 )
        m_player.addLap();
    std::cout <<m_player.getLastScorePos() << "  ::   " << m_int_map.getFloorScore(m_player.getLocation().y,m_player.getLocation().x) << " "<< m_player.getLap() << " \n";
	m_cameraX = m_player.getIntLocation().x * 8 - 50 * calcSinDegree(m_player.getAngle());
	m_cameraZ = m_player.getIntLocation().y * 8 + 50 * calcCosDegree(m_player.getAngle());

	m_theta = m_player.getAngle();
	m_map.setCamera(m_cameraX, m_cameraY, m_cameraZ);
	m_map.setTheta(m_player.getAngle());
	m_map.calc(m_int_map.m_vec_obj,&m_player2, m_player.getIntLocation());
	m_time_update += deltatime;

	if (m_userJoin)
	{
		m_time_update += deltatime;
		if (m_time_update > 0.1f)
		{
			m_data->services.updatePosition(m_data->user.getId(), m_player.getLocation().x, m_player.getLocation().y);
			m_data->services.getPosition(m_data->user.getOtherId(), m_player2.getLocation().x, m_player2.getLocation().y);
			updateDynamic();
			m_time_update = 0.0f;
		}
	}
	// updateDynamic();
	//updateObjLocation();
	HandleCollision(deltatime);

}

void RaceState::HandleEvent(const sf::Event&)
{
	m_player.updateDir();
}

void RaceState::drawStaticObjects() {

	for (auto& x : m_int_map.m_vec_obj)
		if (x.second->getIsInAngle())
		{
			x.second->draw(*m_data->window);
			x.second->setInAngle(false);
		}
	//    float length;
//    auto m_T = HIGHT / 2;
//    auto m_L = WITDH / 2;
//    float xw,zw;
//    auto m_cosinus = std::cos(m_player.getAngle() * 3.1415 / 180.0);
//    auto m_sinus = std::sin(m_player.getAngle() * 3.1415 / 180.0);
//    auto m_D = m_T / std::tan(300 * 3.1415 / 360.0);
//    sf::Vector2f l;
//    //  m_cameraX = m_player.getIntLocation().x*8 - 50*sin(m_player.getAngle()*3.1415/180);
//    //  m_cameraZ = m_player.getIntLocation().y *8 + 50*cos(m_player.getAngle()*3.1415/180);
//    sf::Vector2i save{0,0};
//    int epsilon =-8;
//    for(auto& obj : m_int_map.m_vec_obj )
//        for (auto ys{m_T + 1}; ys < MAPSIZE; ys++) {
//            for (auto xs{0}; xs < MAPSIZE; xs++) {
//             xw = m_cameraX - m_cameraY * ((float) xs - (float) m_L) /((float) m_T - (float) ys) * m_cosinus -m_D * m_cameraY / ((float) m_T - (float) ys) *m_sinus;
//             zw = m_cameraZ -m_cameraY * ((float) xs - (float) m_L) /((float) m_T - (float) ys) * m_sinus +m_D * m_cameraY / ((float) m_T - (float) ys) *m_cosinus;
//
//            if (xw < 0 || zw < 0 || xw >= MAPSIZE || zw >= MAPSIZE)
//                continue;
//
//            else {
//              l.x = (m_int_map.transferPixelToCords(sf::Vector2f(zw, xw)).x);
//                l.y = (m_int_map.transferPixelToCords(sf::Vector2f(zw, xw)).y);
//                if(abs(obj->getIntLocation().y - l.y) >= 0.9 && abs( obj->getIntLocation().x - l.x) >= 0.9)
//                {
//                    length = m_int_map.calcLength(l, sf::Vector2f(m_player.getIntLocation()));
//
//                    if (m_int_map(l.x, l.y) == 7 && save != sf::Vector2i (l.x,l.y))
//                   {
//                       obj->setPosition(sf::Vector2f(xs, ys));
//                        save = sf::Vector2i (l.x,l.y);
//                       obj->setScale(50 / length, 50 / length);
//                       obj->draw(*m_data->window);
//                        break;
//                    }
//                }
//            }
//        }
//    }
}

void RaceState::HandleCollision(float deltatime)
{

	for (auto& obj : m_int_map.m_vec_obj)
		if(obj.second.get()->getIsInAngle() && m_player.collisionWith(*obj.second))
			processCollision(m_player, *obj.second);
}

void RaceState::updateObjLocation()
{
	float obj_length, camera_length;
	unsigned int xs, ys;
	for (auto& d : m_int_map.m_vec_obj)
	{
		if (m_map.calcInAngle( ys, xs,d.first.first, d.first.second))
		{
				obj_length = calcLength(sf::Vector2f(d.second->getIntLocation().x, d.second->getIntLocation().y),
					sf::Vector2f(m_player.getIntLocation().x, m_player.getIntLocation().y));

				camera_length = (calcLength(sf::Vector2f(d.first.second, d.first.first),sf::Vector2f(m_cameraZ, m_cameraX))) / 8.f;

				d.second->setPosition(sf::Vector2f(xs, ys));

				if (camera_length < 10) // x < 10
				{
					d.second->setScale(3, 3);
					d.second->setPosition(sf::Vector2f(xs, ys - 20));
				}
				else if (camera_length < 15)// 10 < x < 15
				{
					d.second->setScale(2, 2);
					d.second->setPosition(sf::Vector2f(xs, ys - 15));
				}
				else if (camera_length < 20)// 15 < x < 20
				{
					d.second->setScale(1.5, 1.5);
					d.second->setPosition(sf::Vector2f(xs, ys - 10));
				}
				else if (camera_length < 25)// 20 < x < 25
				{
					d.second->setScale(1, 1);
					d.second->setPosition(sf::Vector2f(xs, ys - 5));
				}
				else if (camera_length < 30)// 25 < x < 30
				{
					d.second->setScale(0.5, 0.5);
				}

				d.second->setInAngle(true);

				if (camera_length < 5.0 || camera_length > 30)
					d.second->setInAngle(false);
		}
	}
}

void RaceState::updateDynamic()
{
	m_player2.updateLastLocation();
	m_int_map.updateObjects(m_player2.getLastLocation().x*8,
                            m_player2.getLastLocation().y*8,
                            (m_player2.getIntLocation().x * 8),
                            (m_player2.getIntLocation().y * 8));
}


