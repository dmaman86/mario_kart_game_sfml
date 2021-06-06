#include "RaceState.h"
#include "Pictures.h"
#include <cmath>
#include "CollisionHandling.h"

RaceState::RaceState(MarioKart::GameDataRef data) : m_data(data), pipe(sf::Vector2f(150, 230), sf::Vector2f(50, 50)) {

}

void RaceState::Init() {
	m_window.setFramerateLimit(60);
	m_player = Player(sf::Vector2f(WITDH_G / 2, HIGHT_G - 50), sf::Vector2f(63, 124));

	m_cameraX = m_player.getIntLocation().x * 8;
	m_cameraY = -17;
	m_cameraZ = m_player.getIntLocation().y * 8;;

	//m_tempsMoyen =0;
	m_map = Mode7("mario_circuit_2.png", WITDH_G, HIGHT_G, m_cameraX, m_cameraY, m_cameraZ, m_player.getAngle(), 300.0);
	m_int_map.fillMap("mario_circuit_2.txt");
	m_int_map.fillObjectMap("mario_circuit_2.txt");
	//std::cout << m_int_map(6, 20);
}
void RaceState::Draw() {


	int xx = m_player.getIntLocation().x;
	int zz = m_player.getIntLocation().y;

	//std::cout << " XX is: "<<xx << " ZZ is: "<<zz <<"   ";
  //  std::cout <<" int map is: "  << m_int_map(zz,xx) << " angle: "<<m_player.getAngle() << " \n" ;
	// std::cout << "X is: " << m_cameraX << " Y is: " << m_cameraY<< " z is: " << m_cameraZ<<"theta :" << m_theta << std::endl;

	m_data->window->draw(m_map.getSprite());

	drawStaticObjects();
	//    for(int i = 0 ; i < 128; i ++)
	//        for(int j = 0 ; j < 128; j ++)
	//        {
	//            if(m_int_map(i,j) == 7.0 )
	//            {
	//                auto pipe = Pipe(sf::Vector2f(i+100,j+100),sf::Vector2f(50,50));
	//                pipe.draw(*m_data->window);
	//            }
	//        }

	m_player.draw(*m_data->window);
	// pipe.draw(*m_data->window);

}

void RaceState::Update(float deltatime) {

	//if(m_int_map(m_player.getIntLocation().x,m_player.getIntLocation().y) == 0)
  //  std::cout << " player loc x : " << m_player.getIntLocation().x << " y: " << m_player.getIntLocation().y << " player speed : " << m_player.m_speed;
	m_player.setIntLocation(deltatime, m_int_map(m_player.getIntLocation().y, m_player.getIntLocation().x));
	
	m_cameraX = m_player.getIntLocation().x * 8 - 50 * sin(m_player.getAngle() * 3.1415 / 180);
	m_cameraZ = m_player.getIntLocation().y * 8 + 50 * cos(m_player.getAngle() * 3.1415 / 180);
	

	m_theta = m_player.getAngle();
	m_map.setCamera(m_cameraX, m_cameraY, m_cameraZ);
	m_map.setTheta(m_player.getAngle());
	m_map.calc(m_int_map.m_vec_obj, m_player.getIntLocation());
	HandleCollision(deltatime);
}

void RaceState::HandleEvent(const sf::Event&)
{
	m_player.updateDir();
}

void RaceState::BuildVecObj()
{

}

void RaceState::drawStaticObjects() {

	for (auto& x : m_int_map.m_vec_obj)
		if (x.second->getIsInAngle()) {
			x.second->draw(*m_data->window);
			//if (x.first.second >= m_player.getIntLocation().y*8) 
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
