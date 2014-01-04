// ----------------------------------------------------------------------------
// App.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

/*!
 * @brief Entry point for this application
 */
class App
{
public:

    /*!
     * @brief Default constructor
     */
    App();

    /*!
     * @brief Default destructor
     */
    ~App();

    /*!
     * @brief Executes the application
     * @exception If anything goes wrong, exception (base std::exception) is thrown
     */
    void go();
};
