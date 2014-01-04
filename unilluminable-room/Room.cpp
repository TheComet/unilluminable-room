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

// ----------------------------------------------------------------------------
Room::Room()
{
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
                std::size_t mid1 = buffer.find(",");
                std::size_t mid2 = buffer.find(",",mid1+1);
                r = atoi( buffer.substr(7,mid1).c_str() );
                g = atoi( buffer.substr(mid1+1,mid2).c_str() );
                b = atoi( buffer.substr(mid2+1).c_str() );
            }

            // create point
            if( buffer.substr(0,6) == "point=" )
            {
                std::size_t mid = buffer.find(",");
                float x = atof( buffer.substr(6,mid).c_str() );
                float y = atof( buffer.substr(mid+1).c_str() );
#ifdef _DEBUG
                std::cout << "    adding point: " << x << "," << y << " with colour " <<
                static_cast<unsigned int>(r) << "," << static_cast<unsigned int>(g) << "," << static_cast<unsigned int>(b) <<
                ", string: " << buffer << std::endl;
#endif
                m_Room.addPoint( sf::Vector2f(x,y), sf::Color(r,g,b) );
            }
        }

    // failed to open file
    }else
    {
        std::stringstream ss; ss << "[Room::load] Error: Failed to open file \"" << configFile << "\"" << std::endl;
        throw Exception( ss.str() );
    }
}

// ----------------------------------------------------------------------------
void Room::draw( sf::RenderTarget* target, const sf::RenderStates& states ) const
{
    m_Room.draw( target, states ); // forward data
}
