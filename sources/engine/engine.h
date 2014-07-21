#ifndef ENGINE_ENGINE_H
 #define ENGINE_ENGINE_H

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

namespace engine
{

    class Application : public sf::RenderWindow
    {
        public:
            Application();

            void setWindowModeSize(unsigned int w, unsigned int h);

            unsigned int getWindowModeWidth();
            unsigned int getWindowModeHeight();
            
            float getFrameTime();
            
            void display();

        private:
            unsigned int m_width;
            unsigned int m_height;
            sf::Clock m_clock;
            float m_frameTime;
    };

    void init();
    bool isRunning();
    void stop();
    void free();
    unsigned int getWidth();
    unsigned int getHeight();
    void resize();
    void toggleFullScreen();
    void takeScreenShot();
    Application* getApplication();

}

#endif
