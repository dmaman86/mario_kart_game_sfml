#pragma once
#include "GameObj.h"

class PlayerBase : public GameObj {

public:
	PlayerBase() {};
	PlayerBase(const sf::Texture&, const sf::Vector2f pos, const sf::Vector2f loc);

	void setMove(){ m_start_move = true; }
	bool getMove(){ return m_start_move; }
	void updateLastLocation() {
		m_last_location = *m_location;
	}
    const int  getLap() const { return m_lap; }
    void addLap() { ++m_lap; }
	void decLap() { --m_lap; }

    void set_lap(const int lap){ m_lap = lap; }
protected:
	sf::Vector2f m_last_location;
    int m_lap;
private:
    bool m_start_move;
};

