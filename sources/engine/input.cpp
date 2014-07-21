#include "input.h"
#include "engine.h"

namespace engine
{
    namespace input
    {

        KeySet justPressedKeys;
        KeySet justReleasedKeys;
        ButtonSet justPressedButtons;
        ButtonSet justReleasedButtons;

        bool windowClosed;
        bool windowResized;

        void captureEvents()
        {
            justPressedKeys.clear();
            justReleasedKeys.clear();
            windowClosed = false;
            windowResized = false;

            sf::Event event;

            while (getApplication()->pollEvent(event))
            {
                switch (event.type)
                {
                    case sf::Event::KeyPressed:
                    justPressedKeys.insert(event.key.code);
                    break;

                    case sf::Event::KeyReleased:
                    justReleasedKeys.insert(event.key.code);
                    break;

                    case sf::Event::MouseButtonPressed:
                    justPressedButtons.insert(event.mouseButton.button);
                    break;

                    case sf::Event::MouseButtonReleased:
                    justReleasedButtons.insert(event.mouseButton.button);
                    break;

                    case sf::Event::Closed:
                    windowClosed = true;
                    break;

                    case sf::Event::Resized:
                    windowResized = true;
                    break;

                    default:;
                }
            }
        }

        bool isWindowClosed()
        {
            return windowClosed;
        }

        bool isWindowResized()
        {
            return windowResized;
        }

        bool isJustPressed(Keyboard::Key k)
        {
            return justPressedKeys.find(k) != justPressedKeys.end();
        }

        bool isJustReleased(Keyboard::Key k)
        {
            return justReleasedKeys.find(k) != justReleasedKeys.end();
        }

        bool isPressed(Keyboard::Key k)
        {
            return sf::Keyboard::isKeyPressed(k);
        }

        bool isMouseJustPressed(Mouse::Button b)
        {
            return justPressedButtons.find(b) != justPressedButtons.end();
        }

        bool isMouseJustReleased(Mouse::Button b)
        {
            return justReleasedButtons.find(b) != justReleasedButtons.end();
        }

        bool isMousePressed(Mouse::Button b)
        {
            return sf::Mouse::isButtonPressed(b);
        }

    }
}
