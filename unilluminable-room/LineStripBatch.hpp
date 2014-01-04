// ----------------------------------------------------------------------------
// LineStripBatch.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include <vector>

// ----------------------------------------------------------------------------
// forward declarations

namespace sf {
    class RenderTarget;
    class RenderStates;
}

/*!
 * @brief Class that handles a batch of lines to be drawn
 * It holds a list of points that are then connected with lines
 */
class LineStripBatch :
    public Drawable
{
public:

    /*!
     * @brief Default constructor
     */
    LineStripBatch();

    /*!
     * @brief Default destructor
     */
    ~LineStripBatch();

    /*!
     * @brief Adds a point to be drawn
     */
    void addPoint( const sf::Vector2f& point, const sf::Color& colorA = sf::Color(255,255,255) );

    /*!
     * @brief Removes a point
     * Silently fails if the point doesn't exist
     */
    void removePoint( const sf::Vector2f& A );

    /*!
     * @brief Removes all points
     */
    void removeAllPoints();

    /*!
     * @brief Draws the line strip batch to a render target
     */
    void draw( sf::RenderTarget* target, const sf::RenderStates& states ) const;

private:

    std::vector<sf::Vertex> m_Vertices;

};
