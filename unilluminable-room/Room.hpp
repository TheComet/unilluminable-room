// ----------------------------------------------------------------------------
// Room.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <Drawable.hpp>
#include <LineStripBatch.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>

// ----------------------------------------------------------------------------
// forward declarations

namespace sf {
    class RenderTarget;
    class RenderStates;
}

/*!
 * @brief Handles loading a room definition from a configuration file and drawing it
 */
class Room :
    public Drawable
{
public:

    /*!
     * @brief Default constructor
     */
    Room();

    /*!
     * @brief Default destructor
     */
    ~Room();

    /*!
     * @brief Loads a room from a configuration file
     * @param configFile Configuration file to load
     * @exception If the configuration file specified does not exist, an
     * exception is thrown (base std::exception)
     */
    void load( const std::string& configFile );

    /*!
     * @brief Unloads the room
     * This doesn't do anything other than stopping the room from being drawn
     */
    void unload();

    /*!
     * @brief Draws the room to the specified render target
     */
    void draw( sf::RenderTarget* target, const sf::RenderStates& states ) const;

private:

    LineStripBatch m_Room;
    sf::Vector2f m_A;
    sf::Vector2f m_B;

    sf::Text m_TextA;
    sf::Text m_TextB;
    sf::Font m_Font;

    bool m_IsLoaded;
};
