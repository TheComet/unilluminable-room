// ----------------------------------------------------------------------------
// App.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <App.hpp>
#include <LineStripBatch.hpp>
#include <LoopTimer.hpp>
#include <Window.hpp>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <Exception.hpp>

// ----------------------------------------------------------------------------
App::App()
{
}

// ----------------------------------------------------------------------------
App::~App()
{
}

// ----------------------------------------------------------------------------
void App::go()
{

    // list of objects to render every frame
    std::vector<Drawable*> renderList;

    // set up zooming parameters
    float zoomLimitMax = 2.0f;
    float zoomLimitMin = 0.125f;
    float zoomSmoothnessFactor = 4.0f;
    float currentZoom = 1.0f, targetZoom = 1.0f;
    sf::Vector2f viewPosition(0.0f,0.0f);
    sf::Vector2i pinchScrollPosition;
    bool isScrolling = false;

    // mouse states
    sf::Vector2i mousePosition;
    bool mouseButton1 = false;

    // load and parse room configuration
#ifdef _DEBUG
    std::cout << "loading room" << std::endl;
#endif
    LineStripBatch room;
    renderList.push_back( &room );
    std::ifstream file( "room.cfg" );
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
                room.addPoint( sf::Vector2f(x,y), sf::Color(r,g,b) );
            }
        }

    // failed to open file
    }else
    {
        std::stringstream ss; ss << "Error: Failed to open file \"room.cfg\"" << std::endl;
        throw Exception( ss.str() );
    }

    // open render window
    Window window;
    window.open( "window.cfg", "Unilluminable Room Simulation" );

    // set up loop timer
    LoopTimer loopTimer;
    loopTimer.setFPS( 60 );

    // run the program as long as the window is open
    while (window.getRenderWindow()->isOpen())
    {

        // update game logic
        int maxUpdateLoops = 0;
        while( loopTimer.isTimeToUpdate() )
        {

            // limit amount of update loops allowed
            if( ++maxUpdateLoops == 10 )
                break;
        }

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while( window.getRenderWindow()->pollEvent(event) )
        {

            // "close requested" event: close the window
            if( event.type == sf::Event::Closed )
                window.close();

            // handle zooming
            if( event.type == sf::Event::MouseWheelMoved )
            {
                targetZoom += event.mouseWheel.delta/50.0f;
                if( targetZoom >= zoomLimitMax ) targetZoom = zoomLimitMax;
                if( targetZoom <= zoomLimitMin ) targetZoom = zoomLimitMin;
            }

            // mouse button pressed
            if( event.type == sf::Event::MouseButtonPressed )
            {

                // begin scrolling
                if( event.mouseButton.button == sf::Mouse::Right )
                {
                    isScrolling = true;
                    pinchScrollPosition.x = event.mouseButton.x;
                    pinchScrollPosition.y = event.mouseButton.y;
                }
            }

            // mouse button released
            if( event.type == sf::Event::MouseButtonReleased )
            {

                // release mouse
                if( event.mouseButton.button == sf::Mouse::Left )
                    mouseButton1 = false;

                // end scrolling
                if( event.mouseButton.button == sf::Mouse::Right )
                    isScrolling = false;
            }

            // mouse movement
            if( event.type == sf::Event::MouseMoved )
            {

                // set mouse position
                mousePosition.x = event.mouseMove.x;
                mousePosition.y = event.mouseMove.y;

                // handle scrolling
                if( isScrolling )
                {
                    viewPosition.x += static_cast<float>(event.mouseMove.x - pinchScrollPosition.x)/currentZoom;
                    viewPosition.y += static_cast<float>(event.mouseMove.y - pinchScrollPosition.y)/currentZoom;
                    pinchScrollPosition.x = event.mouseMove.x;
                    pinchScrollPosition.y = event.mouseMove.y;
                }

            }

        }

        // clear
        window.getRenderWindow()->clear();

        // create render state
        sf::Transform transform;
        transform.translate( viewPosition );
        transform.scale( currentZoom, currentZoom );
        sf::RenderStates states;
        states.transform = transform;

        // draw everything to render window
        for( std::vector<Drawable*>::iterator it = renderList.begin(); it != renderList.end(); ++it )
            (*it)->draw( window.getRenderWindow(), states );

        // end the current frame
        window.getRenderWindow()->display();
    }

}
