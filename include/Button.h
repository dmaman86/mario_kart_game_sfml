#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include <memory>
#include <functional>

class Button : public sf::Drawable, public sf::Transformable
{
public:
    typedef std::function<void()> Callback;
public:
	Button( const std::string& );
	Button(const std::string&, const std::string&);
	~Button() = default;

	bool validGlobalBound(const sf::Vector2f& );
	void updateIfSelected(bool selected){ m_selected = selected; }
	void resetIfSelected(){ m_selected = false; }
	void setTextureInRect( int, int, int, int );
    void setInScale(float, float);
    void setIntoScale(float, float);
    void setInPosition( const sf::Vector2f& );
    const sf::Vector2f& getInPosition(){ return m_button.getPosition(); }
    void setInOrigin(){
        m_button.setOrigin(m_button.getLocalBounds().width / 2,
                         m_button.getLocalBounds().height / 2);
    }
    // void draw( sf::RenderWindow* );
    float getWidth(){ return m_button.getGlobalBounds().width; }
    float getHeight(){ return m_button.getGlobalBounds().height; }
    const std::string& getName(){ return m_name; }
    void setId(const std::string& id){ m_id = id; }
    const std::string& getId(){ return m_id; }
    const bool& getIfSelected(){ return m_selected; }
    void setFillInColor(int x, int y, int z, int w){
        m_button.setColor(sf::Color(x, y, z, w));
    }
    void setCallback(Callback);
    void initCallback();
    const sf::Sprite& getSprite(){ return m_button; }

private:
    void draw(sf::RenderTarget&, sf::RenderStates) const;

private:
	sf::Sprite m_button;
	std::string m_name;
	std::string m_id;
	bool m_selected;
	Callback m_callBack;
};