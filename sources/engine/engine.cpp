#include <ctime>

#include "engine.h"

#define WIDTH  640
#define HEIGHT 480

namespace engine
{
    //Application::Application() : sf::RenderWindow(sf::VideoMode::GetDesktopMode(), "Ocean's Keeper 2", sf::Style::Fullscreen)
    Application::Application() : sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT, 32), "Ocean's Keeper 2", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar)
    {
        m_width = WIDTH;
        m_height = HEIGHT;
        m_frameTime = 0;
        setMouseCursorVisible(false);
    }

    void Application::setWindowModeSize(unsigned int w, unsigned int h)
    {
        m_width = w;
        m_height = h;
    }

    unsigned int Application::getWindowModeWidth()
    {
        return m_width;
    }

    unsigned int Application::getWindowModeHeight()
    {
        return m_height;
    }
    
    float Application::getFrameTime()
    {
        return m_frameTime;
    }
    
    void Application::display()
    {
        sf::RenderWindow::display();
        m_frameTime = m_clock.restart().asSeconds();
    }

    Application* app;

    void init()
    {
        app = new Application();
        app->setKeyRepeatEnabled(false);
        app->setVerticalSyncEnabled(true);
        srand(time(NULL));
    }

    bool isRunning()
    {
        return app->isOpen();
    }

    void stop()
    {
        app->close();
    }

    void free()
    {
        delete app;
    }

    unsigned int getWidth()
    {
        return app->getSize().x;
    }

    unsigned int getHeight()
    {
        return app->getSize().y;
    }

    bool fullscreen = false;

    void resize()
    {
        fullscreen = false;
        app->setWindowModeSize(getWidth(), getHeight());
        glViewport(0, 0, app->getWindowModeWidth(), app->getWindowModeHeight());
    }

    void toggleFullScreen()
    {
        fullscreen = !fullscreen;
        if (fullscreen)
        {
            app->create(sf::VideoMode::getDesktopMode(), "Ocean's Keeper 2", sf::Style::Fullscreen);
        }
        else
        {
            app->create(sf::VideoMode(app->getWindowModeWidth(), app->getWindowModeHeight(), 32), "Ocean's Keeper 2", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
        }
    }
    
    void takeScreenShot()
    {
        sf::Image screen = app->capture();
        screen.saveToFile("screenshot.jpg");
    }

    Application* getApplication()
    {
        return app;
    }
}
