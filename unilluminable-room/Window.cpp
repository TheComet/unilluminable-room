// ----------------------------------------------------------------------------
// Window.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <Window.hpp>
#include <Exception.hpp>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <stdlib.h>

// ----------------------------------------------------------------------------
Window::Window() :
    m_Window(0)
{
}

// ----------------------------------------------------------------------------
Window::~Window()
{
    this->close();
}

// ----------------------------------------------------------------------------
void Window::open( const std::string& configFile, const std::string& windowTitle )
{

    // open config file and get video mode
    int width = 800, height = 600; // default
    std::ifstream file( configFile.c_str() );
    if( file.is_open() )
    {
        std::string buffer;
        while( !file.eof() )
        {
            std::getline( file, buffer );
            if( buffer.substr(0,11) == "resolution=" )
            {
                std::size_t mid = buffer.find("x");
                width = atoi( buffer.substr(11,mid-11).c_str() );
                height = atoi( buffer.substr(mid+1).c_str() );
            }
        }

    // warn user about default video mode
    }else
        std::cerr << "[Window::open] Failed to open config file \"" << configFile << "\". Using default settings..." << std::endl;;

    // create window
    std::cout << "Opening render window..." << std::endl;
    std::cout << "    width: " << width << ", height: " << height << std::endl;
    m_Window = new sf::RenderWindow( sf::VideoMode(width,height), windowTitle );
}

// ----------------------------------------------------------------------------
void Window::close()
{
    if( m_Window )
    {
        delete m_Window;
        m_Window = 0;
    }
}

// ----------------------------------------------------------------------------
sf::RenderWindow* Window::getRenderWindow() const
{
    return m_Window;
}
