#include "genTree.hpp"
#include "Evenement.hpp"
#include <fstream>
#include <iostream>
#include <unistd.h>

void genTree::generatePoint(n_data data)
{
    Evenement new_point;

    // * Set The Position with the given longitude and latitude
    // * longitude + Latitude
    new_point.m_shape_Evenement.setPosition({1000 * data.longitude / 180, 530 * data.latitude / -90});
    new_point.m_shape_Evenement.setRadius(3);
    new_point.m_data = data;

    // * Change the color according to the type of event
    if (data.type == m_Evenement_type::BIRTH)
        new_point.m_shape_Evenement.setFillColor(sf::Color::Red);
    else if (data.type == m_Evenement_type::DEATH)
        new_point.m_shape_Evenement.setFillColor(sf::Color::Black);
    else if (data.type == m_Evenement_type::WEDDING)
        new_point.m_shape_Evenement.setFillColor(sf::Color::Magenta);

    m_point.push_back(new_point);
}

/*
    * Scale the size of the point according to the current zoom
    * of the view
*/

void genTree::scalePoint(sf::Vector2f actualSize)
{
    auto radius = m_point[0].m_shape_Evenement.getRadius();

    static float oldRatio = 2000;

    // * Iteration on all the points
    for (auto &i : m_point)
    {
        if (actualSize.x/oldRatio > 1)
            i.m_shape_Evenement.setRadius(radius * 1.02);
        else if (actualSize.x / oldRatio < 1)
            i.m_shape_Evenement.setRadius(radius * 0.98);
    }
    oldRatio = actualSize.x;
}

/* 
    * Event Handling
    * W/S Zoom in/out
    * Key arrow to move the View
*/

void genTree::event()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Resized)
        {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            m_window.setView(sf::View(visibleArea));
        }
        else if (event.type == sf::Event::Closed)
            m_window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            sf::View view = m_window.getView();
            view.zoom(0.99);
            m_window.setView(view);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            sf::View view = m_window.getView();
            view.zoom(1.01);
            m_window.setView(view);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            sf::View view = m_window.getView();
            view.move(-20, 0);
            m_window.setView(view);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            sf::View view = m_window.getView();
            view.move(20, 0);
            m_window.setView(view);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            sf::View view = m_window.getView();
            view.move(0, -20);
            m_window.setView(view);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            sf::View view = m_window.getView();
            view.move(0, 20);
            m_window.setView(view);
        }
    }
}

void genTree::run()
{
    sf::Clock clock;
    int nbr = 500;
    
    while (m_window.isOpen()) {
        // * Init the View
        if (nbr == 500) {
            sf::View view = m_window.getView();
            view.setCenter(0, 0);
            m_window.setView(view);
        }

        event();
        
        sf::Time elapsed1 = clock.getElapsedTime();
        if (elapsed1.asMilliseconds() >= 50) {
            m_window.draw(m_background);
            nbr++;
            for (auto &i : m_point)
            {
                if (nbr == i.m_data.intDate[0] || nbr - 1 == i.m_data.intDate[0])
                    m_window.draw(i.getShape());
            }
            clock.restart();
            m_window.display();
            m_window.clear();
        }
        scalePoint(m_window.getView().getSize());
    }
}

void genTree::init()
{
    for (int i = 0; i < m_data.size(); i++)
        generatePoint(m_data[i]);
}