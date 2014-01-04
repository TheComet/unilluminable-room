// ----------------------------------------------------------------------------
// include files

#include <SFML/System/Clock.hpp>

// ----------------------------------------------------------------------------
// forward declarations
namespace sf {
	class Clock;
}

/*! \brief Handles timings used in the main loop
 *
 * The main loop is composed of an "update loop" and a
 * "render loop". The update loop updates all of the game
 * logic, and should be called 60 times a second. The render
 * loop is detached, and needs to run as fast as possible
 *
 * This class takes care of counting and synchronizing the
 * update loop
 */
class LoopTimer
{
public:

	/*!
	 * \brief Default constructor
	 */
	LoopTimer( void );

	/*!
	 * \brief Default destructor
	 */
	~LoopTimer( void );

	 /*!
	 * \brief Resets the timer
	 *
	 * Will reset the timer and the loop counter to 0
	 */
	void reset( void );

	 /*!
	 * \brief Returns true when it's time to call the update loop
	 *
	 * \return If it's time to call the update loop, true is returned
	 */
	bool isTimeToUpdate( void );

	 /*!
	 * \brief Sets the frame rate the update loop should have
	 *
	 * \param The frame rate the update loop should aim to be
	 */
	void setFPS( unsigned long fps );

	 /*!
	 * \brief Gets the current rendering frame rate
	 *
	 * \return Returns the current rendering frame rate
	 */
	unsigned long getRenderFPS( void );

	 /*!
	 * \brief Gets the current update frame rate
	 *
	 * \return Returns the current update frame rate
	 */
	unsigned long getUpdateFPS( void );

private:

	// timer implementation
	sf::Clock m_Timer;

	// counts how many render loops have passed
	// this is incremented every time checkUpdateLoop() is called
	unsigned long m_UpdateLoopCounter;

	// counts how many update loops were authorized
	// this is only incremented whenever it is time to update the logic loop
	unsigned long m_RenderLoopCounter;

	// stores how much time is allowed to be between frames
	unsigned long m_TimeBetweenFrames;

	// statistics
	struct statistics_t
	{
		statistics_t( void );
		unsigned long lastUpdated;
		unsigned long renderFrameRate;
		unsigned long updateFrameRate;
		unsigned long lastUpdateLoopCounter;
		unsigned long lastRenderLoopCounter;
	}m_Statistics;

};
