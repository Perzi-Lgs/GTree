#pragma once

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Parsing.hpp"

class Evenement
{
private:
    m_Evenement_type Evenement_type;
public:
    sf::CircleShape m_shape_Evenement;
    n_data m_data;
    
    // Evenement(m_Evenement_type a, sf::Color col = {255, 255, 255, 255}) {}
    Evenement()
    {
        m_shape_Evenement.setOrigin(m_shape_Evenement.getRadius(), m_shape_Evenement.getRadius());
    };
    ~Evenement() = default;
    void setPosition(float x, float y) { m_shape_Evenement.setPosition({x, y}); };
    void setPosition(sf::Vector2f pos) { m_shape_Evenement.setPosition(pos); };
    void setColor(sf::Color color) { m_shape_Evenement.setFillColor(color); };
    sf::CircleShape &getShape() { return m_shape_Evenement; };
};

//-380
//