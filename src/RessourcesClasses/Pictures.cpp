#include "Pictures.h"
#include <iostream>
#include <exception>

const std::string Pictures::MarioDriver = "mario.png";
const std::string Pictures::mario_circuit_2 = "mario_circuit_2.png";
const std::string Pictures::donut_plains_1 = "base.png";
const std::string Pictures::misc = "misc.png";
const std::string Pictures::menuBackground = "menuBackground.png";
const std::string Pictures::marioLogo = "marioLogo.png";
const std::string Pictures::BowserDriver = "bowser.png";
const std::string Pictures::DKDriver = "dk.png";
const std::string Pictures::KoopaDriver = "koopa.png";
const std::string Pictures::LuigiDriver = "luigi.png";
const std::string Pictures::PeachDriver = "peach.png";
const std::string Pictures::ToadDriver = "toad.png";
const std::string Pictures::YoshiDriver = "yoshi.png";
const std::string Pictures::rectangle = "rectangle.jpg";
const std::string Pictures::drivers = "drivers.png";
const std::string Pictures::sky_back = "sky_back.png";
const std::string Pictures::sky_front = "sky_front.png";
const std::string Pictures::speed0 = "speed0.png";
const std::string Pictures::speed1 = "speed1.png";
const std::string Pictures::speed2 = "speed2.png";
const std::string Pictures::speed3 = "speed3.png";
const std::string Pictures::speed4 = "speed4.png";
const std::string Pictures::MenuButtons1 = "menuButtons1.png";
const std::string Pictures::GameStartGui = "gameStartGui.png";
const std::string Pictures::helpStateback = "helpStateback.png";
const std::string Pictures::game_boy = "gameBoy.png";


Pictures &Pictures::instance() {
    static Pictures inst;
    return inst;
}

