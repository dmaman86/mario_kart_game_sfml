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
*/
class Mode7
{

public:
	//=============  Constructor  ===============
	Mode7() {};
	Mode7(std::string const& , unsigned int , unsigned int
		, float , float);
	//===========  Public functions  ============
	void setTheta(float theta);
	bool calcInAngle(sf::Vector2f&, const sf::Vector2u, const Camera& camera);//
	void UpdateImg(std::map<std::pair<float, float>, std::shared_ptr<GameObj>>&,const Camera&);
	sf::Sprite getSprite();

private:
	//============  Public members  =============
	unsigned int m_screenWidth, m_screenHeight;
	unsigned int m_H_helf, m_W_half; 
	unsigned int m_imageWidth, m_imageHeight;
	float m_FOV, m_D; // m_D distance du point de la caméra au plan de projection
	float m_cameraX, m_cameraY, m_cameraZ;
	float m_cosinus, m_sinus;
	sf::Image m_image, m_imageTransformed;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	//===========  Public functions  ============
	void setScreen(unsigned int width, unsigned int height);
	void loadImage(std::string const& file);
	void setFOVangle(float angle);

}; // end Mode7