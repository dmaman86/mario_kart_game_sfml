#pragma once
#include "GameObj.h"

/*
	PlayerBase:
		An intermediate class from which the player's heir and the playerOnline
*/
class PlayerBase : public GameObj {

public:
	//============================= Constructor ===============================
	PlayerBase() : m_lap(0), m_start_move(false) {};
	PlayerBase
	(const sf::Texture& t, const sf::Vector2f& loc, const sf::Vector2f &pos)
		:GameObj::GameObj(t, loc, pos), m_start_move(false),m_last_location(),
		m_lap(0) {}
	
	//========================== Public Functions =============================
	void setMove(){ m_start_move = true; }
	const bool getMove()const{ return m_start_move; }
	void updateLastLocation() { m_last_location = m_location; }
    const int  getLap() const { return m_lap; }
    void addLap() { ++m_lap; }
	void decLap() { --m_lap; }
    void set_lap(const int lap){ m_lap = lap; }

protected:
	// protected members
	sf::Vector2f m_last_location;
    int m_lap;

private:
	// private members
    bool m_start_move;

};// end PlayerBase

