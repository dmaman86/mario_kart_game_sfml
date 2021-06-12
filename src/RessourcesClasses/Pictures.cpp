#include "Pictures.h"
#include <iostream>
#include <exception>

const std::string Pictures::MarioDriver = "mario.png";
const std::string Pictures::mario_circuit_2 = "mario_circuit_2.png";
const std::string Pictures::misc = "misc.png";
const std::string Pictures::menuBackground = "menuBackground.png";
const std::string Pictures::marioLogo = "marioLogo.png";
const std::string Pictures::letsPlay = "letsPlay.png";
const std::string Pictures::help = "help.png";
const std::string Pictures::about = "about.png";
const std::string Pictures::online = "online.png";
const std::string Pictures::settings = "settings.png";
const std::string Pictures::career = "career.png";
const std::string Pictures::back = "back.png";
const std::string Pictures::new_game = "new_game.png";
const std::string Pictures::load_game = "load_game.png";
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
	if (!(m_pics[Pictures::misc] = sf::Texture()).loadFromFile(Pictures::misc))
		throw std::runtime_error("Cant Open " + Pictures::misc);
    if(!(m_pics[Pictures::menuBackground] = sf::Texture()).loadFromFile(Pictures::menuBackground))
        throw std::runtime_error("Cant Open " + Pictures::menuBackground);
    if(!(m_pics[Pictures::marioLogo] = sf::Texture()).loadFromFile(Pictures::marioLogo))
        throw std::runtime_error("Cant Open " + Pictures::marioLogo);
    if(!(m_pics[Pictures::letsPlay] = sf::Texture()).loadFromFile(Pictures::letsPlay))
        throw std::runtime_error("Cant Open " + Pictures::letsPlay);
    if(!(m_pics[Pictures::help] = sf::Texture()).loadFromFile(Pictures::help))
        throw std::runtime_error("Cant Open " + Pictures::help);
    if(!(m_pics[Pictures::about] = sf::Texture()).loadFromFile(Pictures::about))
        throw std::runtime_error("Cant Open " + Pictures::about);
    if(!(m_pics[Pictures::online] = sf::Texture()).loadFromFile(Pictures::online))
        throw std::runtime_error("Cant Open " + Pictures::online);
    if(!(m_pics[Pictures::settings] = sf::Texture()).loadFromFile(Pictures::settings))
        throw std::runtime_error("Cant Open " + Pictures::settings);
    if(!(m_pics[Pictures::career] = sf::Texture()).loadFromFile(Pictures::career))
        throw std::runtime_error("Cant Open " + Pictures::career);
	if (!(m_pics[Pictures::back] = sf::Texture()).loadFromFile(Pictures::back))
		throw std::runtime_error("Cant Open " + Pictures::back);
	if(!(m_pics[Pictures::new_game] = sf::Texture()).loadFromFile(Pictures::new_game))
        throw std::runtime_error("Cant Open " + Pictures::new_game);
	if (!(m_pics[Pictures::load_game] = sf::Texture()).loadFromFile(Pictures::load_game))
		throw std::runtime_error("Cant Open " + Pictures::load_game);
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

    for (int i = 0; i < NUMBER_OF_DRIVERS; ++i) {
        m_drivers[i] = (setDriverData(i));
    }


}

const sf::Texture &Pictures::getTexture(std::string name) const {
    return m_pics.at(name);
}

const sf::Image &Pictures::getMapTex(std::string string) {
    return m_maps[string];
}

AnimationData Pictures::setDriverData(int i) {

    const auto size = sf::Vector2i(34, 34);
    auto location = sf::Vector2i(6,8+ i * 35);
    const auto middleSpace = sf::Vector2i(0, 10);
    auto driver = AnimationData{};


    for (int j = 0; j < DRIVER_VECTOR_LEN; ++j) {

        driver.m_data.emplace_back( location,size);
        location.x += 32;
    }

    return driver;
}

const AnimationData& Pictures::getDriveAnimationData(std::string driver) {

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




