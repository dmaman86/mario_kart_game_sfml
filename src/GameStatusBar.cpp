#include "GameStatusBar.h"
#include "Fonts.h"

GameStatusBar::GameStatusBar() :m_score(0){

    m_scoreText.setFont(Fonts::instance().getFont());
    m_levelText.setFont(Fonts::instance().getFont());
    m_lifeText.setFont(Fonts::instance().getFont());
    m_timeTheLevel.setFont(Fonts::instance().getFont());

    m_lifeText.setCharacterSize(50);
    m_scoreText.setCharacterSize(50);
    m_levelText.setCharacterSize(50);
    m_timeTheLevel.setCharacterSize(50);

}

//====================================================
void GameStatusBar::printGameStatus(sf::RenderWindow& window, const  sf::Time& timeLevel,
    const sf::Clock& time, bool m_isOnTime, int score, int lap) {

    // print status 
    printChangeColor(lap, time, timeLevel, score);
    // Computer time plays for printing
    float lefttime = timeLevel.asSeconds() - time.getElapsedTime().asSeconds();

    std::string scorestr = "000000";

    if (score >= 100)
        scorestr += "0";

    scorestr.replace(scorestr.size() - std::to_string(score).size(),
        std::to_string(score).size(), std::to_string(score));
    m_scoreText.setString("Score:" + scorestr);
    m_lifeText.setString("Lap:" + std::to_string(lap));

    // if game is on time
    if (m_isOnTime)
    {
        if (lefttime < 10)
            m_timeTheLevel.setFillColor(sf::Color::Red);
        else
            m_timeTheLevel.setFillColor(sf::Color::White);

        m_timeTheLevel.setString("Time:" + std::to_string(lefttime));
    }
    else// if not
    {
        m_timeTheLevel.setString("Time: 9999");
    }

    m_scoreText.setPosition(800, 800);
    m_levelText.setPosition(m_scoreText.getPosition().x + m_scoreText.getGlobalBounds().width + 30.f, 809);
    m_lifeText.setPosition(m_levelText.getPosition().x + m_levelText.getGlobalBounds().width + 30.f, 809);
    m_timeTheLevel.setPosition(m_lifeText.getPosition().x + m_lifeText.getGlobalBounds().width + 30.f, 809);

    printboard(window);

}
//====================================================

void GameStatusBar::printboard(sf::RenderWindow& window) {
    window.draw(m_lifeText);
    window.draw(m_scoreText);
    window.draw(m_levelText);
    window.draw(m_timeTheLevel);

}
//====================================================
void GameStatusBar::printChangeColor(int life, const sf::Clock& clock,
    const sf::Time& time, int score) {
    // If the score is greater than the current score 
    if (score > m_score)
    {
        m_scoreText.setFillColor(sf::Color::Green);
        m_scorechange = clock.getElapsedTime();
    }
    // If life is smaller than the present life
    if (life < m_life)
    {
        m_lifeText.setFillColor(sf::Color::Red);
        m_lifechange = clock.getElapsedTime();

    }
    // If the life is greater than the current life
    if (life > m_life)
    {
        m_lifeText.setFillColor(sf::Color::Green);
        m_lifechange = clock.getElapsedTime();
    }
    // If the time is greater than the current time
    if (time > m_time)
    {
        m_timeTheLevel.setFillColor(sf::Color::Green);
        m_timechange = clock.getElapsedTime();
    }
    m_life = life;
    m_time = time;
    m_score = score;

    if (clock.getElapsedTime().asSeconds() > m_scorechange.asSeconds() + 2)
        m_scoreText.setFillColor(sf::Color::White);

    if (clock.getElapsedTime().asSeconds() > m_timechange.asSeconds() + 2)
        m_timeTheLevel.setFillColor(sf::Color::White);

    if (clock.getElapsedTime().asSeconds() > m_lifechange.asSeconds() + 2)
        m_lifeText.setFillColor(sf::Color::White);

}
//====================================================

