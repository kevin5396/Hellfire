
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include "SFML.h"
#include "Application.h"
// Here is a small helper for you ! Have a look.

int main(int, char const**)
{
    try
    {
        Application app;
        app.run();
        //Game game;
        //game.run();
    }
    catch (std::exception& e)
    {
        std::cout << "Exception : " << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
