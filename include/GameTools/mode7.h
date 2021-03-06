#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "GameObj.h"
#include "PlayerOnline.h"
#include "Player.h"
#include "Camera.h"

/*
	Mode7 :
	Manages and computes the image the player sees, the road,
	And the objects get a vector reference and update where they should be drawn
*/
class Mode7
{

public:
	//=============  Constructor  ===============
	Mode7();
	Mode7(std::string const& , unsigned int , unsigned int
		, float , float);
	//===========  Public functions  ============
	void setTheta(const float theta);
	const bool calcInAngle(sf::Vector2f&, 
		const sf::Vector2u &, const Camera& camera)const;
	void UpdateImg(std::map<std::pair<float, float>,
		std::shared_ptr<GameObj>>&,const Camera&);
	const sf::Sprite& getSprite();

private:
	//============  Public members  =============
	unsigned int m_screenWidth, m_screenHeight,
		m_imageWidth, m_imageHeight, m_H_helf, m_W_half;
	float m_FOV, m_D, m_cosinus, m_sinus; 
	sf::Image m_image, m_imageTransformed;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	//===========  Public functions  ============
	void setScreen(const unsigned int width,
		const  unsigned int height);
	void loadImage(const std::string & file);
	void setFOVangle(const float angle);

}; // end Mode7