// ----------------------------------------------------------------------------
// Room.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <Drawable.hpp>
#include <LineStripBatch.hpp>

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
     * @brief Draws the room to the specified render target
     */
    void draw( sf::RenderTarget* target, const sf::RenderStates& states ) const;

private:

    LineStripBatch m_Room;
};
