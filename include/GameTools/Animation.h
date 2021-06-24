#pragma once

#include <SFML/Graphics.hpp>

// Animation
class Animation
{
public:
	//Constructors/Destructor
    Animation(sf::Sprite& sprite) : 
		m_sprite(sprite),m_animationTime(0),
		m_is_cyclic(false),m_vector_len(0){};
    
	Animation(const std::vector <sf::IntRect >&,
		sf::Sprite& , const float, const bool ,
		const unsigned int spinlen );
	
	~Animation() = default;
	//public functions
    void update(float delta, bool is_pressed);
    void spin();
    void setIndex(int i){m_index = i;}
private:
	//private members
    const std::vector <sf::IntRect> m_data;
    float m_elapsed = {};
    sf::Sprite& m_sprite;
    float m_animationTime;
    int m_index = 0;
    bool m_is_cyclic;
    unsigned int m_vector_len;
	//private functions
	void update();

};//end Animation
