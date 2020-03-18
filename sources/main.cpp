#include <iostream>
#include "genTree.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

int main(int argc, char const *argv[])
{
    try
    {
        Parsing parser;
        genTree tree;

        parser.run("data/Birth.txt", tree.getData(), m_Evenement_type::BIRTH);
        parser.run("data/Death.txt", tree.getData(), m_Evenement_type::DEATH);
        parser.run("data/Wedding.txt", tree.getData(), m_Evenement_type::WEDDING);
        tree.init();
        tree.run();
    }
    catch(const std::exception& e)
    {
        std::cout << "Exception Occured" << std::endl;
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