Pictures::Pictures():m_drivers(DRIVER_VECTOR_LEN)
{
    if(!(m_pics[Pictures::MarioDriver] = sf::Texture()).loadFromFile(Pictures::MarioDriver))
        throw std::runtime_error("Cant Open " + Pictures::MarioDriver);
    if(!(m_maps[Pictures::mario_circuit_2] = sf::Image()).loadFromFile(Pictures::mario_circuit_2))
        throw std::runtime_error("Cant Open " + Pictures::mario_circuit_2);
    if(!(m_maps[Pictures::donut_plains_1] = sf::Image()).loadFromFile(Pictures::donut_plains_1))
        throw std::runtime_error("Can't Open " + Pictures::donut_plains_1);
	if (!(m_pics[Pictures::misc] = sf::Texture()).loadFromFile(Pictures::misc))
		throw std::runtime_error("Cant Open " + Pictures::misc);
    if(!(m_pics[Pictures::menuBackground] = sf::Texture()).loadFromFile(Pictures::menuBackground))
        throw std::runtime_error("Cant Open " + Pictures::menuBackground);
    if(!(m_pics[Pictures::marioLogo] = sf::Texture()).loadFromFile(Pictures::marioLogo))
        throw std::runtime_error("Cant Open " + Pictures::marioLogo);
    if(!(m_pics[Pictures::BowserDriver] = sf::Texture()).loadFromFile(Pictures::BowserDriver))
        throw std::runtime_error("Cant Open " + Pictures::BowserDriver);
    if(!(m_pics[Pictures::DKDriver] = sf::Texture()).loadFromFile(Pictures::DKDriver))
        throw std::runtime_error("Cant Open " + Pictures::DKDriver); 
    if(!(m_pics[Pictures::KoopaDriver] = sf::Texture()).loadFromFile(Pictures::KoopaDriver))
        throw std::runtime_error("Cant Open " + Pictures::KoopaDriver); 
    if(!(m_pics[Pictures::LuigiDriver] = sf::Texture()).loadFromFile(Pictures::LuigiDriver))
        throw std::runtime_error("Cant Open " + Pictures::LuigiDriver); 
    if(!(m_pics[Pictures::PeachDriver] = sf::Texture()).loadFromFile(Pictures::PeachDriver))
        throw std::runtime_error("Cant Open " + Pictures::PeachDriver); 
    if(!(m_pics[Pictures::ToadDriver] = sf::Texture()).loadFromFile(Pictures::ToadDriver))
        throw std::runtime_error("Cant Open " + Pictures::ToadDriver); 
    if(!(m_pics[Pictures::YoshiDriver] = sf::Texture()).loadFromFile(Pictures::YoshiDriver))
        throw std::runtime_error("Cant Open " + Pictures::YoshiDriver); 
    if (!(m_pics[Pictures::rectangle] = sf::Texture()).loadFromFile(Pictures::rectangle))
        throw std::runtime_error("Cant Open " + Pictures::rectangle);
    if (!(m_pics[Pictures::drivers] = sf::Texture()).loadFromFile(Pictures::drivers))
        throw std::runtime_error("Cant Open " + Pictures::drivers);
	if (!(m_pics[Pictures::sky_back] = sf::Texture()).loadFromFile(Pictures::sky_back))
		throw std::runtime_error("Cant Open " + Pictures::sky_back);
	if (!(m_pics[Pictures::sky_front] = sf::Texture()).loadFromFile(Pictures::sky_front))
		throw std::runtime_error("Cant Open " + Pictures::sky_front);
	if (!(m_pics[Pictures::speed0] = sf::Texture()).loadFromFile(Pictures::speed0))
		throw std::runtime_error("Cant Open " + Pictures::speed0);
	if (!(m_pics[Pictures::speed1] = sf::Texture()).loadFromFile(Pictures::speed1))
		throw std::runtime_error("Cant Open " + Pictures::speed1);
	if (!(m_pics[Pictures::speed2] = sf::Texture()).loadFromFile(Pictures::speed2))
		throw std::runtime_error("Cant Open " + Pictures::speed2);
	if (!(m_pics[Pictures::speed3] = sf::Texture()).loadFromFile(Pictures::speed3))
		throw std::runtime_error("Cant Open " + Pictures::speed3);
	if (!(m_pics[Pictures::speed4] = sf::Texture()).loadFromFile(Pictures::speed4))
		throw std::runtime_error("Cant Open " + Pictures::speed4);
    if (!(m_pics[Pictures::GameStartGui] = sf::Texture()).loadFromFile(Pictures::GameStartGui))
        throw std::runtime_error("Cant Open " + Pictures::GameStartGui);
    if (!(m_pics[Pictures::MenuButtons1] = sf::Texture()).loadFromFile(Pictures::MenuButtons1))
        throw std::runtime_error("Cant Open " + Pictures::MenuButtons1);
    if (!(m_pics[Pictures::helpStateback] = sf::Texture()).loadFromFile(Pictures::helpStateback))
        throw std::runtime_error("Cant Open " + Pictures::helpStateback);

	if (!(m_pics[Pictures::game_boy] = sf::Texture()).loadFromFile(Pictures::game_boy))
		throw std::runtime_error("Cant Open " + Pictures::game_boy);


    for (int i = 0; i < NUMBER_OF_DRIVERS; ++i) {
        m_drivers[i] = (setDriverData(i));
    }
    m_trafficLight.emplace_back(87,64,8,24);
    m_trafficLight.emplace_back(96,64,8,24);
    m_trafficLight.emplace_back(105,64,8,24);
    m_trafficLight.emplace_back(114,64,8,24);


    m_startCloud.emplace_back(5,1,36,32);
    m_startCloud.emplace_back(47,1,36,32);
    m_startCloud.emplace_back(89,1,36,32);

}

const sf::Texture &Pictures::getTexture(const std::string& name) const {
    return m_pics.at(name);
}

const sf::Image &Pictures::getMapTex(const std::string& name)const {
    return m_maps.at(name);
}

std::vector <sf::IntRect > Pictures::setDriverData(int i) {

    const auto size = sf::Vector2i(34, 34);
    auto location = sf::Vector2i(6,8+ i * 36);
    const auto middleSpace = sf::Vector2i(0, 3);
    auto driver = std::vector <sf::IntRect >() ;


    for (int j = 0; j < DRIVER_VECTOR_LEN; ++j) {

        driver.emplace_back( location,size);
        location.x += 32;
    }

    return driver;
}

const std::vector <sf::IntRect >&  Pictures::getDriveAnimationData(const std::string & driver)const {

    if(driver == MarioDriver)
    {
        return m_drivers[Mario];
    }

    if(driver == BowserDriver)
    {
        return m_drivers[Boewser];
    }
    if(driver == DKDriver)
    {
        return m_drivers[Dk];
    }

    if(driver == KoopaDriver)
    {
        return m_drivers[Koopa];
    }

    if(driver == LuigiDriver)
    {
        return m_drivers[Luigi];
    }

    if(driver == PeachDriver)
    {
        return m_drivers[Peach];
    }

    if(driver == ToadDriver)
    {
        return m_drivers[Toad];
    }

    if(driver == YoshiDriver)
    {
        return m_drivers[Yoshi];
    }
    else return m_drivers[Mario];
}

const std::vector<sf::IntRect>&Pictures::getTraffic() const{
    return m_trafficLight;
}

const std::vector<sf::IntRect> &Pictures::getCloud()const {
    return m_startCloud;
}




