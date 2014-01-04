// ----------------------------------------------------------------------------
// LineStripBatch.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <LineStripBatch.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

// ----------------------------------------------------------------------------
LineStripBatch::LineStripBatch()
{
}

// ----------------------------------------------------------------------------
LineStripBatch::~LineStripBatch()
{
}

// ----------------------------------------------------------------------------
void LineStripBatch::addPoint( const sf::Vector2f& point, const sf::Color& color )
{
    m_Vertices.push_back( sf::Vertex(point,color) );
}

// ----------------------------------------------------------------------------
void LineStripBatch::removePoint( const sf::Vector2f& point )
{
    for( std::vector<sf::Vertex>::iterator it = m_Vertices.begin(); it != m_Vertices.end(); ++it )
        if( it->position == point )
            m_Vertices.erase( it );
}

// ----------------------------------------------------------------------------
void LineStripBatch::removeAllPoints()
{
    m_Vertices.clear();
}

// ----------------------------------------------------------------------------
void LineStripBatch::draw( sf::RenderTarget* target, const sf::RenderStates& states ) const
{
    if( m_Vertices.size() )
        target->draw( &m_Vertices[0], m_Vertices.size(), sf::LinesStrip, states );
}
