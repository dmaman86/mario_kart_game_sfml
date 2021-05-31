#include "mode7.h"
#include "Pictures.h"
/*Mode7::Mode7() : m_screenWidth{}, m_screenHeight{}, m_T{}, m_L{},
            m_imageWidth{}, m_imageHeight{}, m_FOV{}, m_D{}, m_cameraX{},
            m_cameraY{}, m_cameraZ{}, m_cosinus{1}, m_sinus{} {}
*/

Mode7::Mode7(std::string const &file, unsigned int width, unsigned int height, float cameraX, float cameraY, float cameraZ, float theta, float FOV)
{
    setScreen(width, height);

    try
    {
        loadImage(file);
    }
    catch(char const *s)
    {
        std::cout << s << " " << file << std::endl;
        exit(EXIT_FAILURE);
    }

    setCamera(cameraX, cameraY, cameraZ);
    setFOVangle(FOV);
    setTheta(theta);
}

void Mode7::setScreen(unsigned int width, unsigned int height)
{
    m_screenWidth = width;
    m_screenHeight = height;
    m_T = height / 2;
    m_L = width / 2;

    m_imageTransformed.create(m_screenWidth, m_screenHeight, sf::Color::Black);
    m_texture.create(m_screenWidth, m_screenHeight);
}

void Mode7::loadImage(std::string const &file)
{
    sf::Vector2u vec;
    m_image = Pictures::instance().getMapTex(Pictures::mario_circuit_2);

    vec = m_image.getSize();
    m_imageWidth = vec.x;
    m_imageHeight = vec.y;
}

void Mode7::setCamera(float x, float y, float z)
{
    m_cameraX = x;
    m_cameraY = y;
    m_cameraZ = z;
}

void Mode7::setFOVangle(float angle)
{
    m_FOV = angle;
    m_D = m_T / std::tan(m_FOV * 3.1415 / 360.0);
}

void Mode7::setTheta(float theta)
{
    m_cosinus = std::cos(theta * 3.1415 / 180.0);
    m_sinus = std::sin(theta * 3.1415 / 180.0);
}

void Mode7::calc()
{
    for(unsigned int ys{m_T + 1}; ys < m_screenHeight; ys++)
        for(unsigned int xs{}; xs < m_screenWidth; xs++)
        {
            float const xw = m_cameraX - m_cameraY*((float)xs - (float)m_L) / ((float)m_T - (float)ys) * m_cosinus - m_D*m_cameraY / ((float)m_T - (float)ys) * m_sinus;
            float const zw = m_cameraZ - m_cameraY*((float)xs - (float)m_L) / ((float)m_T - (float)ys) * m_sinus + m_D*m_cameraY / ((float)m_T - (float)ys) * m_cosinus;

            if(xw < 0 || zw < 0 || xw >= m_imageWidth || zw >= m_imageHeight)
                m_imageTransformed.setPixel(xs, ys, sf::Color::Black);
            else
                m_imageTransformed.setPixel(xs, ys, m_image.getPixel((unsigned int)xw, (unsigned int )zw));
        }
}



sf::Sprite Mode7::getSprite()
{
    m_texture.update(m_imageTransformed);
    m_sprite.setTexture(m_texture);
    return m_sprite;
}