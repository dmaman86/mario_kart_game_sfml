#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include <memory>
#include <functional>

// class button with multiple ingeritance
class Button : public sf::Drawable, public sf::Transformable {
public:
    // button can have function like member
    typedef std::function<void()> Callback;
public:
    // constructor & destructor
    Button(const std::string &);

    Button(const std::string &, const std::string &);

    ~Button() = default;

    // public functions
    bool validGlobalBound(const sf::Vector2f &);

    void updateIfSelected(bool);

    void resetIfSelected();

    void setTextureInRect(const sf::IntRect&);
    void setTextureInRect(int, int, int, int);

    void setInScale(float, float);

    void setIntoScale(float, float);

    void setInPosition(const sf::Vector2f &);

    const sf::Vector2f &getInPosition();

    void setInOrigin();

    float getWidth();

    float getHeight();

    const std::string &getName();

    void setId(const std::string &);

    const std::string &getId();

    const bool &getIfSelected();

    void setFillInColor(sf::Color);

    void setCallback(Callback);

    void initCallback();

    const sf::Sprite &getSprite();

private:
    // private function to draw in window
    void draw(sf::RenderTarget &, sf::RenderStates) const;

private:
    // private members
	sf::Sprite m_button;
	std::string m_name;
	std::string m_id;
	bool m_selected;
	// function member
	Callback m_callBack;
};