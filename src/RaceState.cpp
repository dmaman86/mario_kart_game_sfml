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
    m_cameraX = 0.0;
    m_cameraY= -17.0;
    m_cameraZ = 0.0;
    m_theta = 180;
    //m_tempsMoyen =0;
    m_map = Mode7("mario_circuit_2.png", WITDH, HIGHT, m_cameraX, m_cameraY, m_cameraZ, m_theta, 300.0);
}

void RaceState::Draw() {

   // std::cout << "X is: " << m_cameraX << " Y is: " << m_cameraY<< " z is: " << m_cameraZ<<"theta :" << m_theta << std::endl;
    m_data->window->draw(m_map.getSprite());


}

void RaceState::Update(float deltatime) {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_cameraZ -= std::cos(m_theta*3.141592/180)*deltatime*CAR_SPEED;
        m_cameraX += std::sin(m_theta *3.141592/180)*deltatime*CAR_SPEED;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

        m_theta++;
        if (m_theta >= 360) m_theta = 0;

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

        m_theta--;
        if (m_theta <= 0) m_theta += 360;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_cameraZ += std::cos(m_theta*3.141592/180);
        std::cout << m_theta<< " ";
        std::cout << sin(m_theta)<<std::endl;
        m_cameraX -= std::sin(m_theta *3.141592/180);
    }

    m_map.setCamera(m_cameraX, m_cameraY, m_cameraZ);
    m_map.setTheta(m_theta);
    m_map.calc();

}

void RaceState::HandleEvent(const sf::Event &) {


}

