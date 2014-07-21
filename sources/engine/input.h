#ifndef ENGINE_INPUT_H
 #define ENGINE_INPUT_H

#include <set>
#include <GL/glew.h>
#include <SFML/Window.hpp>

namespace engine
{
    namespace input
    {

        typedef sf::Keyboard Keyboard;
        typedef sf::Mouse Mouse;

        typedef std::set<Keyboard::Key> KeySet;
        typedef std::set<Mouse::Button> ButtonSet;

        void captureEvents();
        bool isWindowClosed();
        bool isWindowResized();
        bool isJustPressed(Keyboard::Key k);
        bool isJustReleased(Keyboard::Key k);
        bool isPressed(Keyboard::Key k);
        bool isMouseJustPressed(Mouse::Button b);
        bool isMouseJustReleased(Mouse::Button b);
        bool isMousePressed(Mouse::Button b);

    }
}

#endif
