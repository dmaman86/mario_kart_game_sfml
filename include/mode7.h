#pragma once
#define MODE7_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "GameObj.h"
class Mode7 final
{

private:
	unsigned int m_screenWidth, m_screenHeight;
	unsigned int m_T, m_L; // variable intermédiare m_T = m_screenHeght /2 et m_L = mscreenWidth / 2 (T: top, L: left)
	unsigned int m_imageWidth, m_imageHeight;
	float m_FOV, m_D; // m_D distance du point de la caméra au plan de projection
	float m_cameraX, m_cameraY, m_cameraZ;
	float m_cosinus, m_sinus;
	sf::Image m_image, m_imageTransformed;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

public:
	Mode7() {};
	//   Mode7(const Mode7&) = delete;
	//   Mode7(const Mode7&&) = delete;
	Mode7(std::string const& file, unsigned int width, unsigned int height, float x, float y, float z, float theta, float FOV);
	void setScreen(unsigned int width, unsigned int height);
	void loadImage(std::string const& file);
	void setCamera(float x, float y, float z);
	void setFOVangle(float angle);
	void setTheta(float theta);
	void calc(std::map<std::pair<float, float >, std::unique_ptr<GameObj>>&, const sf::Vector2f);
	sf::Sprite getSprite();

	float calcLength(sf::Vector2f a, sf::Vector2f b) {
		return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}

};