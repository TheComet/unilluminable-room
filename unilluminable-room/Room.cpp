// ----------------------------------------------------------------------------
// Room.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <Room.hpp>
#include <Exception.hpp>

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>

#include <SFML/Graphics/RenderTarget.hpp>

// ----------------------------------------------------------------------------
Room::Room() :
    m_IsLoaded( false )
{

    // load font required for rendering
    m_Font.loadFromFile( "arial.ttf" );
    m_TextA.setFont( m_Font );
    m_TextA.setCharacterSize( 18 );
    m_TextA.setString( "A" );
    m_TextB.setFont( m_Font );
    m_TextB.setCharacterSize( 18 );
    m_TextB.setString( "B" );
}

// ----------------------------------------------------------------------------
Room::~Room()
{
}

// ----------------------------------------------------------------------------
void Room::load( const std::string& configFile )
{

    // load and parse room configuration
#ifdef _DEBUG
    std::cout << "loading room" << std::endl;
#endif
    std::ifstream file( configFile.c_str() );
    if( file.is_open() )
    {
        std::string buffer;
        char r = 255, g = 255, b = 255;
        while( !file.eof() )
        {
            std::getline( file, buffer );

            // set global colour
            if( buffer.substr(0,7) == "colour=" )
            {
                std::size_t mid1 = buffer.find( "," );
                std::size_t mid2 = buffer.find( ",", mid1+1 );
                r = atoi( buffer.substr(7,mid1).c_str() );
                g = atoi( buffer.substr(mid1+1,mid2).c_str() );
                b = atoi( buffer.substr(mid2+1).c_str() );
            }

            // create line connection point
            if( buffer.substr(0,6) == "point=" )
            {
                std::size_t mid = buffer.find( "," );
                float x = atof( buffer.substr(6,mid).c_str() );
                float y = atof( buffer.substr(mid+1).c_str() );
#ifdef _DEBUG
                std::cout << "    adding point: " << x << "," << y << " with colour " <<
                static_cast<unsigned int>(r) << "," << static_cast<unsigned int>(g) << "," << static_cast<unsigned int>(b) <<
                ", string: " << buffer << std::endl;
#endif
                m_Room.addPoint( sf::Vector2f(x,y), sf::Color(r,g,b) );
            }

            // set points A and B
            if( buffer.substr(0,2) == "A=" )
            {
                std::size_t mid = buffer.find( "," );
                float x = atof( buffer.substr(2,mid).c_str() );
                float y = atof( buffer.substr(mid+1).c_str() );
                m_A = sf::Vector2f( x, y );
#ifdef _DEBUG
                std::cout << "    Point A set to " << x << "," << y << std::endl;
#endif
            }
            if( buffer.substr(0,2) == "B=" )
            {
                std::size_t mid = buffer.find( "," );
                float x = atof( buffer.substr(2,mid).c_str() );
                float y = atof( buffer.substr(mid+1).c_str() );
                m_B = sf::Vector2f( x, y );
#ifdef _DEBUG
                std::cout << "    Point B set to " << x << "," << y << std::endl;
#endif
            }
        }

    // failed to open file
    }else
    {
        std::stringstream ss; ss << "[Room::load] Error: Failed to open file \"" << configFile << "\"" << std::endl;
        throw Exception( ss.str() );
    }

    // is loaded
    m_IsLoaded = true;
}

// ----------------------------------------------------------------------------
void Room::unload()
{
    m_IsLoaded = false;
}

// ----------------------------------------------------------------------------
void Room::draw( sf::RenderTarget* target, const sf::RenderStates& states ) const
{

    // forward data for room
    m_Room.draw( target, states );

    // set render states for text
    sf::RenderStates textStatesA( states );
    sf::RenderStates textStatesB( states );
    textStatesA.transform.translate( m_A.x, m_A.y );
    textStatesB.transform.translate( m_B.x, m_B.y );

    // render text
    target->draw( m_TextA, textStatesA );
    target->draw( m_TextB, textStatesB );
}
