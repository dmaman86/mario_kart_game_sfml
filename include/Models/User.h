#pragma once

#include <string>
#include <vector>

class User
{
public:
    User();
    User(std::string id, std::string name, std::string sprite, std::string map);
    ~User() = default;

    void setId( std::string );
    void setIdOther( std::string );
    const std::string& getId();
    const std::string& getName();
    const std::string& getOtherId();
    void setName( std::string );
    void setSprite( std::string );
    const std::string& getSprite();
    void updateInGame(bool);
    bool getInGame();
    bool getIfSound();
    void setIfSound(bool);
    void setHost(bool);
    bool getIfHost();
    void setMapGame(const std::string&);
    const std::string& getMapGame();
    bool getIfMusic();
    void setIfMusic(bool);
	void setOnline(const bool);
	const bool getOnline();
	const int getCoins()const;
	void setCoins(int);
	void setDrive(const std::string&);
    const std::string& getDrive(size_t);
    const int getMaxDrivers();

private:
    std::string m_id;
    std::string m_idOther;
    std::string m_name;
    std::string m_sprite;
    std::string m_map_game;
    std::vector<std::string> m_drivers;
    bool m_inGame;
    bool m_sound;
    bool m_music;
    bool m_host;
	bool m_online;
	int m_numberCoins;
	int m_max_drivers;

	void initDrivers();
};