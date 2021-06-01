#include "RaceState.h"
#include <cmath>
RaceState::RaceState(MarioKart::GameDataRef data):m_data(data)
{

}

void RaceState::run() {

    m_sky.setPosition(0,0);
    auto sktt = sf::Texture();
    sktt.loadFromFile("sky_back.png");
    m_sky.setTexture(sktt);
    m_sky.setTextureRect(sf::Rect(100,0,640,200));
    auto event = sf::Event();
    m_clock.restart();
    float deltatime;
    while(m_window.isOpen())
    {
        deltatime = m_clock.getElapsedTime().asSeconds();
        m_clock.restart();
    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
        }

      }

    }
}

void RaceState::Init() {
    m_window.setFramerateLimit(60);
    m_player = Player(sf::Vector2f(250, 370), sf::Vector2f(112, 61));
    m_cameraX = m_player.getIntLocation().x*8;
    m_cameraY= -17;
    m_cameraZ = m_player.getIntLocation().y*8;;
    m_theta = 0;
    //m_tempsMoyen =0;
    m_map = Mode7("mario_circuit_2.png", WITDH, HIGHT, m_cameraX, m_cameraY, m_cameraZ, m_theta, 300.0);
    m_int_map.fillMap("mario_circuit_2.txt");
    std::cout << m_int_map(6,20);
}

void RaceState::Draw() {


    int xx = m_player.getIntLocation().x;
    int zz =  m_player.getIntLocation().y;

   std::cout << " XX is: "<<xx << " ZZ is: "<<zz <<"   ";
   std::cout <<" int map is: "  << m_int_map(zz,xx) <<" \n" ;
   // std::cout << "X is: " << m_cameraX << " Y is: " << m_cameraY<< " z is: " << m_cameraZ<<"theta :" << m_theta << std::endl;
    m_data->window->draw(m_map.getSprite());
    m_player.draw(*m_data->window);



}

void RaceState::Update(float deltatime) {

    //if(m_int_map(m_player.getIntLocation().x,m_player.getIntLocation().y) == 0)
    std::cout << " player loc x : " << m_player.getIntLocation().x << " y: " << m_player.getIntLocation().y << " player speed : " << m_player.m_speed;
    m_player.setIntLocation(deltatime,m_int_map(m_player.getIntLocation().y,m_player.getIntLocation().x));

    m_cameraX = m_player.getIntLocation().x*8 - 50*sin(m_player.getAngle()*3.1415/180);
    m_cameraZ = m_player.getIntLocation().y *8 + 50*cos(m_player.getAngle()*3.1415/180);


    m_theta = m_player.getAngle();
    m_map.setCamera(m_cameraX, m_cameraY, m_cameraZ);
    m_map.setTheta(m_theta);
    m_map.calc();

}

void RaceState::HandleEvent(const sf::Event &) {

 m_player.updateDir();

}

