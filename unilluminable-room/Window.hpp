// ----------------------------------------------------------------------------
// Window.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <string>

// ----------------------------------------------------------------------------
// forward declarations

namespace sf {
    class RenderTarget;
    class RenderWindow;
}

/*!
 * @brief Initialises the render window according to the config file
 */
class Window
{
public:

    /*!
     * @brief Default constructor
     */
    Window();

    /*!
     * @brief Default destructor
     * Closes the window
     */
    ~Window();

    /*!
     * @brief Opens the window using the specified config file
     * @param configFile The configuration file to read from
     * @param windowTitle The title of the window
     */
    void open( const std::string& configFile, const std::string& windowTitle );

    /*!
     * @brief Closes the window
     */
    void close();

    /*!
     * @brief Returns the window
     * If @a open wasn't called, or if the render window isn't open, a zero
     * pointer is returned
     * @return A pointer to the active window
     */
    sf::RenderWindow* getRenderWindow() const;

private:

    sf::RenderWindow* m_Window;
};
