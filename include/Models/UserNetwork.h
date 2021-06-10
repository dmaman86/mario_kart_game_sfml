#pragma once

#include <string>
#include "SFML/Graphics.hpp"

class UserNetwork
{
public:
    UserNetwork();
    UserNetwork(std::string id, std::string name, std::string sprite, std::string map);
    ~UserNetwork() = default;

    void setId( std::string );
    void setIdOther( std::string );
    const std::string& getId();
    const std::string& getName(){ return m_name; }
    const std::string& getOtherId(){ return m_idOther; }
    void setName( std::string );
    void setSprite( std::string );
    const std::string& getSprite(){ return m_sprite; }
    void updateInGame(bool game){ m_inGame = game; }
    bool getInGame(){ return m_inGame; }
    bool getIfSound() { return m_sound; }
    void setIfSound(bool sound) { m_sound = sound; }
    void setHost(bool host){ m_host = host; }
    bool getIfHost(){ return m_host; }
    void setMapGame(std::string& map){ m_map_game = map; }
    const std::string& getMapGame(){ return m_map_game; }
    bool getIfMusic() { return m_music; }
    void setIfMusic(bool music) { m_music = music; }
private:
    std::string m_id;
    std::string m_idOther;
    std::string m_name;
    std::string m_sprite;
    std::string m_map_game;
    bool m_inGame;
    bool m_sound;
    bool m_music;
    bool m_host;
};