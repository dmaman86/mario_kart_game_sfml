#include "mode7.h"
#include "Pictures.h"
#include <cmath>
#include "Utilities.h"
#include "Macros.h"
Mode7::Mode7():m_D(0),m_FOV(0),m_H_helf(0),m_W_half(0),m_sinus(0),m_cosinus(0)
	,m_imageHeight(0),m_imageWidth(0),m_screenHeight(0),m_screenWidth(0)
{
}
//============================ Constructor ====================================
Mode7::Mode7(std::string const& file, unsigned int width, unsigned int height, float theta, float FOV)
{
	setScreen(width, height);
	loadImage(file);
	setFOVangle(FOV);
	setTheta(theta);
}

//========================== Public functions =================================
void Mode7::setTheta(float theta)
{
	m_cosinus = float(std::cos(theta * 3.1415 / 180.0));
	m_sinus = float(std::sin(theta * 3.1415 / 180.0));
}
//=============================================================================
bool Mode7::calcInAngle
	(sf::Vector2f & world_c, const sf::Vector2u& screen_c,const Camera& camera)
{
	auto dis_y = ((float)m_H_helf - (float)screen_c.y);
	auto dis_x = ((float)screen_c.x - (float)m_W_half);
	auto depth = m_D * camera.getY() / dis_y;
	auto dis = camera.getY() * dis_x / dis_y;

	world_c.x = camera.getX() - (dis * m_cosinus) - (depth * m_sinus);
	world_c.y = camera.getZ() - (dis * m_sinus) + (depth * m_cosinus);

	return (world_c.x < 0 || world_c.y < 0 ||
		world_c.x >= m_imageWidth || world_c.y >= m_imageHeight);
	
}

//=============================================================================

//this function build the new image and check witch objects are in fov
//if the object is in the fov the function set their position and size
void Mode7::UpdateImg
	(std::map<std::pair<float, float>, std::shared_ptr<GameObj>>& vec
	, const Camera& camera)
{
	float camera_length;
	sf::Vector2u screen_c;
	sf::Vector2f world_c;
	for (screen_c.y =  m_H_helf + 1 ;screen_c.y < m_screenHeight; screen_c.y++)
		for (screen_c.x = 0; screen_c.x < m_screenWidth; screen_c.x++)
		{
			if (this->calcInAngle(world_c, screen_c, camera))
			{
				m_imageTransformed.setPixel(screen_c.x, screen_c.y, sf::Color::Black);
			}
			else
			{
				m_imageTransformed.setPixel(screen_c.x, screen_c.y,
					m_image.getPixel((unsigned int)world_c.x, (unsigned int)world_c.y));

				for (auto& d : vec)
				{
	
					auto abz = abs(d.first.second - world_c.y);
					auto abx = abs(d.first.first - world_c.x);
					if (abz <= 4 && abx <= 4)
					{
						camera_length = (calcLength(sf::Vector2f(d.first.second, d.first.first),
							sf::Vector2f(camera.getZ(), camera.getX()))) / 8.f;
						if (camera_length >= 12.5|| (camera_length < 12.5 && abz <= 1 && abx <= 1)) {
							d.second->setInAngle(true);
							d.second->setPosition(sf::Vector2f(float(screen_c.x) * 2, float(screen_c.y) * 2));

							d.second->setScale(30 / camera_length, 30 / camera_length);

							if (camera_length < 0.5 || camera_length > 25)
								d.second->setInAngle(false);
						}
					}
				}
			}
		}
}


//=============================================================================
sf::Sprite Mode7::getSprite()
{
	m_texture.update(m_imageTransformed);
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(2,2);
	return m_sprite;
}

//========================== Public functions =================================
void Mode7::setScreen(unsigned int width, unsigned int height)
{
	m_screenWidth = width;
	m_screenHeight = height;
	m_H_helf = height / 2u;
	m_W_half = width / 2u;
	m_imageTransformed.create(m_screenWidth, m_screenHeight, sf::Color::Black);
	m_texture.create(m_screenWidth, m_screenHeight);
}

//=============================================================================
void Mode7::loadImage(std::string const& file)
{
	sf::Vector2u vec;
	m_image = Pictures::instance().getMapTex(file);
	vec = m_image.getSize();
	m_imageWidth = vec.x;
	m_imageHeight = vec.y;
}

//=============================================================================
void Mode7::setFOVangle(float angle)
{
	m_FOV = angle;
	m_D = m_H_helf / float(std::tan(m_FOV * 3.1415 / 360.0));
}