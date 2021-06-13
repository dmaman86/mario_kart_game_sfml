#include "RaceState.h"
#include "Pictures.h"
#include <cmath>
#include "CollisionHandling.h"
#include "Utilities.h"

//========================== Constructor / Destructor =========================
RaceState::RaceState(MarioKart::GameDataRef data) : m_data(data),
						m_status(*data->window),
                        pipe(sf::Vector2f(150, 230), sf::Vector2f(50, 50)),
                        m_userJoin( data->user.getOnline() ? new UserNetwork() : nullptr ),
                        m_player(sf::Vector2f(WITDH_G / 2,HIGHT_G - 50),
                                 sf::Vector2f(63,124),
                                 m_data->user.getSprite()),
                        m_time_update(0.0f),
                        m_map_race( data->user.getIfHost() ? data->user.getMapGame() : "mario_circuit_2.png"),
                        m_mutex_player1(),
                        m_mutex_player2(),
                        m_thread_up(),
                        m_thread_get(),
                        m_services()
{
	if(m_userJoin)
		 m_data->services.getUser(m_userJoin, m_data->user.getOtherId());
}
//=============================================================================
RaceState::~RaceState()
{
    delete m_userJoin;
}

//========================= Init section ======================================
void RaceState::Init()
{
	m_window.setFramerateLimit(60);
	InitNetwork();
	InitMap();
	InitSky();
	m_player.setLastScorePos(m_int_map.getFloorScore(m_player.getLocation().y, m_player.getLocation().x));
	m_clock.restart();
	m_status.printGameStatus(m_clock, m_player.getLap(), 0, 0, correctDirection());

}

//=============================================================================
void RaceState::InitNetwork()
{
	if (m_userJoin)
	{
		m_player2 = PlayerOnline(m_userJoin->getSprite(),
			sf::Vector2f(WITDH_G / 2.f + 100, HIGHT_G - 50), sf::Vector2f(63, 110));

		m_int_map.addObjects(63 * 8, 110 * 8, &m_player2);
        m_thread_up = std::thread(&Services::updatePosition, &m_services, &m_data->user, &m_player, &m_mutex_player1);
        m_thread_get = std::thread(&Services::getPosition, &m_services, m_userJoin, &m_player2, &m_mutex_player2);
	}
}

//=============================================================================
void RaceState::InitMap()
{
	m_cameraX = m_player.getIntLocation().x * 8;
	m_cameraY = -17;
	m_cameraZ = m_player.getIntLocation().y * 8;;
	m_map = Mode7(m_map_race, WITDH_G, HIGHT_G, m_cameraX, m_cameraY, m_cameraZ, m_player.getAngle(), 300.0);
	m_int_map.fillMap(m_map_race);
	m_int_map.fillObjectMap(m_map_race);
}
//=============================================================================
void RaceState::InitSky()
{
	m_sky_back.setTexture(Pictures::instance().getTexture(Pictures::sky_back));
	m_sky_back.setScale(3, 3);
	m_sky_front.setTexture(Pictures::instance().getTexture(Pictures::sky_front));
	m_sky_front.setScale(5, 5);
	m_sky_front.setPosition(0, m_data->window->getSize().y / 10.5);
	m_sky_front.setTextureRect(sf::Rect(1040, 0, 1024 / 5, 32));
}


//============================== Handle Event ==================================
void RaceState::HandleEvent(const sf::Event&)
{
	m_player.updateDir();
}

//================================= Update =====================================
void RaceState::Update(float deltatime) {
	
	UpdatePlayer(deltatime);
	this->updateSky();
	UpdateNetwork(deltatime);
    UpdateMap();
	HandleCollision(deltatime);
}

//=============================================================================
void RaceState::UpdateNetwork(float deltatime)
{
	m_time_update += deltatime;

	if (m_userJoin)
	{
		m_time_update += deltatime;
		if (m_time_update > 0.1f)
		{
		    m_mutex_player2.lock();
		    std::cout << "RaceState. New position player 2: " << m_player2.getLocation().x <<
		                " " << m_player2.getLocation().y << std::endl;
            updateDynamic();
		    m_mutex_player2.unlock();
			m_time_update = 0.0f;
		}
	}
	//updateDynamic();
	//updateObjLocation();
}

//=============================================================================
void RaceState::UpdateMap()
{
	m_cameraX = m_player.getIntLocation().x * 8 - 50 * calcSinDegree(m_player.getAngle());
	m_cameraZ = m_player.getIntLocation().y * 8 + 50 * calcCosDegree(m_player.getAngle());
	m_theta = m_player.getAngle();
	m_map.setCamera(m_cameraX, m_cameraY, m_cameraZ);
	m_map.setTheta(m_player.getAngle());
	m_map.calc(m_int_map.m_vec_obj, &m_player2, m_player.getIntLocation());
}

//=============================================================================
void RaceState::UpdatePlayer(float deltatime)
{
	m_player.Update(deltatime, m_int_map.getFloorScore(m_player.getLocation().y, m_player.getLocation().x));
	m_player.CheckLap(m_int_map.getFloorScore(m_player.getLocation().y, m_player.getLocation().x));
}

//=============================================================================
void RaceState::Draw() {

    m_player.updateAnimation();
	m_data->window->draw(m_map.getSprite());
	m_data->window->draw(m_sky_back);
	m_data->window->draw(m_sky_front);
	drawStaticObjects();
	m_player.draw(*m_data->window);
	m_status.printGameStatus(m_clock, m_player.getLap(), 0, 0, correctDirection());
}

//=============================================================================
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

//=============================================================================
void RaceState::HandleCollision(float deltatime)
{
	for (auto& obj : m_int_map.m_vec_obj)
		if(obj.second.get()->getIsInAngle() && m_player.collisionWith(*obj.second))
			processCollision(m_player, *obj.second);
	processCollision(m_player, m_int_map(m_player.getIntLocation().y, m_player.getIntLocation().x));
}

//=============================================================================
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

//=============================================================================
void RaceState::updateDynamic()
{
	m_player2.updateLastLocation();
	m_int_map.updateObjects(m_player2.getLastLocation().x*8,
                            m_player2.getLastLocation().y*8,
                            (m_player2.getLastLocation().x * 8),
                            (m_player2.getLastLocation().y * 8));
}

//=============================================================================
void RaceState::updateSky()
{
	auto x = m_sky_front.getTextureRect();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		x.left += 3;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (x.left <= 10)
			x.left = 1040;
		x.left -= 3;
	}
	x.left %= 2560;
	m_sky_front.setTextureRect(x);
}

//=============================================================================
bool RaceState::correctDirection()
{
	bool currect = false;
	std::cout << m_int_map.getFloorScore(m_player.getLocation().y, m_player.getLocation().x) << " "  << m_player.getLastScorePos() << "\n";
	

	if (m_int_map.getFloorScore(m_player.getLocation().y, m_player.getLocation().x) <= m_player.getLastScorePos())
		currect = false;
	else if (m_int_map.getFloorScore(m_player.getLocation().y, m_player.getLocation().x) >= m_player.getLastScorePos())
		currect = true;


	return currect;
}
