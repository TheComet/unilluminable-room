// ----------------------------------------------------------------------------
// include files

#include <iostream>

#include <LoopTimer.hpp>

// ----------------------------------------------------------------------------
LoopTimer::LoopTimer() :
	m_UpdateLoopCounter( 0 ),
	m_RenderLoopCounter( 0 ),
	m_TimeBetweenFrames( 0 )
{
}

// ----------------------------------------------------------------------------
LoopTimer::statistics_t::statistics_t() :
	lastUpdated( 0 ),
	renderFrameRate( 0 ),
	updateFrameRate( 0 ),
	lastUpdateLoopCounter( 0 ),
	lastRenderLoopCounter( 0 )
{
}

// ----------------------------------------------------------------------------
LoopTimer::~LoopTimer()
{
}

// ----------------------------------------------------------------------------
void LoopTimer::reset()
{
	m_Timer.restart();
	m_UpdateLoopCounter = 0;
	m_RenderLoopCounter = 0;
	m_Statistics.lastUpdated = m_Timer.getElapsedTime().asMilliseconds();
}

// ----------------------------------------------------------------------------
void LoopTimer::setFPS( unsigned long fps )
{
	// calculate time between frames in milliseconds
	m_TimeBetweenFrames = 1000 / fps;
}

// ----------------------------------------------------------------------------
bool LoopTimer::isTimeToUpdate()
{

	// update internal statistics every second
	if( m_Timer.getElapsedTime().asMilliseconds() - m_Statistics.lastUpdated > 1000 )
	{

		// calculate render frame rate
		m_Statistics.renderFrameRate = m_RenderLoopCounter - m_Statistics.lastRenderLoopCounter;

		// calculate update frame rate
		m_Statistics.updateFrameRate = m_UpdateLoopCounter - m_Statistics.lastUpdateLoopCounter;

		// update statistics for next time
		m_Statistics.lastUpdated = m_Timer.getElapsedTime().asMilliseconds();
		m_Statistics.lastUpdateLoopCounter = m_UpdateLoopCounter;
		m_Statistics.lastRenderLoopCounter = m_RenderLoopCounter;

		std::cout << "render FPS: " << m_Statistics.renderFrameRate <<
			"			update FPS: " << m_Statistics.updateFrameRate << std::endl;
	}

	// calling this method means a render loop has occured
	++m_RenderLoopCounter;

	// if time that has passed is smaller than the time that should have
	// passed, it's not time to update yet
	if( m_Timer.getElapsedTime().asMilliseconds() < m_UpdateLoopCounter * m_TimeBetweenFrames )
        return false;

	// game loop has been updated, increase counter
	++m_UpdateLoopCounter;

	// time to update
	return true;
}

// ----------------------------------------------------------------------------
unsigned long LoopTimer::getRenderFPS()
{
	return m_Statistics.renderFrameRate;
}

// ----------------------------------------------------------------------------
unsigned long LoopTimer::getUpdateFPS()
{
	return m_Statistics.updateFrameRate;
}

