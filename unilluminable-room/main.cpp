// ----------------------------------------------------------------------------
// unilluminable room simulation
// ----------------------------------------------------------------------------
// author       : TheComet (Alex Murray)
// date started : 4. January 2013, 17:18 GMT+1
// date finished:
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <App.hpp>

#include <exception>
#include <iostream>

int main()
{

    App* theApp;
    try {
        theApp = new App();
        theApp->go();
    }catch( const std::exception& e )
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
